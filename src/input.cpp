#include "input.h" 
#include "func_wrapper.h"
#include "utility.h"
#include "common.h"

VALIDATE_SIZE(Input, 0x129F8);

VALIDATE_OFFSET(Input, m_din, 0x27FC);

DIJOYSTATE2* Input::sub_820570(int a2)
{
    return &this->field_4F8[a2];
}

bool Input::sub_820590(int a2)
{
    bool result = false;

    if (this->field_14[a2]) {
        result = (this->field_64[a2] > 0);
    }

    return result;
}