#pragma once

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
        Reset();
    }

    inline void Reset() {
        m_fCornerA_x = m_fCornerA_y = m_fCornerA_z = 999999.0f;
        m_fCornerB_x = m_fCornerB_y = m_fCornerB_z = -999999.0f;
    }

    FxBox_c& operator=(const FxBox_c& right) = default;

    FxBox_c& operator=(const RwMatrix& right) {
        m_fCornerA_x = right.pos.x;
        m_fCornerA_y = right.pos.y;
        m_fCornerA_z = right.pos.z;

        m_fCornerB_x = right.pos.x;
        m_fCornerB_y = right.pos.y;
        m_fCornerB_z = right.pos.z;
        return *this;
    }
};
VALIDATE_SIZE(FxBox_c, 0x18);
