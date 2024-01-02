#pragma once

#include "Base.h"
#include "ePedBones.h"

struct tBoneInfo {
    ePedBones m_current; // This bone
    ePedBones m_prev;    // Previous connected bone
    CVector   m_Max;
    CVector   m_Min;
    CVector   m_ABC;
};
VALIDATE_SIZE(tBoneInfo, 0x28);
