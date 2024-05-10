#pragma once

#include "func_wrapper.h"
#include "resource_key.h"

#include "resource_amalgapak_header.h"

#include "nlPlatformEnum.h"

#include "mstring.h"
#include "resource_pack_location.h"

#include <vector>



#include "nfl_system.h"

#include "memory.h"
#include "common.h"
#include "func_wrapper.h"
#include "log.h"


#include "utility.h"
#include "variable.h"

#include <cassert>
#include <numeric>

#include "trace.h"
#include "os_file.h"
#include "nfl_system.h"
using namespace nflSystem;

struct resource_partition;
struct resource_pack_location;
struct resource_pack_slot;
struct mString;
struct nflFileID;

     struct resource_memory_map {
    char field_0;
    int field_4;
    int field_8;
    int field_C;
    struct {
        int field_0;
        int field_4;
        int field_8;
        int field_C;
    } field_10[8];

    resource_memory_map()
    {
        this->field_0 = 0;
        std::memset(this->field_10, 0, sizeof(this->field_10));
    }
};

     using modified_callback_t = void (*)(std::vector<resource_key> &a1);

     static inline Var<std::vector<modified_callback_t>> resource_pack_modified_callbacks { 0x0095CAC4 };

     inline     Var<mString> amalgapak_name { 0x0095CAD4 };

inline Var<_nlPlatformEnum> g_platform { 0 };

inline Var<std::vector<resource_partition*>*> partitions { 0x0095C7F0 };

inline Var<std::vector<resource_pack_slot*>> resource_context_stack { 0x0096015C };







inline Var<int> amalgapak_base_offset { 0x00921CB4 };

inline Var<nflFileID> amalgapak_id { 0x00921CB8 };

inline Var<int> resource_buffer_used { 0x0095C180 };

inline Var<int> memory_maps_count { 0x0095C7F4 };

inline Var<size_t> resource_buffer_size { 0x0095C1C8 };

inline Var<int> in_use_memory_map { 0x00921CB0 };

inline Var<uint8_t*> resource_buffer { 0x0095C738 };

inline Var<bool> using_amalga { 0x0095C800 };

inline Var<int> amalgapak_signature { 0x0095C804 };

inline Var<resource_memory_map*> memory_maps { 0x0095C2F0 };

inline Var<int> amalgapak_pack_location_count { 0x0095C7FC };

inline Var<resource_pack_location*> amalgapak_pack_location_table { 0x0095C7F8 };

inline Var<int> amalgapak_prerequisite_count { 0x0095C174 };

inline Var<resource_key*> amalgapak_prerequisite_table { 0x0095C300 };

namespace resource_manager {



    inline bool can_reload_amalgapak()
    {
        return (bool) CDECL_CALL(0x0053DE90);
    }

      inline mString get_amalgapak_filename(_nlPlatformEnum arg4)
    {
        const char* a2[] = { ".PAK", "_XB.PAK", "_GC.PAK", "_PC.PAK" };

#ifdef TARGET_XBOX
        mString v1 { a2[1] };
#else
        mString v1 { a2[arg4] };
#endif

        mString v2 { "packs\\amalga2" };

        mString res = v2 + v1;

        return res;
    }

       inline void load_amalgapak()
    {
        CDECL_CALL(0x00537650);
    }

     inline bool using_amalgapak()
    {
        return using_amalga();
    }





