#pragma once
#include "CVector.h"

class CPed;
class CEventGroup;

enum ePedStuckState : std::uint16_t
{
    PED_STUCK_STATE_NONE = 0,
    PED_STUCK_STATE_STUCK = 1,
    PED_STUCK_STATE_WAS_STUCK = 2
};

class CPedStuckChecker
{
public:
    CVector m_lastNonStuckPoint;
    std::uint16_t m_radius;
    ePedStuckState m_state;

    bool TestPedStuck(CPed* pPed, CEventGroup* pEventGroup);
};

VALIDATE_SIZE(CPedStuckChecker, 0x10);
