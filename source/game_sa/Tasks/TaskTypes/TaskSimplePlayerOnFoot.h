/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"

extern int32& gLastRandomNumberForIdleAnimationID;
extern uint32& gLastTouchTimeDelta;
extern float& gDuckAnimBlendData;
extern bool& gbUnknown_8D2FE8;

class CPed;

class CTaskSimplePlayerOnFoot : public CTaskSimple {
public:
    int32          m_nAnimationBlockIndex;
    uint32 m_nFrameCounter;
    int32          m_nTimer;
    int32          dword_14;           // always 0
    CEntity*     m_pLookingAtEntity; // always 0

public:
    static void InjectHooks();

    bool ProcessPed(class CPed* ped) override;

    bool ProcessPed_Reversed(class CPed* ped);

    CTaskSimplePlayerOnFoot* Constructor();
    CTaskSimplePlayerOnFoot* Destructor();
    void ProcessPlayerWeapon(CPlayerPed* pPlayerPed);
    void PlayIdleAnimations(CPed* pPed);
    void PlayerControlFighter(CPlayerPed* pPlayerPed);
    void PlayerControlZeldaWeapon(CPlayerPed* pPlayerPed);
    void PlayerControlDucked(CPed* pPed);
    int32 PlayerControlZelda(CPed* pPed, bool bAvoidJumpingAndDucking);
};

VALIDATE_SIZE(CTaskSimplePlayerOnFoot, 0x1C);
