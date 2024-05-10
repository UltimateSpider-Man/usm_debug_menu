#include "pc_joypad_device.h"

#include "game.h"
#include "input.h"

#include "gamepadinput.h"
#include "trace.h"
#include "utility.h"

#include <optional>


pc_joypad_device::pc_joypad_device()
{
    using vtbl_t = std::decay_t<decltype(*m_vtbl)>;
    Var<vtbl_t> tmp { 0x0088EA80 };
    static vtbl_t vtbl = tmp();

    this->m_vtbl = &vtbl;
    this->field_4 = INVALID_DEVICE_ID;

    {
        auto address = func_address(&pc_joypad_device::clear_state);
        this->m_vtbl->clear_state = CAST(this->m_vtbl->clear_state, address);
    }

    {
        auto address = func_address(&pc_joypad_device::get_axis_state);
        this->m_vtbl->get_axis_state = CAST(this->m_vtbl->get_axis_state, address);
    }

    {
        auto address = func_address(&pc_joypad_device::get_axis_old_state);
        this->m_vtbl->get_axis_old_state = CAST(this->m_vtbl->get_axis_old_state, address);
    }

    {
        auto address = func_address(&pc_joypad_device::get_axis_delta);
        this->m_vtbl->get_axis_delta = CAST(this->m_vtbl->get_axis_delta, address);
    }

    {
        auto address = func_address(&pc_joypad_device::poll);
        this->m_vtbl->poll = CAST(this->m_vtbl->poll, address);
    }

    {
        auto address = func_address(&pc_joypad_device::is_connected);
        this->m_vtbl->is_connected = CAST(this->m_vtbl->is_connected, address);
    }
}

static pc_joypad_device g_gamepad {};

pc_joypad_device* pc_joypad_device::instance = &g_gamepad;



void pc_joypad_device::clear()
{
    this->field_4 = INVALID_DEVICE_ID;
}

void pc_joypad_device::initialize(int a2)
{
    this->field_4 = 0xF4247;
    this->field_8 = a2;
}

mString pc_joypad_device::get_name() const
{
    mString a1 { "USB GamePad" };
    return a1;
}

void pc_joypad_device::clear_state()
{
    ;
}

float pc_joypad_device::get_axis_state(int axis, int a3)
{
    TRACE("pc_joypad_device::get_axis_state");

    printf("axis = %d, %d\n", axis, a3);

    if (Input::instance() != nullptr) {
        static uint16_t gamepad_codes[Gamepad_Num_Axes] {};

#define register_buttons_code(buttons) gamepad_codes[buttons] = buttons

        register_buttons_code(L2);
        register_buttons_code(R2);

#undef register_buttons_code

        float result = (Input::instance()->m_state_gamepad[gamepad_codes[axis]] != 1);
        return result;
    }

    return 1.0f;
}

float pc_joypad_device::get_axis_old_state(int axis, int)
{
    return 0.0f;
}

float pc_joypad_device::get_axis_delta(int axis, int a2)
{
    return this->get_axis_state(axis, a2) - 1.0f;
}

void pc_joypad_device::poll()
{
    TRACE("pc_joypad_device::poll");
    ;
}

bool pc_joypad_device::is_connected() const
{
    return this->field_4 != INVALID_DEVICE_ID;
}


bool pc_joypad_device::is_vibrator_present() const
{
    return true;
}