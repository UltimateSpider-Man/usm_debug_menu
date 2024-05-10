#pragma once

#include "input_device.h"
#include "mstring.h"

struct pc_joypad_device : input_device {

    int field_8;

    pc_joypad_device();

    // virtual
    mString get_name() const;

    void clear();

    void initialize(int a2);

    // virtual
    void clear_state();

    // virtual
    float get_axis_state(int axis, int);

    float get_axis_old_state(int a2, int a3);

    float get_axis_delta(int axis, int a3);

    void poll();

    bool is_connected() const;

    bool is_vibrator_present() const;

    static pc_joypad_device* instance;
};


