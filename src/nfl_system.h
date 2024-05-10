#pragma once
#include <cstdint>

struct nflFileID {
    int field_0;

    nflFileID() = default;

    constexpr nflFileID(int a1) : field_0(a1) {}

    bool operator==(const nflFileID &id) const
    {
        return field_0 == id.field_0;
    }

    bool operator!=(const nflFileID &id) const
    {
        return !(field_0 == id.field_0);
    }
};

enum nfdFileFlags
{
    NFD_FILE_FLAGS_READ = 0x1,
    NFD_FILE_FLAGS_WRITE = 0x2,
    NFD_FILE_FLAGS_CREATE = 0x4,
    NFD_FILE_FLAGS_UNDEFINED
};

inline constexpr nflFileID NFL_FILE_ID_INVALID {-1};


struct nflMediaID {
    int field_0;

    nflMediaID()
    {
        field_0 = 0;
    }

    nflMediaID(int a1)
    {
        field_0 = a1;
    }
};

namespace nflSystem {
//0x0079E180
nflFileID openFile(nflMediaID a1, const char *a2, nfdFileFlags a3, uint32_t *a4);


nflFileID nflOpenFile(nflMediaID a1, const char* a2);

};