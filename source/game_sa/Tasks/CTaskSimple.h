/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTask.h"

class  CTaskSimple : public CTask {
    CTaskSimple() = delete;
protected:
    CTaskSimple(plugin::dummy_func_t a) : CTask(a) {}
public:
	virtual bool ProcessPed(class CPed *ped);//=0
	virtual bool SetPedPosition(class CPed *ped);
    static void InjectHooks();
};

VALIDATE_SIZE(CTaskSimple, 8);