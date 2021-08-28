#pragma once
#include "CTaskSimple.h"

class CTaskSimpleJump : public CTaskSimple
{
public:
    CVector m_vecClimbPos;
    float m_fClimbAngle;
    unsigned char m_nClimbSurfaceType;
    unsigned char _pad_19[3];
    CEntity* m_pClimbEntity;
    unsigned char m_bIsFinished;
    unsigned char m_bIsJumpBlocked;
    unsigned char m_bClimbJump;
    unsigned char m_bLaunchAnimStarted;
    unsigned char m_bCanClimb;
    unsigned char m_bHighJump;
    unsigned char _pad_26[2];
    CAnimBlendAssociation* m_pAnim;

private:
    CTaskSimpleJump* Constructor(bool bCanClimb);
public:
    CTaskSimpleJump(bool bCanClimb);
    ~CTaskSimpleJump() override;

    static void InjectHooks();

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_JUMP; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    bool ProcessPed(CPed* ped) override;

    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);
    bool ProcessPed_Reversed(CPed* ped);

    bool CheckIfJumpBlocked(CPed* ped);
    void Launch(CPed* ped);
    bool StartLaunchAnim(CPed* ped);
    static void JumpAnimFinishCB(CAnimBlendAssociation* pAnim, void* data);
};

VALIDATE_SIZE(CTaskSimpleJump, 0x2C);
