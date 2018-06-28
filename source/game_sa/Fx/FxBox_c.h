/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"

class FxBox_c {
public:
    float m_fCornerA_x;
    float m_fCornerB_x;
    float m_fCornerA_y;
    float m_fCornerB_y;
    float m_fCornerA_z;
    float m_fCornerB_z;

    inline FxBox_c() {
        m_fCornerA_x = m_fCornerA_y = m_fCornerA_z = 999999.0f;
        m_fCornerB_x = m_fCornerB_y = m_fCornerB_z = -999999.0f;
    }
};

VALIDATE_SIZE(FxBox_c, 0x18);