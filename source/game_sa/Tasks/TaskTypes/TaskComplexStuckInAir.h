#pragma once

#include "TaskComplex.h"

class CTaskComplexStuckInAir : public CTaskComplex {
public:
    static constexpr auto Type = TASK_COMPLEX_STUCK_IN_AIR;

    CTaskComplexStuckInAir() = default;           // 0x67BA40
    ~CTaskComplexStuckInAir() override = default; // 0x67BA70

    eTaskType GetTaskType() const override { return Type; } // 0x67BA60
    CTask* Clone() const override { return new CTaskComplexStuckInAir(); }       // 0x67C700
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType, CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTask* ControlSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateSubTask_Reversed(eTaskType taskType, CPed* ped);
};
