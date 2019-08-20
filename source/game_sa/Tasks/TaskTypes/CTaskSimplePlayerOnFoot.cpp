#include "StdInc.h"

CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskSimplePlayerOnFoot*, 0x685750, CTaskSimplePlayerOnFoot*>(this);
}

CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Destructor()
{
    return plugin::CallMethodAndReturn<CTaskSimplePlayerOnFoot*, 0x68B0C0, CTaskSimplePlayerOnFoot*>(this);
}

bool CTaskSimplePlayerOnFoot::ProcessPed(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x688810, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
#else
    bool result = false;
    CPlayerPed* pPlayerPed = static_cast<CPlayerPed*>(pPed);
    if (pPlayerPed->GetPadFromPlayer())
    {
        CPedIntelligence* pIntelligence = pPlayerPed->m_pIntelligence;
        bool bPedMoving = pPlayerPed->m_nMoveState >= PEDMOVE_WALK;
        if (pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType == WEAPON_CHAINSAW
            && pIntelligence->GetTaskFighting()
            && pIntelligence->GetTaskFighting()->m_nCurrentMove == 4)
        {
            bPedMoving = 1;
        }
        pPlayerPed->SetMoveState(PEDMOVE_STILL);
        if (pPlayerPed->bIsDucking)
        {
            PlayerControlDucked(pPlayerPed);
        }
        else if (!pIntelligence->GetTaskFighting() || bPedMoving)
        {
            CTaskSimpleUseGun* pSimpleTaskUseGun = pIntelligence->GetTaskUseGun();
            if (pSimpleTaskUseGun
                && pSimpleTaskUseGun->m_pWeaponInfo
                && !pSimpleTaskUseGun->m_pWeaponInfo->m_nFlags.bAimWithArm)
            {
                PlayerControlZeldaWeapon(pPlayerPed);
            }
            else
            {
                PlayerControlZelda(pPlayerPed, 0);
            }
        }
        else
        {
            PlayerControlFighter(pPlayerPed);
        }
        ProcessPlayerWeapon(pPlayerPed);
        m_nFrameCounter = CTimer::m_FrameCounter;
        result = 0;
    }
    else
    {
        m_nFrameCounter = CTimer::m_FrameCounter;
        result = 0;
    }
    return result;
#endif
}

bool CTaskSimplePlayerOnFoot::ProcessPlayerWeapon(CPlayerPed* pPlayerPed)
{
    return plugin::CallMethodAndReturn<bool, 0x6859A0, CTaskSimplePlayerOnFoot*, CPlayerPed*>(this, pPlayerPed);
}

void CTaskSimplePlayerOnFoot::PlayIdleAnimations(CPed* pPed)
{
    plugin::CallMethod<0x6872C0, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
}

void CTaskSimplePlayerOnFoot::PlayerControlFighter(CPlayerPed* pPlayerPed)
{
    plugin::CallMethod<0x687530, CTaskSimplePlayerOnFoot*, CPlayerPed*>(this, pPlayerPed);
}

bool CTaskSimplePlayerOnFoot::PlayerControlZeldaWeapon(CPed* pPed) 
{
    return plugin::CallMethodAndReturn<bool, 0x687C20, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
}

void CTaskSimplePlayerOnFoot::PlayerControlDucked(CPed* pPed)
{
    plugin::CallMethod<0x687F30, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
}

int CTaskSimplePlayerOnFoot::PlayerControlZelda(CPed* pPed, bool a3)
{
    return plugin::CallMethodAndReturn<int, 0x6883D0, CTaskSimplePlayerOnFoot*, CPed*, bool>(this, pPed, a3);
}