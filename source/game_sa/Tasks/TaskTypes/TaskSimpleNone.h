#pragma once
#include "TaskSimple.h"

class CTaskSimpleNone : public CTaskSimple
{
public:
    CTaskSimpleNone() : CTaskSimple() {}
    ~CTaskSimpleNone() override {}
    CTask* Clone() override { return new CTaskSimpleNone(); }
    eTaskType GetTaskType() override { return TASK_NONE; }
    bool ProcessPed(CPed* ped) override { return true; }
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override { return true; }
};

VALIDATE_SIZE(CTaskSimpleNone, 0x8);
