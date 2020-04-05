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
public:
	CTask *m_pSubTask;

    CTaskComplex();
    ~CTaskComplex();
private:
    CTaskComplex* Constructor();
public:
	CTask* GetSubTask() override;
	bool IsSimple() override;
	bool MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event) override;

	virtual void SetSubTask(CTask *subTask);
	virtual CTask *CreateNextSubTask(CPed *ped) = 0;
	virtual CTask *CreateFirstSubTask(CPed *ped) = 0;
	virtual CTask *ControlSubTask(CPed *ped) = 0;

	CTask* GetSubTask_Reversed() { return m_pSubTask; }
	bool IsSimple_Reversed() { return false; }
	bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, class CEvent* _event);

};

VALIDATE_SIZE(CTaskComplex, 0xC);