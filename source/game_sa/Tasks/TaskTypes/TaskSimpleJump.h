#pragma once

#include "TaskSimple.h"

class CTaskSimpleJump : public CTaskSimple {
public:
    CVector  m_vecClimbPos;
    float    m_fClimbAngle;
    uint8    m_nClimbSurfaceType;
    CEntity* m_pClimbEntity;
    uint8    m_bIsFinished;
    uint8    m_bIsJumpBlocked;
    uint8    m_bClimbJump;
    uint8    m_bLaunchAnimStarted;
    uint8    m_bCanClimb;
    uint8    m_bHighJump;
    CAnimBlendAssociation* m_pAnim;

public:
    static constexpr auto Type = TASK_SIMPLE_JUMP;

    explicit CTaskSimpleJump(bool bCanClimb);
    ~CTaskSimpleJump() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    bool CheckIfJumpBlocked(CPed* ped);
    void Launch(CPed* ped);
    bool StartLaunchAnim(CPed* ped);
    static void JumpAnimFinishCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleJump* Constructor(bool bCanClimb);
    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};
VALIDATE_SIZE(CTaskSimpleJump, 0x2C);
