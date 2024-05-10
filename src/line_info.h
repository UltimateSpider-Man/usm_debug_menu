#pragma once

#include "entity.h"
#include "entity_base_vhandle.h"
#include "variable.h"
#include "vector3d.h"

struct line_info_local_query {};

struct line_info {
    vector3d field_0;
    vector3d field_C;
    vector3d hit_pos;
    vector3d hit_norm;
    vector3d field_30;
    vector3d field_3C;
    bool collision;
    bool field_59;
    bool queued_for_collision_check;
    bool field_5C;



};

#ifndef TEST_CASE
int num_debug_line_info[2] {};

extern std::array<line_info[64], 2> debug_line_info;





#endif

//0x0068A9D0
extern bool is_noncrawlable_surface(line_info &a1);

extern void line_info_patch();
