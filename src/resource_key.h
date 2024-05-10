#pragma once

#include "func_wrapper.h"
#include "string_hash.h"


struct resource_key
{
    string_hash field_0;
    int field_4;
};

inline resource_key create_resource_key_from_path(const char *in_string, int a3)
{
    resource_key key;
    CDECL_CALL(0x004217B0, &key, in_string, a3);

    return key;
}
