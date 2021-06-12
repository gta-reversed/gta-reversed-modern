#include "StdInc.h"

void CTaskSimpleRunAnim::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleRunAnim", "Constructor", 0x61A8B0, &CTaskSimpleRunAnim::Constructor);
    ReversibleHooks::Install("CTaskSimpleRunAnim", "Constructor2", 0x61A900, &CTaskSimpleRunAnim::Constructor2);
    ReversibleHooks::Install("CTaskSimpleRunAnim", "StartAnim", 0x61A950, &CTaskSimpleRunAnim::StartAnim);
    //VTABLE
    ReversibleHooks::Install("CTaskSimpleRunAnim", "Clone", 0x61B6D0, &CTaskSimpleRunAnim::Clone_Reversed);
    ReversibleHooks::Install("CTaskSimpleRunAnim", "ProcessPed", 0x61BAC0, &CTaskSimpleRunAnim::ProcessPed_Reversed);
}

CTaskSimpleRunAnim* CTaskSimpleRunAnim::Constructor(unsigned int animGroup, unsigned int animID, float fBlendDelta, bool bHoldLastFrame)
{
    this->CTaskSimpleRunAnim::CTaskSimpleRunAnim(animGroup, animID, fBlendDelta, bHoldLastFrame);
    return this;
}

CTaskSimpleRunAnim* CTaskSimpleRunAnim::Constructor2(unsigned int animGroup, unsigned int animID, float fBlendDelta, unsigned int nTaskType, char* pTaskName, bool bHoldLastFrame)
{
    this->CTaskSimpleRunAnim::CTaskSimpleRunAnim(animGroup, animID, fBlendDelta, nTaskType, pTaskName, bHoldLastFrame);
    return this;
}

// 0x61A900
CTaskSimpleRunAnim::CTaskSimpleRunAnim(unsigned int animGroup, unsigned int animID, float fBlendDelta, unsigned int nTaskType, char* pTaskName _IGNORED_, bool bHoldLastFrame) : CTaskSimpleAnim(bHoldLastFrame)
{
    m_nAnimGroup = animGroup;
    m_nAnimId = animID;
    m_fBlendDelta = fBlendDelta;
    m_nTaskType = nTaskType;
}

// 0x61A8B0
CTaskSimpleRunAnim::CTaskSimpleRunAnim(unsigned int animGroup, unsigned int animID, float fBlendDelta, bool bHoldLastFrame) : CTaskSimpleAnim(bHoldLastFrame)
{
    m_nAnimGroup = animGroup;
    m_nAnimId = animID;
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

