#include "wds_render_manager.h"


#include "line_info.h"
#include "city_lod.h"

#include "vector2d.h"
#include "debug_render.h"
#include "func_wrapper.h"
#include "game.h"
#include "geometry_manager.h"
#include "ngl_mesh.h"

#include "region.h"

#include "trace.h"
#include "wds.h"
#include "terrain.h"
#include "vector2di.h"
#include "utility.h"
#include "physical_interface.h"
#include "os_developer_options.h"

#include "common.h"

#include <cassert>
#include <cmath>

VALIDATE_SIZE(wds_render_manager, 156u);

struct traversed_entity {
    entity_base_vhandle m_handle;
    int field_4;
};
static Var<fixed_vector<traversed_entity, 750> *> traversed_entities_last_frame {0x0095C7B4};

wds_render_manager::wds_render_manager() {
    this->field_30.sub_56FCB0();

    
    this->field_94 = nullptr;
    this->field_98 = 0;

    this->field_10[0] = 0.30000001f;
    this->field_10[1] = -1.0f;
    this->field_10[2] = 0.2f;
    this->field_10[3] = 0;

    this->field_20[0] = 0.80000001f;
    this->field_20[1] = 0.80000001f;
    this->field_20[2] = 0.85000002f;
    this->field_20[3] = 1.0f;

    this->field_60 = {0, 0, 0, 1};

    this->field_90 = 1.0f;
    this->field_5C = nullptr;
    this->field_8C = 0;
    this->field_84 = 175.0f;
    this->field_88 = 250.0f;
}


void show_terrain_info()
{
    if ( g_world_ptr() != nullptr )
    {
        auto *v0 = g_world_ptr()->get_hero_ptr(0);
        if ( v0 != nullptr )
        {
            auto *v8 = g_world_ptr()->get_hero_ptr(0);
            if ( v8->has_physical_ifc() )
            {
                auto *v3 = g_world_ptr()->get_hero_ptr(0);
                auto *v4 = v3->physical_ifc();

                string_hash v17;
                v4->get_parent_terrain_type(&v17);

                vector2d v5{512.0, 32.0};
                vector2di v14 {v5};

                auto *v6 = v17.to_string();
                mString v16 {v6};
                color32 v7{255, 255, 255, 255};
                render_text(v16, v14, v7, 1.0, 1.0);
            }
        }
    }
}



void wds_render_manager::debug_render()
{
    TRACE("wds_render_manager::debug_render");

    if constexpr (1) {

        if (os_developer_options::instance()->get_flag(mString{"SHOW_TERRAIN_INFO"}))
        {
            show_terrain_info();
        }

        if ( debug_render_get_ival((debug_render_items_e)20) || os_developer_options::instance()->get_flag(mString {"SHOW_GLASS_HOUSE"}))
        {
            //glass_house_manager::show_glass_houses();
        }

        //if ( debug_render_get_ival((debug_render_items_e)21) || SHOW_OBBS || SHOW_DISTRICTS )
        {
            auto *ter= g_world_ptr()->get_the_terrain();
            ter->show_obbs();
        }

        render_debug_spheres();

    }
}





static constexpr auto g_projected_fov_multiplier = 0.80000001f;


#include "debug_menu.h"

void wds_render_manager::render(camera &a2, int a3)
{
    TRACE("wds_render_manager::render");

    assert(this->field_94 != nullptr);

    CDECL_CALL(0x0054B250, this, &a2, a3);

    //_populate_missions();

    if ( debug_render_get_bval(OCCLUSION) )
    {
    }

    this->debug_render();
}

void render_data::sub_56FCB0() {
    CDECL_CALL(0x0056FCB0, this);
}

void wds_render_manager::frame_advance(Float a2) {
    TRACE("wds_render_manager::frame_advance");

    CDECL_CALL(0x0054ADE0, this, a2);
}

void wds_render_manager::render_stencil_shadows(const camera &a2)
{
    TRACE("wds_render_manager::render_stencil_shadows");
    
    CDECL_CALL(0x0053D5E0, this, &a2);
}

void wds_render_manager::build_render_data_regions(render_data *arg0, camera *arg4)
{
    TRACE("wds_render_manager::build_render_data_regions");

    CDECL_CALL(0x00547000, this, arg0, arg4);
}

void wds_render_manager::build_render_data_ents(render_data *a2, camera *a3, int a4)
{
    TRACE("wds_render_manager::build_render_data_ents");

    CDECL_CALL(0x00547250, this, a2, a3, a4);
}

void wds_render_manager::sub_53D560(const camera *a2)
{
    TRACE("wds_render_manager::sub_53D560");

    CDECL_CALL(0x0053D560, this, a2);
}

