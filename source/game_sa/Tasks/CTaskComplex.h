/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTask.h"

class CPed;

class CTaskComplex : public CTask {
    CTaskComplex() = delete;
protected:
    CTaskComplex(plugin::dummy_func_t a) : CTask(a) {}
public:
	CTask *m_pSubTask;

	// vtable
	virtual void SetSubTask(CTask *subTask);
	virtual CTask *CreateNextSubTask(CPed *ped);//=0
	virtual CTask *CreateFirstSubTask(CPed *ped);
	virtual CTask *ControlSubTask(CPed *ped);//=0
};

VALIDATE_SIZE(CTaskComplex, 0xC);