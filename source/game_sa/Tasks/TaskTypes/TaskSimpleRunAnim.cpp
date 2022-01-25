#include "StdInc.h"

#include "TaskSimpleRunAnim.h"

void CTaskSimpleRunAnim::InjectHooks()
{
    Install("CTaskSimpleRunAnim", "Constructor", 0x61A8B0, &CTaskSimpleRunAnim::Constructor);
    Install("CTaskSimpleRunAnim", "Constructor2", 0x61A900, &CTaskSimpleRunAnim::Constructor2);
    Install("CTaskSimpleRunAnim", "StartAnim", 0x61A950, &CTaskSimpleRunAnim::StartAnim);
    //VTABLE
    Install("CTaskSimpleRunAnim", "Clone", 0x61B6D0, &CTaskSimpleRunAnim::Clone_Reversed);
    Install("CTaskSimpleRunAnim", "ProcessPed", 0x61BAC0, &CTaskSimpleRunAnim::ProcessPed_Reversed);
}

CTaskSimpleRunAnim* CTaskSimpleRunAnim::Constructor(AssocGroupId animGroup, AnimationId animId, float fBlendDelta, bool bHoldLastFrame)
{
    this->CTaskSimpleRunAnim::CTaskSimpleRunAnim(animGroup, animId, fBlendDelta, bHoldLastFrame);
    return this;
}

CTaskSimpleRunAnim* CTaskSimpleRunAnim::Constructor2(AssocGroupId animGroup, AnimationId animId, float fBlendDelta, int32 nTaskType, const char* taskName, bool bHoldLastFrame)
{
    this->CTaskSimpleRunAnim::CTaskSimpleRunAnim(animGroup, animId, fBlendDelta, nTaskType, taskName, bHoldLastFrame);
    return this;
}

// 0x61A900
CTaskSimpleRunAnim::CTaskSimpleRunAnim(AssocGroupId animGroup, AnimationId animId, float fBlendDelta, int32 nTaskType, const char* taskName _IGNORED_, bool bHoldLastFrame) : CTaskSimpleAnim(bHoldLastFrame)
{
    m_nAnimGroup = animGroup;
    m_nAnimId = animId;
    m_fBlendDelta = fBlendDelta;
    m_nTaskType = nTaskType;
}

// 0x61A8B0
CTaskSimpleRunAnim::CTaskSimpleRunAnim(AssocGroupId animGroup, AnimationId animId, float fBlendDelta, bool bHoldLastFrame) : CTaskSimpleAnim(bHoldLastFrame)
{
    m_nAnimGroup = animGroup;
    m_nAnimId = animId;
    m_fBlendDelta = fBlendDelta;
    m_nTaskType = TASK_SIMPLE_ANIM;
}

// 0x61B6D0
CTask* CTaskSimpleRunAnim::Clone()
{
    return Clone_Reversed();
}

// 0x61BAC0
bool CTaskSimpleRunAnim::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

CTask* CTaskSimpleRunAnim::Clone_Reversed()
{
    return new CTaskSimpleRunAnim(m_nAnimGroup, m_nAnimId, m_fBlendDelta, m_bHoldLastFrame);
}

bool CTaskSimpleRunAnim::ProcessPed_Reversed(CPed* ped)
{
    if (m_bIsFinished)
        return true;

    if (!m_pAnim && !RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_nAnimId))
        StartAnim(ped);

    return m_bIsFinished;
}

// 0x61A950
void CTaskSimpleRunAnim::StartAnim(CPed* ped)
{
    m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_nAnimGroup, m_nAnimId, m_fBlendDelta);
    m_pAnim->SetFinishCallback(CTaskSimpleAnim::FinishRunAnimCB, this);
}

