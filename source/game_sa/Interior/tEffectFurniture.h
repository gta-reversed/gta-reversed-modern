#pragma once

#include "Base.h"

struct tEffectFurniture {
    int8  m_type;
    int8  m_id;
    int8  m_x;
    int8  m_y;
    int8  m_z;
    int8  field_5;
    int8  field_6;
    int8  field_7;
    int8  field_8;
    int8  field_9;
    int8  field_A;
    int8  field_B;
    int8  field_C;
    int8  field_D;
    int8  field_E;
    int8  field_F;
    int8  field_10;
    int8  field_11;
    int8  field_12;
    int8  field_13;
    int8  field_14;
    int8  field_15;
    int8  field_16;
    int8  field_17;
    int8  field_18;
    int8  field_19;
    int8  field_1A;
    int8  field_1B;
    int8  field_1C;
    int8  field_1D;
    int8  field_1E;
    int8  m_wealth;
    float field_20;
    int32 field_24;
    int32 field_28;
    int32 field_2C;
    int32 field_30;
};
VALIDATE_SIZE(tEffectFurniture, 0x34);
