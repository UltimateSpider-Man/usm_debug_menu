#pragma once

#include "func_wrapper.h"


#include "utility.h"
#include "wds.h"

#include <cstdarg>
#include <cstdio>



struct mString
{
    struct fmtd {
        int value;
    };

    int field_0;
    int m_size;
    const char *guts;
    void* field_C;

    mString()
    {
        void (__fastcall *func)(void *) = bit_cast<decltype(func)>(0x00420F00);
        func(this);
    }

    mString(const mString &a2)
    {
        void (__fastcall *func)(void *, int, const mString *) = bit_cast<decltype(func)>(0x00421220);
        func(this, 0, &a2);
    }

    mString(float a2)
    {
        void(__fastcall * func)(void*, int, float) = bit_cast<decltype(func)>(0x00421220);
        func(this, 0, a2);
    }

    mString(int , const char *Format, ...)
    {
        char Dest[1024];
        va_list Args;

        va_start(Args, Format);
        vsprintf(Dest, Format, Args);
        CDECL_CALL(0x00420F60, this, 0, Dest);
    }

    mString(const char *str)
    {
        typedef int (__fastcall* mString_constructor_ptr)(mString* , void* edx, const char* str);
        mString_constructor_ptr mString_constructor = (mString_constructor_ptr) 0x00421100;
        mString_constructor(this, 0, str);
    }

    ~mString()
    {
        typedef int (__fastcall* mString_finalize_ptr)(mString* , void* edx, int zero);
        mString_finalize_ptr mString_finalize = (mString_finalize_ptr) 0x004209C0;

        mString_finalize(this, 0, 0);
    }

    mString &operator=(const mString &a2)
    {
        if (this != &a2)
        {
            this->update_guts(a2.c_str(), a2.m_size);
        }

        return (*this);
    }

    mString &operator=(const char *a2)
    {
        this->update_guts(a2, -1);
        return (*this);
    }

    int length() const {
        return this->m_size;
    }

    void update_guts(const char* a2, signed int a3) {

        typedef void(__fastcall* mString_update_guts_ptr)(void *, void* edx, const char* a2, signed int a3);
        mString_update_guts_ptr mString_update_guts = (mString_update_guts_ptr) 0x41F9D0;

        //printf("mString:%s\n", a2);


        return mString_update_guts(this, 0, a2, a3);
    }

    const char *c_str() const
    {
        return guts;
    }

    void append(const char *from_string, size_t Count)
    {
        void (__fastcall *func)(void *, int, const char *, unsigned int) = bit_cast<decltype(func)>(0x0041FAB0);
        func(this, 0, from_string, Count);
    }

    mString &operator+=(const mString &a1)
    {
        this->append(a1.c_str(), -1);
        return (*this); 
    }

    friend mString operator+(const char *a2, const mString &a3)
    {
        mString result;
        CDECL_CALL(0x00421410, &result, a2, &a3);
        return result;
    }

    friend mString operator+(const mString &a2, const mString &a3)
    {
        mString result;
        CDECL_CALL(0x00421330, &result, &a2, &a3);
        return result;
    }

        double atof(const char* i) const;

    double to_float() const
    {
        return atof(this->guts);
    }

    mString*  sub_67086F(void*, const char* a2, char* a1)
    {

    }
    inline void set_size(size_t size)
    {
        this->m_size = size;
    }
    static inline Var<char*> null { 0x0091E7C0 };


    static inline Var<int> mString_count { 0x00957CEC };


    mString([[maybe_unused]] mString::fmtd fmt, const char* Format, ...)
    {
        char Dest[1024];
        va_list Args;

        va_start(Args, Format);
        this->set_size(0);
        this->field_0 = 0;
        vsprintf(Dest, Format, Args);

        this->guts = (char*)mString::null();
        ++mString_count();

        this->field_C = nullptr;
        this->update_guts(Dest, -1);
    }

};


