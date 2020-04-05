/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTask.h"

class CTaskSimple : public CTask {
public:
    static void InjectHooks();
    CTaskSimple();
    ~CTaskSimple();

    CTask* GetSubTask() override;
    bool IsSimple() override;
	virtual bool ProcessPed(class CPed *ped) = 0;
	virtual bool SetPedPosition(class CPed *ped);

    CTask* GetSubTask_Reversed() { return nullptr; }
    bool IsSimple_Reversed() { return true; }
    bool SetPedPosition_Reversed(class CPed* ped) { return false; };
};

VALIDATE_SIZE(CTaskSimple, 8);