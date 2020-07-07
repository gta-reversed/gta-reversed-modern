#include "StdInc.h"

void CTaskSimpleStealthKill::InjectHooks()
{
    HookInstall(0x62E540, &CTaskSimpleStealthKill::ProcessPed_Reversed);
    HookInstall(0x6225F0, &CTaskSimpleStealthKill::Constructor);
    HookInstall(0x623830, &CTaskSimpleStealthKill::Clone_Reversed);
    HookInstall(0x622670, &CTaskSimpleStealthKill::GetId_Reversed);
    HookInstall(0x6226F0, &CTaskSimpleStealthKill::MakeAbortable_Reversed);
    HookInstall(0x6296D0, &CTaskSimpleStealthKill::ManageAnim);
    HookInstall(0x622790, &CTaskSimpleStealthKill::FinishAnimStealthKillCB);
}

CTaskSimpleStealthKill::CTaskSimpleStealthKill(bool bKeepTargetAlive, CPed* pTarget, int nAssocGroupId)
{
    m_bKeepTargetAlive = bKeepTargetAlive;
    m_pTarget = pTarget;
    m_nAssocGroupId = nAssocGroupId;
    m_bIsAborting = false;
    m_bIsFinished = false;
    m_pAnim = nullptr;
    m_nTime = 0;
    if (pTarget)
        pTarget->RegisterReference(reinterpret_cast<CEntity**>(&m_pTarget));
}

CTaskSimpleStealthKill* CTaskSimpleStealthKill::Constructor(bool bKeepTargetAlive, CPed* pTarget, int nAssocGroupId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleStealthKill*, 0x6225F0, CTaskSimpleStealthKill*, bool, CPed*, int>(this, bKeepTargetAlive, pTarget, nAssocGroupId);
#else
    this->CTaskSimpleStealthKill::CTaskSimpleStealthKill(bKeepTargetAlive, pTarget, nAssocGroupId);
    return this;
#endif
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
        magnitude = std::min(CTimer::ms_fTimeStep * 0.05f, magnitude);
        ped->m_vecAnimMovingShiftLocal.y = magnitude;
        ped->m_vecAnimMovingShiftLocal.x = 0.0f;
        ped->m_fAimingRotation = atan2(-distance.x, distance.y);
    }

    return false;
}

bool CTaskSimpleStealthKill::ProcessPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x62E540, CTask*, CPed*>(this, ped);
#else
    return CTaskSimpleStealthKill::ProcessPed_Reversed(ped);
#endif
}

CTask* CTaskSimpleStealthKill::Clone_Reversed()
{
    return new CTaskSimpleStealthKill(m_bKeepTargetAlive, m_pTarget, m_nAssocGroupId);
}

CTask* CTaskSimpleStealthKill::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleStealthKill*, 0x623830, CTaskSimpleStealthKill*>(this);
#else
    return CTaskSimpleStealthKill::Clone_Reversed();
#endif
}

bool CTaskSimpleStealthKill::MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x6226F0, CTaskSimpleStealthKill*, CPed*, eAbortPriority, CEvent*>(this, ped, priority, _event);
#else
    return CTaskSimpleStealthKill::MakeAbortable_Reversed(ped, priority, _event);
#endif
}

bool CTaskSimpleStealthKill::MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, class CEvent* _event)
{
    CEventDamage* eventDamage = (CEventDamage*)_event;
    if (priority == ABORT_PRIORITY_IMMEDIATE) {
        if (m_pAnim)
        {
            m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, 0);
            m_pAnim = nullptr;
        }

        m_bIsAborting = true;
        return true;
    }
    else if (priority == ABORT_PRIORITY_URGENT &&
             !m_bKeepTargetAlive &&
             m_pAnim &&
             m_pAnim->m_nAnimId == ANIM_ID_KILL_KNIFE_PED_DIE &&
             _event->GetEventType() == EVENT_DAMAGE &&
             eventDamage->m_pSourceEntity == m_pTarget) {
        m_bIsAborting = true;
        m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, 0);
        return true;
    }
    else {
        return false;
    }
}

eTaskType CTaskSimpleStealthKill::GetId()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<eTaskType, 0x622670, CTaskSimpleStealthKill*>(this);
#else
    return CTaskSimpleStealthKill::GetId_Reversed();
#endif
}

void CTaskSimpleStealthKill::ManageAnim(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CTaskSimpleStealthKill*, CPed*))0x6296D0)(this, ped);
#else
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
            CPedDamageResponseCalculator damageCalculator = CPedDamageResponseCalculator(ped, CPedDamageResponseCalculator::ms_damageFactor, m_pTarget->GetActiveWeapon().m_nType, PED_PIECE_TORSO, false);

            CEventDamage eventDamage(m_pTarget, CTimer::m_snTimeInMilliseconds, m_pTarget->GetActiveWeapon().m_nType, PED_PIECE_TORSO, 0, 0, ped->bInVehicle);
            if (eventDamage.AffectsPed(ped))
            {
                damageCalculator.ComputeDamageResponse(ped, &eventDamage.m_damageResponse, true);

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
        m_nTime += static_cast<std::uint32_t>(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
        if (m_nTime > 10000)
            m_bIsAborting = true;
    }
#endif
}

void CTaskSimpleStealthKill::FinishAnimStealthKillCB(CAnimBlendAssociation* pAnimAssoc, void* data)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((void(__cdecl*)(CAnimBlendAssociation*, void*))0x622790)(pAnimAssoc, data);
#else
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
#endif
}
