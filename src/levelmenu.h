#pragma once

#include "common.h"
#include "game.h"
#include "resource_key.h"
#include "resource_manager.h"
#include "fixedstring.h"
#include "resource_partition.h"
#include "igofrontend.h"
#include "string_hash.h"
#include "actor.h"
#include "entity.h"
#include "femanager.h"
#include "debug_menu.h"
#include "mstring.h"
#include "fe_health_widget.h"
#include "wds.h"
#include "ai_player_controller.h"

#include <cassert>

constexpr auto NUM_HEROES = 19u;

const char* hero_list[NUM_HEROES] = {
        "ultimate_spiderman",
        "arachno_man_costume",
        "usm_wrestling_costume",
        "usm_blacksuit_costume",
        "peter_parker",
        "peter_parker_costume",
        "peter_hooded",
        "peter_hooded_costume",
        "venom",
        "venom_spider",
        "carnage",
        "rhino",
        "electro_suit",
        "electro_nosuit",
        "green_goblin",
        "silver_sable",
        "mary_jane",
        "wolverine",
        "beetle"
};

enum class hero_status_e {
    UNDEFINED = 0,
    REMOVE_PLAYER = 1,
    ADD_PLAYER = 2,
    CHANGE_HEALTH_TYPE = 3,
} hero_status;

int hero_selected;
int frames_to_skip = 2;

struct level_descriptor_t
{
    fixedstring<32> field_0;
    fixedstring<64> field_20;
    fixedstring<16> field_60;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    int field_88;
    int field_8C;
};

VALIDATE_SIZE(level_descriptor_t, 0x90);

level_descriptor_t *get_level_descriptors(int *arg0)
{
    auto *game_partition = resource_manager::get_partition_pointer(0);
    assert(game_partition != nullptr);

    assert(game_partition->get_pack_slots().size() == 1);

    auto &v2 = game_partition->get_pack_slots();
    auto *game_slot = v2.front();
    assert(game_slot != nullptr);

    auto v6 = 9;
    string_hash v5 {"level"};
    resource_key a1 {v5, v6};
    int a2 = 0;
    auto *v11 = (level_descriptor_t *) game_slot->get_resource(a1, &a2, nullptr);

    if ( arg0 != nullptr )
    {
        *arg0 = a2 / sizeof(level_descriptor_t);
    }

    return v11;
}

void level_select_handler(debug_menu_entry *entry)
{
    auto *v1 = entry->text;
    mString v15 {v1};

    int arg0;
    auto *v13 = get_level_descriptors(&arg0);
    for ( auto i = 0; i < arg0; ++i )
    {
        auto *v2 = v15.c_str();
        fixedstring<16> v6 {v2};
        if ( v13[i].field_60 == v6 )
        {
            auto *v3 = v13[i].field_0.to_string();
            v15 = {v3};
            break;
        }
    }

    g_game_ptr()->load_new_level(v15, -1);
}


struct reboot_t {
    std::string field_0;
    const char* field_C;
    int field_10;
    int field_14;
};

std::vector<reboot_t> menu_reboot; 

void reboot_handler(debug_menu_entry* a1)
{
    auto v1 = (int)a1->m_id;
    auto v7 = &menu_reboot.at(v1);
    auto v6 = v7->field_C;
    auto v5 = v7->field_14;
    auto* v4 = v7->field_0.c_str();
    auto v3 = v7->field_10;
    auto* v2 = mission_manager::s_inst();
    v2->force_mission(v3, v4, v5, v6);
    close_debug();
}

void handle_hero_select_menu(debug_menu_entry *entry, custom_key_type)
{
    entry->m_game_flags_handler(entry);
}

void hero_entry_callback(debug_menu_entry *);

void hero_toggle_handler(debug_menu_entry *entry);



