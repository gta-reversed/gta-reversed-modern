#include "StdInc.h"

#include "TaskSimpleAnim.h"

void CTaskSimpleAnim::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleAnim", "MakeAbortable", 0x61A790, &CTaskSimpleAnim::MakeAbortable_Reversed);
}

CTaskSimpleAnim::CTaskSimpleAnim(bool bHoldLastFrame) : CTaskSimple()
{
    m_bIsFinished = false;
    m_bDontInterrupt = false;
    m_bHoldLastFrame = bHoldLastFrame;
    m_pAnim = nullptr;
}

CTaskSimpleAnim::~CTaskSimpleAnim()
{
    if (!m_pAnim)
        return;

    m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    m_pAnim->m_nFlags |= eAnimationFlags::ANIM_FLAG_FREEZE_LAST_FRAME;
    if (!m_bHoldLastFrame)
    {
        if (m_pAnim->m_fBlendAmount > 0.0F && m_pAnim->m_fBlendDelta >= 0.0F)
            m_pAnim->m_fBlendDelta = -4.0F;
    }

    m_pAnim = nullptr;
}

bool CTaskSimpleAnim::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return CTaskSimpleAnim::MakeAbortable_Reversed(ped, priority, event);
}
bool CTaskSimpleAnim::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    bool bSkipBlend = false;
    auto fBlend = -4.0F;
    if (priority == eAbortPriority::ABORT_PRIORITY_IMMEDIATE)
    {
        fBlend = -1000.0F;
        m_bHoldLastFrame = false;
    }
    else if (m_bDontInterrupt)
    {
        if (event && event->GetEventType() != eEventType::EVENT_SCRIPT_COMMAND)
            return false;
    }
    else if (event)
    {
        if (event->GetEventType() == eEventType::EVENT_SCRIPT_COMMAND)
        {
            const auto* pEvent = static_cast<const CEventScriptCommand*>(event);
            if (pEvent->m_task)
            {
                if (pEvent->m_task->GetTaskType() == eTaskType::TASK_SIMPLE_NAMED_ANIM)
                {
                    if (m_pAnim)
                        m_pAnim->m_nFlags |= ANIM_FLAG_FREEZE_LAST_FRAME;

                    bSkipBlend = true;
                }
            }
        }
    }

    if (!bSkipBlend)
    {
        if (m_pAnim)
        {
            m_pAnim->m_nFlags |= ANIM_FLAG_FREEZE_LAST_FRAME;
            if (!m_bHoldLastFrame)
            {
                if (m_pAnim->m_nFlags & ANIM_FLAG_PARTIAL)
                    m_pAnim->m_fBlendDelta = fBlend;
                else
                    CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, AnimationId::ANIM_ID_IDLE, -fBlend);
            }
        }
    }

    if (priority != eAbortPriority::ABORT_PRIORITY_IMMEDIATE
        && priority != eAbortPriority::ABORT_PRIORITY_URGENT
        && !m_bHoldLastFrame)
    {
        return false;
    }

    if (m_pAnim)
    {
        m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        m_bIsFinished = true;
        m_pAnim = nullptr;
    }

    return true;
}

void CTaskSimpleAnim::FinishRunAnimCB(CAnimBlendAssociation* pBlendAssoc, void* data)
{
    static_cast<CTaskSimpleAnim*>(data)->m_bIsFinished = true;
    static_cast<CTaskSimpleAnim*>(data)->m_pAnim = nullptr;
}
