#pragma once

#include "TaskComplex.h"
#include "Accident.h"

class CTaskComplexTreatAccident : public CTaskComplex {
public:
    CAccident* m_pAccident;

public:
    static constexpr auto Type = TASK_COMPLEX_TREAT_ACCIDENT;

    explicit CTaskComplexTreatAccident(CAccident* accident);
    ~CTaskComplexTreatAccident() override = default; // 0x658AE0

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
    float ComputeHeading(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexTreatAccident* Constructor(CAccident* pAcc);

    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
    CTask* Clone_Reversed();
};
VALIDATE_SIZE(CTaskComplexTreatAccident, 0x10);
