#pragma once
#include "CTaskComplex.h"

class CTaskComplexGetUpAndStandStill : public CTaskComplex
{
private:
    CTaskComplexGetUpAndStandStill* Constructor();
public:
    CTaskComplexGetUpAndStandStill() {}
    ~CTaskComplexGetUpAndStandStill() {}

    static void InjectHooks();

    CTask* Clone() override { return new CTaskComplexGetUpAndStandStill(); }
    eTaskType GetTaskType() override { return TASK_COMPLEX_GET_UP_AND_STAND_STILL; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType);

    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexGetUpAndStandStill, 0xC);
