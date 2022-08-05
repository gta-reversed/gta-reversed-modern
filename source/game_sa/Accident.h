#pragma once

#include "Base.h"

class CPed;

class CAccident {
public:
    CPed* m_pPed;
    bool  m_bIsTreated;
    bool  m_bIsRevived;

public:
    // 0x56CDE0
    CAccident() {
        m_pPed = nullptr;
        m_bIsTreated = false;
        m_bIsRevived = false;
    }

    // 0x56CE00
    bool IsFree() {
        return    m_pPed
               && !m_bIsTreated
               && !m_bIsRevived
               && !m_pPed->physicalFlags.bSubmergedInWater;
    }
};
VALIDATE_SIZE(CAccident, 0x8);
