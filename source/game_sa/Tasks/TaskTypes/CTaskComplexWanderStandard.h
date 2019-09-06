/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplexWander.h"
#include "CTaskTimer.h"

class  CTaskComplexWanderStandard : public CTaskComplexWander {
protected:
    CTaskComplexWanderStandard(plugin::dummy_func_t a) : CTaskComplexWander(a) , m_TaskTimer(a) {}
public:
    CTaskTimer m_TaskTimer;
    int m_nMinNextScanTime;

    CTaskComplexWanderStandard* Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly = true);
};

VALIDATE_SIZE(CTaskComplexWanderStandard, 0x38);
