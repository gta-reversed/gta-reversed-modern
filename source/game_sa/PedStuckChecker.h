#pragma once

#include "Vector.h"

class CPed;
class CEventGroup;

enum ePedStuckState : uint16 {
    PED_STUCK_STATE_NONE = 0,
    PED_STUCK_STATE_STUCK = 1,
    PED_STUCK_STATE_WAS_STUCK = 2
};

class CPedStuckChecker {
public:
    CVector        m_lastNonStuckPoint;
    uint16         m_radius;
    ePedStuckState m_state;

    bool TestPedStuck(CPed* pPed, CEventGroup* pEventGroup);
};

VALIDATE_SIZE(CPedStuckChecker, 0x10);
