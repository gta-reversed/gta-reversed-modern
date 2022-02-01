/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskComplexWander.h"
#include "TaskTimer.h"

class CTaskComplexWanderStandard : public CTaskComplexWander {
public:
    CTaskTimer m_TaskTimer;
    int32 m_nMinNextScanTime;

    CTaskComplexWanderStandard* Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly = true);
};

VALIDATE_SIZE(CTaskComplexWanderStandard, 0x38);
