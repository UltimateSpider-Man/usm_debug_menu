#pragma once

#include "mstring.h"
#include "utility.h"

#include <cstdint>
#include <windows.h>

struct os_file {
    enum mode_flags
    {
        FILE_READ = 1,
        FILE_WRITE = 2,
        FILE_MODIFY = 3,
        FILE_APPEND = 4
    };

    enum filepos_t {
        FP_BEGIN,
        FP_CURRENT,
        FP_END
    };

    mString m_path;
    uint32_t flags;
    bool opened;
    bool field_15;

    HANDLE io;

    uint32_t field_1C;
    uint32_t m_fileSize;
    bool field_24;
    uint32_t m_offset;
    uint32_t field_2C;
    uint32_t field_30;

        // 0x0058DEA0
    os_file()
    {
        void(__fastcall * func)(void*, void*) = CAST(func, 0x0058DEA0);
        func(this, nullptr);
    }

        // 0x0059EAA0
    explicit os_file(const mString& a2, int dwShareMode)
    {
        void(__fastcall * func)(void*, void*, const mString*, int) = CAST(func, 0x0059EAA0);
        func(this, nullptr, &a2, dwShareMode);
    }

    int write(const void* lpBuffer, int nNumberOfBytesToWrite)
    {
        int(__fastcall * func)(void*, void*, const void*, int) = CAST(func, 0x00598C30);
        return func(this, nullptr, lpBuffer, nNumberOfBytesToWrite);
    }

    bool is_open() const
    {
        return opened;
    }

    // 0x0059B6F0
    ~os_file()
    {
        void(__fastcall * func)(void*, void*) = CAST(func, 0x0059B6F0);
        func(this, nullptr);
    }


    void sub_58DEF0()
    {
        void(__fastcall * func)(void*, void*) = CAST(func, 0x0058DEF0);
        func(this, nullptr);
    }

    size_t sub_58DF50()
    {
        void(__fastcall * func)(void*, void*) = CAST(func, 0x0058DF50);
        func(this, nullptr);
    }

    // 0x0058DF90
    int get_size()
    {
        void(__fastcall * func)(void*, void*) = CAST(func, 0x0058DF90);
        func(this, nullptr);
    }

    // 0x0059B740
    void open(const mString& path, int shareMode)
    {
        void(__fastcall * func)(void*, void*, const mString&, int) = CAST(func, 0x0059B740);
        func(this, nullptr, path, shareMode);
    }


    // 0x00598AD0
    int read(LPVOID data, int bytes)
    {
        void(__fastcall * func)(void*, void*, LPVOID, int) = CAST(func, 0x00598AD0);
        func(this, nullptr, data, bytes);

        return 0;
    }

    // 0x0058E020
    void set_fp(uint32_t lDistanceToMove, filepos_t a3)
    {
        void(__fastcall * func)(void*, void*, uint32_t, filepos_t) = CAST(func, 0x0058E020);
        func(this, nullptr, lDistanceToMove, a3);
    }

    // 0x00598A60
    void close()
    {
        void(__fastcall * func)(void*, void*) = CAST(func, 0x00598A60);
        func(this, nullptr);
    }

    static Var<bool> system_locked;
};
   

