#pragma once
#include "CTaskComplex.h"

class CTaskComplexUseWaterCannon : public CTaskComplex
{
public:
    CFire* m_pFire;

private:
    CTaskComplexUseWaterCannon* Constructor(CFire* pFire);
public:
    CTaskComplexUseWaterCannon(CFire* pFire);
    ~CTaskComplexUseWaterCannon() override;

    static void InjectHooks();

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_USE_WATER_CANNON; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* Clone_Reversed();
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexUseWaterCannon, 0x10);
