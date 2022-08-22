#pragma once

#include "TaskSimple.h"

class CPed;
class CEvent;
class CTaskSimpleClearLookAt;

class CTaskSimpleClearLookAt : public CTaskSimple {
public:
    constexpr static auto Type = TASK_SIMPLE_IK_LOOK_AT;

    CTaskSimpleClearLookAt() = default;
    ~CTaskSimpleClearLookAt() = default;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleClearLookAt(); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return true; }
    bool ProcessPed(CPed* ped) override;
};
