#pragma once

#include "TaskSimple.h"

class NOTSA_EXPORT_VTABLE CTaskSimpleNone : public CTaskSimple {
public:
    CTaskSimpleNone() = default;
    ~CTaskSimpleNone() override = default;

    CTask* Clone() override { return new CTaskSimpleNone(); }
    eTaskType GetTaskType() override { return TASK_NONE; }
    bool ProcessPed(CPed* ped) override { return true; }
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override { return true; }
};

VALIDATE_SIZE(CTaskSimpleNone, 0x8);
