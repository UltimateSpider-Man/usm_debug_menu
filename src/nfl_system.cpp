
#include "nfl_system.h"

#include "func_wrapper.h"

#include "trace.h"

nflFileID nflSystem::openFile(nflMediaID a1, const char* a2, nfdFileFlags Flags, uint32_t* p_fileSize)
{

    return (nflFileID)CDECL_CALL(0x0079E180, a1, a2, Flags, p_fileSize);
}

nflFileID nflSystem::nflOpenFile(nflMediaID a1, const char* a2)
{
    return nflFileID();
}

nflFileID nflOpenFile(nflMediaID a1, const char *a2) {
    TRACE("nflOpenFile");

    auto result = nflSystem::openFile(a1, a2, NFD_FILE_FLAGS_READ, nullptr);
    return result;
}
