#pragma once

#include "Vector.h"

struct MovementInfo_t {
    CVector m_v0;
    CVector m_v1;
    float   m_fMinCW;
    float   m_fMaxCW;
    float   m_fMinCCW;
    float   m_fMaxCCW;
    bool    m_bFloat;
    bool    m_bUnderwater;

    void Process() {
        m_fMinCW      = 0.0f;
        m_fMaxCW      = 0.0f;
        m_fMinCCW     = 0.0f;
        m_fMaxCCW     = 0.0f;
        m_bFloat      = false;
        m_bUnderwater = false;
    }
};
VALIDATE_SIZE(MovementInfo_t, 0x2C);
