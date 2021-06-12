#pragma once
#include "CTaskComplex.h"
#include "CAccident.h"

class CTaskComplexTreatAccident : public CTaskComplex
{
public:
    CAccident* m_pAccident;
private:
    CTaskComplexTreatAccident* Constructor(CAccident* pAcc);
public:
    CTaskComplexTreatAccident(CAccident* pAcc);
    ~CTaskComplexTreatAccident() override;

    static void InjectHooks();

    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* Clone() override;

    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
    CTask* Clone_Reversed();

    eTaskType GetId() override { return TASK_COMPLEX_TREAT_ACCIDENT; }

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
    float ComputeHeading(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexTreatAccident, 0x10);
