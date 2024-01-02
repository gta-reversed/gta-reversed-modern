#pragma once

#include "TaskComplex.h"

class CTaskComplexFallAndGetUp : public CTaskComplex {
public:
    AnimationId  m_nFallAnimId;
    AssocGroupId m_nFallAnimGroup;
    int32        m_nFallDownTime;

public:
    static constexpr auto Type = TASK_COMPLEX_FALL_AND_GET_UP;

    CTaskComplexFallAndGetUp(AnimationId nFallAnimId, AssocGroupId nFallAnimGroup, int32 nFallDownTime);
    CTaskComplexFallAndGetUp(int32 nDir, int32 nFallDownTime);
    ~CTaskComplexFallAndGetUp() override = default;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskComplexFallAndGetUp(m_nFallAnimId, m_nFallAnimGroup, m_nFallDownTime); }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;

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
