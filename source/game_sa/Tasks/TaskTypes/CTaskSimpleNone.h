#pragma once
#include "CTaskSimple.h"

class CTaskSimpleNone : public CTaskSimple
{
public:
    CTaskSimpleNone() : CTaskSimple() {}
    ~CTaskSimpleNone() override {}
    CTask* Clone() override { return new CTaskSimpleNone(); }
    eTaskType GetId() override { return TASK_NONE; }
    bool ProcessPed(CPed* ped) override { return true; }
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event) override { return true; }
};

VALIDATE_SIZE(CTaskSimpleNone, 0x8);
