#pragma once


#include "debug_menu.h"
#include <iostream>
#include <string>
#include <map>
#include <cassert>

struct debug_variable_t {
    std::string field_0;


    std::map<std::string, std::string> g_dvars;

    void add_value(const std::string& a1)
    {
        auto it = g_dvars.find(this->field_0);
        if (it == g_dvars.end()) {
            std::pair<std::string, std::string> v3 { this->field_0, a1 };
            g_dvars.insert(v3);
        }
    }

    const std::string& get_value() const
    {
        auto a1 = g_dvars.find(this->field_0);

        auto end = g_dvars.end();
        if (a1 == end) {
            assert("Uninitialized dvar" && 0);
        }

        return a1->second;
    }

    operator float() const
    {
        const std::string& value = get_value();
        return std::stof(value);
    }

    debug_variable_t(const char* a1, float a2)
        : field_0(a1)
    {
        std::string val { "a2" };
        this->add_value(val);
    }



};

