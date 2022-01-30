#include "StdInc.h"

#include "TaskSimpleGiveCPR.h"

void CTaskSimpleGiveCPR::InjectHooks()
{
    RH_ScopedClass(CTaskSimpleGiveCPR);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x658860);
    RH_ScopedInstall(ReviveDeadPed, 0x658900);
    RH_ScopedInstall(FinishGiveCPRAnimCB, 0x658910);
    //VTABLE
    RH_ScopedInstall(Clone_Reversed, 0x659A10);
    RH_ScopedInstall(ProcessPed_Reversed, 0x65A7C0);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x6589B0);
}

CTaskSimpleGiveCPR* CTaskSimpleGiveCPR::Constructor(CAccident* pAccident)
{
    this->CTaskSimpleGiveCPR::CTaskSimpleGiveCPR(pAccident);
    return this;
}

// 0x658860
CTaskSimpleGiveCPR::CTaskSimpleGiveCPR(CAccident* pAccident)
{
    bNoHealthValue = true;
    bAnimationFinished = false;
    m_pAccident = pAccident;
    m_pAnim = nullptr;
}

// 0x659E10
CTaskSimpleGiveCPR::~CTaskSimpleGiveCPR()
{
    if (m_pAnim)
        m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
}

// 0x659A10
CTask* CTaskSimpleGiveCPR::Clone()
{
    return Clone_Reversed();
}

// 0x65A7C0
bool CTaskSimpleGiveCPR::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

// 0x6589B0
bool CTaskSimpleGiveCPR::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return MakeAbortable_Reversed(ped, priority, event);
}

CTask* CTaskSimpleGiveCPR::Clone_Reversed()
{
    return new CTaskSimpleGiveCPR(m_pAccident);
}

bool CTaskSimpleGiveCPR::ProcessPed_Reversed(CPed* ped)
{
    if (bNoHealthValue)
    {
        m_fInitialHealth = ped->m_fHealth;
        bNoHealthValue = false;
    }

    if (bAnimationFinished)
    {
        ReviveDeadPed(ped);
        return true;
    }
    else
    {
        if (!m_pAnim)
        {
            m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_MEDIC, ANIM_ID_CPR, 4.0F);
            m_pAnim->SetFinishCallback(FinishGiveCPRAnimCB, this);
        }
        return false;
    }
}

bool CTaskSimpleGiveCPR::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    eEventType eventType = event->GetEventType();

    if (priority == ABORT_PRIORITY_IMMEDIATE
        || eventType == EVENT_DEATH
        || eventType == EVENT_HEALTH_REALLY_LOW
        || eventType == EVENT_ON_FIRE
        || eventType == EVENT_IN_WATER
        || eventType == EVENT_WATER_CANNON
        || eventType == EVENT_VEHICLE_DAMAGE_WEAPON
        || eventType == EVENT_VEHICLE_DAMAGE_COLLISION
        || eventType == EVENT_DAMAGE && (ped->m_fHealth <= 10.0F || m_fInitialHealth - ped->m_fHealth >= 40.0F)
        )
    {
        if (m_pAnim)
        {
            m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_pAnim->m_fBlendDelta = -1000.0F;
            m_pAnim = nullptr;
        }
        return true;
    }
    else
        return false;
}

// 0x658900
void CTaskSimpleGiveCPR::ReviveDeadPed(CPed* ped)
{
    if (m_pAccident && m_pAccident->m_pPed)
    {
        CPed* targetPed = m_pAccident->m_pPed;

        m_pAccident->m_bIsRevived = true;
        if (!targetPed->bRemoveHead)
        {
            g_InterestingEvents.Add((CInterestingEvents::EType)11, targetPed);
            CEventRevived eventRevived;
            targetPed->GetIntelligence()->m_eventGroup.Add(&eventRevived, false);
        }
    }
}

// 0x658910
void CTaskSimpleGiveCPR::FinishGiveCPRAnimCB(CAnimBlendAssociation* pAnim, void* priv)
{
    CTaskSimpleGiveCPR* pTask = reinterpret_cast<CTaskSimpleGiveCPR*>(priv);

    pTask->m_pAnim = nullptr;
    pTask->bAnimationFinished = true;
}
