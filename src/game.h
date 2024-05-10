#pragma once

#include "fetext.h"
#include "variable.h"
#include "common.h"
#include "os_developer_options.h"
#include "entity_handle_manager.h"
#include "vector2di.h"
#include "memory.h"
#include "ngl.h"
#include "entity.h"
#include "physical_interface.h"
#include "po.h"
#include "region.h"
#include "terrain.h"
#include "utility.h"
#include "wds.h"

struct game_process
{
    const char *field_0;
    int *field_4;
    int index;
    int num_states;
    int field_10;
    bool field_14;
};

inline Var<game_process> lores_game_process{0x00922074};

struct game_settings;
struct message_board;
struct level_descriptor_t;

    struct game {
    char field_0[0x5C];
    entity* field_5C;
    entity* current_game_camera;
    void* field_64;
    message_board* mb;
    struct {
        int field_0;
        game_process* m_first;
        game_process* m_last;
        game_process* m_end;

        auto& back()
        {
            return *(m_last - 1);
        }
    } process_stack;

    int field_7C[17];
    game_settings* gamefile;
    int field_C4[41];

    struct flag_t {
        bool level_is_loaded;
        bool single_step;
        bool physics_enabled;
        bool field_3;
        bool game_paused;
    } flag;
    bool field_16D;
    bool field_16E;
    bool m_hero_start_enabled;
    bool field_170;
    bool field_171;
    bool field_172;
    char empty5[253];
    int field_270;
    int field_274;
    float field_278;
    int field_27C;
    int field_280;
    float field_284;
    int field_288;
    float field_28C;
    bool field_2B4;
    bool field_2B5;
    int field_2B8;
    int field_2BC;
    bool field_15C;
    bool field_15D;
    bool field_15E;
    bool field_15F;
    bool field_160;
    bool field_167;
    float field_290;
    world_dynamics_system* the_world;


        struct level_load_stuff {
        level_descriptor_t* descriptor;
        mString name_mission_table;
        mString field_14;
        vector3d field_24;
        int field_30;
        bool load_widgets_created;
        bool load_completed;
        bool field_3A;
        bool field_3B;

        void reset_level_load_data()
        {
            this->descriptor = nullptr;
            this->field_30 = 0;
            this->load_completed = false;
            this->field_3A = false;
            this->load_widgets_created = false;
        }
    };

    game_settings *get_game_settings() {
        assert(gamefile != nullptr);

        return this->gamefile;
    }

    void enable_user_camera(bool a2) {
        this->field_172 = a2;
    }

    bool is_user_camera_enabled() const {
        return this->field_172;
    }

    void set_camera(int camera_state);

    void enable_physics(bool a2)
    {
        void (__fastcall *func)(void*, int, bool) = (decltype(func)) 0x00515230;
        func(this, 0, a2);
    }

    void message_board_init();

    void enable_marky_cam(bool a2, bool a3, Float a4, Float a5)
    {
        void (__fastcall *func)(void *, void *, bool, bool, Float, Float) = bit_cast<decltype(func)>(0x005241E0);

        func(this, nullptr, a2, a3, a4, a5);
    }

    void push_process(game_process &process) {
        void (__fastcall *sub_570FD0)(void *, int, void *) = (decltype(sub_570FD0)) 0x00570FD0;

        sub_570FD0(&this->process_stack, 0, &process);

        auto &last_proc = this->process_stack.back();
        last_proc.index = 0;
        last_proc.field_10 = 0;
    }

    void push_lores()
    {
        this->push_process(lores_game_process());
    }

    void load_new_level(const mString& a1, int a2)
    {


        
    void(__fastcall * func)(void*, void*, const mString*,int) = CAST(func, 0x00514C70);
    return func(this, nullptr,&a1, a2);

    this->load_this_level();
    level_load_stuff*  reset_load_level_data();
    }

        void load_this_level()
    {

        void(__fastcall * func)(void*, void*) = CAST(func, 0x0055C6E0);
        return func(this, nullptr);
    }

    void begin_hires_screenshot(int a2, int a3)
    {
        void (__fastcall *func)(void *, void *, int, int) = (decltype(func)) 0x00548C10;
        func(this, nullptr, a2, a3);
    }

    mString get_hero_info();

    mString get_camera_info();

    mString get_analyzer_info();

    void show_debug_info();

    void frame_advance_level(Float time_inc);
};

inline Var<game *> g_game_ptr{0x009682E0};

inline Var<int> g_TOD { 0x0091E000 };

extern void game_patch();

