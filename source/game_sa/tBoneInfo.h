#pragma once

#include "Base.h"
#include "ePedBones.h"

struct tBoneInfo {
    ePedBones m_current; // This bone
    ePedBones m_prev;    // Previous connected bone
    int32 field_4;
    int32 field_8;
    int32 field_C;
    int32 field_10;
    int32 field_14;
    int32 field_18;
    int32 field_1C;
    int32 field_20;
    int32 field_24;
};
