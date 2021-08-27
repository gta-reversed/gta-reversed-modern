#pragma once
#include "CTaskSimple.h"

class CTaskSimpleUninterruptable : public CTaskSimple
{
private:
    CTaskSimpleUninterruptable* Constructor();
public:
    CTaskSimpleUninterruptable() {}
    ~CTaskSimpleUninterruptable() override {}

    static void InjectHooks();

    CTask* Clone() override { return new CTaskSimpleUninterruptable(); }
    eTaskType GetId() override { return TASK_SIMPLE_UNINTERRUPTABLE; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return priority == ABORT_PRIORITY_IMMEDIATE; }
    bool ProcessPed(CPed* ped) override { return false; }
};

VALIDATE_SIZE(CTaskSimpleUninterruptable, 0x8);
