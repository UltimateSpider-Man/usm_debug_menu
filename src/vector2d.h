#pragma once

#include "float.hpp"

struct vector2d {
    float arr[2];

    const float &operator[](int idx) const {
        return arr[idx];
    }

    float &operator[](int idx) {
        return arr[idx];
    }

    const char *to_string() const;

    float length2() const;

    float length() const;
};