  inline  void load_amalgapak_from_game()
    {
        TRACE("resource_manager::load_amalgapak");

        if constexpr (1) {
            os_file file;

            {
                amalgapak_name() = get_amalgapak_filename(g_platform());
                printf("Loading amalgapak...");

                mString a1 { amalgapak_name().c_str() };

                file.open(a1, os_file::FILE_READ);
            }

            if (!file.is_open()) {
                auto* v1 = amalgapak_name().c_str();
                printf("Could not open amalgapak file %s!", v1);
                assert(0);
            }

            resource_amalgapak_header pack_file_header {};
            file.read(&pack_file_header, sizeof(resource_amalgapak_header));

            {
                mString a1 { amalgapak_name().c_str() };

                pack_file_header.verify(a1);
            }

            if constexpr (0) {
                pack_file_header.field_18 = 0;


                       amalgapak_base_offset() = pack_file_header.field_18;
                using_amalga() = (pack_file_header.field_18 != 0);
                amalgapak_signature() = pack_file_header.field_14;
                amalgapak_pack_location_count() = pack_file_header.location_table_size / sizeof(resource_pack_location);

                amalgapak_pack_location_table() = static_cast<resource_pack_location*>(
                    arch_memalign(16u, pack_file_header.location_table_size));
                assert(amalgapak_pack_location_table() != nullptr);

                file.set_fp(pack_file_header.field_1C, os_file::FP_BEGIN);
                auto how_many_did_we_get = file.read(amalgapak_pack_location_table(),
                    pack_file_header.location_table_size);
                assert(how_many_did_we_get == pack_file_header.location_table_size);

                amalgapak_prerequisite_count() = static_cast<uint32_t>(
                                                     pack_file_header.prerequisite_table_size)
                    >> 3;

                amalgapak_prerequisite_table() = static_cast<resource_key*>(
                    arch_memalign(8u, pack_file_header.prerequisite_table_size));
                assert(amalgapak_prerequisite_table() != nullptr);

                file.set_fp(pack_file_header.field_2C, os_file::FP_BEGIN);
                how_many_did_we_get = file.read(amalgapak_prerequisite_table(),
                    pack_file_header.prerequisite_table_size);
                assert(how_many_did_we_get == pack_file_header.prerequisite_table_size);

                resource_buffer_size() = pack_file_header.field_34;
                assert(pack_file_header.memory_map_table_size % sizeof(resource_memory_map) == 0);

                memory_maps_count() = pack_file_header.memory_map_table_size / sizeof(resource_memory_map);

                memory_maps() = new resource_memory_map[memory_maps_count()];
                file.set_fp(pack_file_header.field_24, os_file::FP_BEGIN);
                how_many_did_we_get = file.read(memory_maps(), pack_file_header.memory_map_table_size);
                assert(how_many_did_we_get == pack_file_header.memory_map_table_size);

                file.close();

                if (using_amalgapak()) {
                    amalgapak_id() = nflOpenFile({ 1 }, amalgapak_name().c_str());

                    if (amalgapak_id() == NFL_FILE_ID_INVALID) {
                        amalgapak_id() = nflOpenFile({ 2 }, amalgapak_name().c_str());

                        if (amalgapak_id() == NFL_FILE_ID_INVALID) {
                            mString v12 { amalgapak_name().c_str() };
                            mString v13 { "data\\" };

                            mString a1 = v13 + v12;

                            amalgapak_id() = nflOpenFile({ 2 }, a1.c_str());
                        }
                    }

                    printf("Using amalgapak found on the HOST");
                } else {
                    printf("Using amalgapak found on the CD");
                }

                if constexpr (0) {
                    printf("amalgapak_base_offset = 0x%08X\n", amalgapak_base_offset());

                    std::for_each(amalgapak_pack_location_table(),
                        amalgapak_pack_location_table() + amalgapak_prerequisite_count(),
                        [](auto& pack_loc) {
                            auto& key = pack_loc.loc.field_0;
                            {
                                printf("%s %s 0x%08X %d\n",
                                    key.get_platform_name(g_platform()).c_str(),
                                    pack_loc.m_name,
                                    pack_loc.loc.m_offset,
                                    pack_loc.loc.m_size);
                                assert(to_hash(pack_loc.m_name) == key.m_hash.source_hash_code);
                                // pack_loc.loc.m_offset = 0u;
                            }
                        });

                    assert(0);
                }

            } else {
                CDECL_CALL(0x00537650);
            }
        }
            }


                inline void reload_amalgapak_from_game()
            {
                TRACE("resource_manager::reload_amalgapak");

                if constexpr (1) {
                    assert(!using_amalgapak());

                    assert(amalgapak_pack_location_table() != nullptr);

                    assert(amalgapak_prerequisite_table() != nullptr);

                    assert(memory_maps() != nullptr);

                    mem_freealign(amalgapak_prerequisite_table());
                    mem_freealign(amalgapak_pack_location_table());
                    delete[] (memory_maps());
                    amalgapak_prerequisite_table() = nullptr;
                    amalgapak_pack_location_table() = nullptr;
                    memory_maps() = nullptr;
                    load_amalgapak_from_game();

                    std::vector<resource_key> v3;
                    for (auto i = 0; i < amalgapak_pack_location_count(); ++i) {
                        if (amalgapak_pack_location_table()[i].field_2C != 0) {
                            v3.push_back(amalgapak_pack_location_table()[i].loc.field_0);
                        }
                    }

                    for (auto& cb : resource_pack_modified_callbacks()) {
                        (*cb)(v3);
                    }
                } else {
                    CDECL_CALL(0x0054C2E0);
                }
            }
         inline   void reload_amalgapak()

                {
                CDECL_CALL(0x0054C2E0);
            }

    inline bool get_pack_file_stats(const resource_key &a1,
                                    resource_pack_location *a2,
                                    mString *a3,
                                    int *a4)
    {
        return (bool) CDECL_CALL(0x0052A820, &a1, a2, a3, a4);
    }

    inline resource_pack_slot *push_resource_context(resource_pack_slot *pack_slot) {
        return (resource_pack_slot *) CDECL_CALL(0x00542740, pack_slot);
    }

    inline resource_pack_slot *pop_resource_context() {
        return (resource_pack_slot *) CDECL_CALL(0x00537530);
    }

    inline void set_active_district(bool a1)
    {
        void (__fastcall *func)(void *, int, bool) = (decltype(func)) 0x00573620;
        func(nullptr, 0, a1);
    }

 

    inline resource_partition *get_partition_pointer(int which_type) {
        return (resource_partition *) CDECL_CALL(0x00537AA0, which_type);
    }


}


