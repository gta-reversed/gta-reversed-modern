#pragma once

#include "TaskSimple.h"

class NOTSA_EXPORT_VTABLE CTaskSimpleNone : public CTaskSimple {
public:
    static constexpr auto Type = TASK_NONE;

    CTaskSimpleNone() = default;
    ~CTaskSimpleNone() override = default;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleNone(); }
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override { return true; }
    bool ProcessPed(CPed* ped) override { return true; }
};
VALIDATE_SIZE(CTaskSimpleNone, 0x8);
