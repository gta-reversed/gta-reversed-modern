#include "StdInc.h"

void CTaskSimpleHitHead::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleHitHead", "Constructor", 0x653060, &CTaskSimpleHitHead::Constructor);
    ReversibleHooks::Install("CTaskSimpleHitHead", "FinishAnimCB", 0x653150, &CTaskSimpleHitHead::FinishAnimCB);
    //VTABLE
    ReversibleHooks::Install("CTaskSimpleHitHead", "MakeAbortable", 0x6530F0, &CTaskSimpleHitHead::MakeAbortable_Reversed);
    ReversibleHooks::Install("CTaskSimpleHitHead", "ProcessPed", 0x657A10, &CTaskSimpleHitHead::ProcessPed_Reversed);
}

CTaskSimpleHitHead* CTaskSimpleHitHead::Constructor()
{
    this->CTaskSimpleHitHead::CTaskSimpleHitHead();
    return this;
}

// 0x653060
CTaskSimpleHitHead::CTaskSimpleHitHead()
{
    m_bIsFinished = false;
    m_pAnim = nullptr;
}

// 0x653090
CTaskSimpleHitHead::~CTaskSimpleHitHead()
{
    if (m_pAnim)
        m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
}

// 0x6530F0
bool CTaskSimpleHitHead::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return MakeAbortable_Reversed(ped, priority, _event);
}

// 0x657A10
bool CTaskSimpleHitHead::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

// 0x653150
void CTaskSimpleHitHead::FinishAnimCB(CAnimBlendAssociation* pAnim, void* data)
{
    auto pTask = reinterpret_cast<CTaskSimpleHitHead*>(data);
    pTask->m_pAnim = nullptr;
    pTask->m_bIsFinished = true;
}

bool CTaskSimpleHitHead::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    if (priority == ABORT_PRIORITY_URGENT || priority == ABORT_PRIORITY_IMMEDIATE)
    {
        if (m_pAnim)
        {
            m_pAnim->m_fBlendDelta = -4.0F;
            m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_pAnim = nullptr;
        }

        m_bIsFinished = true;
        return true;
    }
    else
    {
        if (m_pAnim)
            m_pAnim->m_fBlendDelta = -4.0F;

        return false;
    }
}

bool CTaskSimpleHitHead::ProcessPed_Reversed(CPed* ped)
{
    if (m_bIsFinished)
        return true;

    if (!m_pAnim)
    {
        m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_HIT_WALL, 8.0F);
        m_pAnim->SetFinishCallback(FinishAnimCB, this);
    }

    return m_bIsFinished;
}
