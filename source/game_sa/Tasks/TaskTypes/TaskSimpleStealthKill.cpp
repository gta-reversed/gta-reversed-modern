#include "StdInc.h"

#include "TaskSimpleStealthKill.h"

void CTaskSimpleStealthKill::InjectHooks()
{
    RH_ScopedClass(CTaskSimpleStealthKill);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedVirtualInstall(ProcessPed, 0x62E540);
    RH_ScopedInstall(Constructor, 0x6225F0);
    RH_ScopedVirtualInstall(Clone, 0x623830);
    RH_ScopedVirtualInstall(GetId, 0x622670);
    RH_ScopedVirtualInstall(MakeAbortable, 0x6226F0);
    RH_ScopedInstall(ManageAnim, 0x6296D0);
    RH_ScopedInstall(FinishAnimStealthKillCB, 0x622790);
}

CTaskSimpleStealthKill::CTaskSimpleStealthKill(bool keepTargetAlive, CPed* target, AssocGroupId groupId)
{
    m_bKeepTargetAlive = keepTargetAlive;
    m_pTarget          = target;
    m_nAssocGroupId    = groupId;
    m_bIsAborting      = false;
    m_bIsFinished      = false;
    m_pAnim            = nullptr;
    m_nTime            = 0;
    CEntity::SafeRegisterRef(m_pTarget);
}

// 0x6225F0
CTaskSimpleStealthKill* CTaskSimpleStealthKill::Constructor(bool keepTargetAlive, CPed* target, AssocGroupId groupId)
{
    this->CTaskSimpleStealthKill::CTaskSimpleStealthKill(keepTargetAlive, target, groupId);
    return this;
}

bool CTaskSimpleStealthKill::ProcessPed_Reversed(CPed* ped) {
    if (m_bIsAborting || !m_pTarget)
        return true;

    if (!m_pAnim)
    {
        if (!m_bKeepTargetAlive)
            ped->SetPedState(PEDSTATE_DIE_BY_STEALTH);

        ManageAnim(ped);
        if (!m_pAnim) {
            if (m_bIsFinished)
                return false;
        }
    }

    ped->m_pedIK.bSlopePitch = true;

    CVector distance = m_pTarget->GetPosition() - ped->GetPosition();

    if (!m_bKeepTargetAlive) {
        if (!m_pAnim || m_pAnim->m_nAnimId == ANIM_ID_KILL_KNIFE_PED_DAMAGE) {
            ped->m_fAimingRotation = atan2(-(distance.x * -1.0f), distance.y * -1.0f);
            return false;
        }
        return false;
    }

    float magnitude = distance.Magnitude() - 1.0f;
    if (fabs(magnitude) <= 0.02f) {
        ped->m_fAimingRotation = atan2(-distance.x, distance.y);
    }
    else {
        magnitude = std::min(CTimer::GetTimeStep() * 0.05f, magnitude);
        ped->m_vecAnimMovingShiftLocal.y = magnitude;
        ped->m_vecAnimMovingShiftLocal.x = 0.0f;
        ped->m_fAimingRotation = atan2(-distance.x, distance.y);
    }

    return false;
}

// 0x62E540
bool CTaskSimpleStealthKill::ProcessPed(CPed* ped)
{
    return CTaskSimpleStealthKill::ProcessPed_Reversed(ped);
}

CTask* CTaskSimpleStealthKill::Clone_Reversed()
{
    return new CTaskSimpleStealthKill(m_bKeepTargetAlive, m_pTarget, m_nAssocGroupId);
}

// 0x623830
CTask* CTaskSimpleStealthKill::Clone()
{
    return CTaskSimpleStealthKill::Clone_Reversed();
}

// 0x6226F0
bool CTaskSimpleStealthKill::MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return CTaskSimpleStealthKill::MakeAbortable_Reversed(ped, priority, event);
}

bool CTaskSimpleStealthKill::MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event)
{
    CEventDamage* eventDamage = (CEventDamage*)event;
    if (priority == ABORT_PRIORITY_IMMEDIATE) {
        if (m_pAnim)
        {
            m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_pAnim = nullptr;
        }

        m_bIsAborting = true;
        return true;
    }
    else if (priority == ABORT_PRIORITY_URGENT &&
             !m_bKeepTargetAlive &&
             m_pAnim &&
             m_pAnim->m_nAnimId == ANIM_ID_KILL_KNIFE_PED_DIE &&
             event->GetEventType() == EVENT_DAMAGE &&
             eventDamage->m_pSourceEntity == m_pTarget
     ) {
        m_bIsAborting = true;
        m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        return true;
    }
    else {
        return false;
    }
}

// 0x622670
eTaskType CTaskSimpleStealthKill::GetTaskType()
{
    return CTaskSimpleStealthKill::GetId_Reversed();
}

// 0x6296D0
void CTaskSimpleStealthKill::ManageAnim(CPed* ped)
{
    CAnimBlock* pAnimBlock = CAnimManager::ms_aAnimAssocGroups[m_nAssocGroupId].m_pAnimBlock;
    if (pAnimBlock && pAnimBlock->bLoaded)
    {
        if (m_bKeepTargetAlive)
        {
            m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_nAssocGroupId, ANIM_ID_KILL_KNIFE_PLAYER, 8.0f);
        }
        else if (m_bIsFinished)
        {
            m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_nAssocGroupId, ANIM_ID_KILL_KNIFE_PED_DIE, 8.0f);
            CPedDamageResponseCalculator damageCalculator(ped, CPedDamageResponseCalculator::ms_damageFactor, m_pTarget->GetActiveWeapon().m_nType, PED_PIECE_TORSO, false);
            CEventDamage eventDamage(m_pTarget, CTimer::GetTimeInMS(), m_pTarget->GetActiveWeapon().m_nType, PED_PIECE_TORSO, 0, false, ped->bInVehicle);
            if (eventDamage.AffectsPed(ped))
            {
                damageCalculator.ComputeDamageResponse(ped, eventDamage.m_damageResponse, true);

                eventDamage.m_nAnimGroup = m_nAssocGroupId;
                eventDamage.m_nAnimID = ANIM_ID_KILL_KNIFE_PED_DIE;
                eventDamage.m_fAnimBlend = 8.0f;
                eventDamage.m_fAnimSpeed = 1.0f;
                eventDamage.m_ucDirection |= 4u;
                ped->GetEventGroup().Add(&eventDamage, false);
            }
        }
        else
        {
            m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_nAssocGroupId, ANIM_ID_KILL_KNIFE_PED_DAMAGE, 8.0f);
        }

        m_pAnim->SetFinishCallback(CTaskSimpleStealthKill::FinishAnimStealthKillCB, this);
        m_bIsFinished = true;
    }
    else
    {
        m_nTime += (uint32)CTimer::GetTimeStepInMS();
        if (m_nTime > 10000)
            m_bIsAborting = true;
    }
}

// 0x622790
void CTaskSimpleStealthKill::FinishAnimStealthKillCB(CAnimBlendAssociation* pAnimAssoc, void* data)
{
    auto pTaskSimpleStealthKill = reinterpret_cast<CTaskSimpleStealthKill*>(data);
    if (pAnimAssoc->m_nAnimId != ANIM_ID_KILL_KNIFE_PLAYER && pAnimAssoc->m_nAnimId != ANIM_ID_KILL_KNIFE_PED_DIE)
    {
        pTaskSimpleStealthKill->m_pAnim = nullptr;
    }
    else
    {
        pTaskSimpleStealthKill->m_bIsAborting = true;
        pTaskSimpleStealthKill->m_pAnim = nullptr;
    }
}
