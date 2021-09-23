#pragma once

#include "CTaskComplex.h"

class CTaskComplexInAirAndLand : public CTaskComplex {
public:
    uint8 m_bUsingJumpGlide;
    uint8 m_bUsingFallGlide;
    uint8 m_bInvalidClimb;
    uint8 _pad;


public:
    CTaskComplexInAirAndLand(bool bUsingJumpGlide, bool bUsingFallGlide);
    ~CTaskComplexInAirAndLand() override {}

    CTask* Clone() override { return new CTaskComplexInAirAndLand(m_bUsingJumpGlide, m_bUsingFallGlide); }
    eTaskType GetTaskType() override { return TASK_COMPLEX_IN_AIR_AND_LAND; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexInAirAndLand* Constructor(bool bUsingJumpGlide, bool bUsingFallGlide);
};

VALIDATE_SIZE(CTaskComplexInAirAndLand, 0x10);