void populate_level_select_menu(debug_menu_entry* entry)
{
    // assert(debug_menu::root_menu != nullptr);

    auto* head_menu = create_menu("Level Select");
    entry->set_submenu(head_menu);

    auto* hero_select_menu = create_menu("Hero Select");
    debug_menu_entry v28 { hero_select_menu };

    head_menu->add_entry(&v28);
    for (auto i = 0u; i < 19u; ++i) {
        auto v6 = 25;
        string_hash v5 { (hero_list)[i] };
        auto v11 = resource_key { v5, v6 };
        auto v30 = resource_manager::get_pack_file_stats(v11, nullptr, nullptr, nullptr);
        if (v30) {
            mString v35 { hero_list[i] };
            debug_menu_entry v37 { v35.c_str() };
                v37.set_game_flags_handler(hero_toggle_handler);
                v37.m_id = i;
                v37.set_frame_advance_cb(hero_entry_callback);
                hero_select_menu->add_entry(&v37);
            }
            }


    mString v26 { "city" };
    debug_menu_entry v39 { v26.c_str() };

    v39.set_game_flags_handler(level_select_handler);

        head_menu->add_entry(&v39);

        const mString& v27 { "characterb" };

    debug_menu_entry v41 { v27.c_str() };

    v41.set_game_flags_handler(level_select_handler);


    head_menu->add_entry(&v41);

    mString v25 { "-- REBOOT --" };
    debug_menu_entry v40 { v25.c_str() };

    v40.set_game_flags_handler(reboot_handler);

    head_menu->add_entry(&v40);
}

void create_level_select_menu(debug_menu* parent)
{
    auto* level_select_menu = create_menu("Level Select", debug_menu::sort_mode_t::undefined);
    auto* v2 = create_menu_entry(level_select_menu);
    v2->set_game_flags_handler(populate_level_select_menu);
    parent->add_entry(v2);
}

struct debug_menu_entry;

void hero_toggle_handler(debug_menu_entry *entry)
{
    printf("hero_toggle_handler\n");
    assert(entry->get_id() < NUM_HEROES);
    hero_selected = entry->get_id();
    hero_status = hero_status_e::REMOVE_PLAYER;
}

void hero_entry_callback(debug_menu_entry *)
{
    printf("hero_entry_callback: hero_status = %d\n", hero_status);

    auto v18 = g_world_ptr()->num_players;
    switch ( hero_status )
    {
    case hero_status_e::REMOVE_PLAYER:
    {
        g_world_ptr()->remove_player(v18 - 1);
        hero_status = hero_status_e::ADD_PLAYER;
        frames_to_skip = 2;
        g_game_ptr()->enable_marky_cam(true, true, -1000.0, 0.0);
        break;
    }
    case hero_status_e::ADD_PLAYER:
    {
        auto v1 = frames_to_skip--;
        if ( v1 <= 0 )
        {
            assert(hero_selected > -1 && hero_selected < NUM_HEROES);

            [[maybe_unused]] auto v2 = g_world_ptr()->add_player(mString {hero_list[hero_selected]});

            /*
            auto v10 = v2 <= v18;

            assert(v10 && "Cannot add another_player");
            */
               
            g_game_ptr()->enable_marky_cam(false, true, -1000.0, 0.0);
            frames_to_skip = 2;
            hero_status = hero_status_e::CHANGE_HEALTH_TYPE;
        }
        break;
    }
    case hero_status_e::CHANGE_HEALTH_TYPE: {
        auto v3 = frames_to_skip--;
        if ( v3 <= 0 )
        {
            auto v17 = 0;
            auto *v5 = (actor *) g_world_ptr()->get_hero_ptr(0);
            auto *v6 = v5->get_player_controller();
            auto v9 = v6->field_420;
            switch ( v9 )
            {
            case 1:
                v17 = 0;
                break;
            case 2:
                v17 = 4;
                break;
            case 3:
                v17 = 5;
                break;
            }

            auto *v7 = g_world_ptr()->get_hero_ptr(0);
            auto v8 = v7->my_handle;
            g_femanager().IGO->hero_health->SetType(v17, v8.field_0);
            g_femanager().IGO->hero_health->SetShown(true);
            close_debug();
            hero_status = hero_status_e::UNDEFINED;
        }
        break;
    }
    default:
        break;
    }
}
