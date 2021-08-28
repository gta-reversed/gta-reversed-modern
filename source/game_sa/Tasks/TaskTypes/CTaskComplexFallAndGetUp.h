#pragma once

#include "CTaskComplex.h"

class CTaskComplexFallAndGetUp : public CTaskComplex {
public:
    AnimationId m_nFallAnimId;
    AssocGroupId m_nFallAnimGroup;
    int32 m_nFallDownTime;

public:
    CTaskComplexFallAndGetUp(AnimationId nFallAnimId, AssocGroupId nFallAnimGroup, int32 nFallDownTime);
    CTaskComplexFallAndGetUp(int32 nDir, int32 nFallDownTime);
    ~CTaskComplexFallAndGetUp() override { }


    CTask* Clone() override { return new CTaskComplexFallAndGetUp(m_nFallAnimId, m_nFallAnimGroup, m_nFallDownTime); }
    eTaskType GetId() override { return TASK_COMPLEX_FALL_AND_GET_UP; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    CTask* CreateSubTask(eTaskType taskType);
    bool IsFalling();
    void SetDownTime(int32 nTime);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    
    CTaskComplexFallAndGetUp* Constructor(AnimationId nFallAnimId, AssocGroupId nFallAnimGroup, int32 nFallDownTime);
    CTaskComplexFallAndGetUp* Constructor2(int32 nDir, int32 nFallDownTime);
    
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
};

VALIDATE_SIZE(CTaskComplexFallAndGetUp, 0x18);
