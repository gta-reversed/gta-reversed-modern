#pragma once

#include "TaskComplex.h"

class CTaskComplexBeStill : public CTaskComplex {
public:
    CTaskComplexBeStill() = default;
    ~CTaskComplexBeStill() override = default; // 0x5F6700

    CTask* Clone() override { return new CTaskComplexBeStill(); } // 0x5F6680
    eTaskType GetTaskType() override { return TASK_COMPLEX_BE_STILL; } // 0x5F66D0

    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
};
