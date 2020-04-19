#pragma once
#include "CTaskComplexGoToPointAndStandStill.h"

class CTaskComplexGoToPointAndStandStillTimed : public CTaskComplexGoToPointAndStandStill
{
public:
    unsigned int m_nTimeInMs;
    unsigned int m_nStartTickInMs;
    unsigned int m_nTimeLeftInMs;
    bool m_bWarpPedToPointOnTimeout;
    bool m_bResetTime;
private:
    char field_36[2]; // padding
};

VALIDATE_SIZE(CTaskComplexGoToPointAndStandStillTimed, 0x38);