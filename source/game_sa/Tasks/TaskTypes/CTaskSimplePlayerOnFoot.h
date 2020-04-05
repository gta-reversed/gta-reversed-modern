/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"

extern int& gLastRandomNumberForIdleAnimationID;
extern unsigned int& gLastTouchTimeDelta;
extern float& gDuckAnimBlendData;
extern bool& gbUnknown_8D2FE8;

class CPed;
class  CTaskSimplePlayerOnFoot : public CTaskSimple {
public:
    int m_nAnimationBlockIndex;
    unsigned int m_nFrameCounter;
    int m_nTimer;
    int dword_14; // always 0
    CEntity* m_pLookingAtEntity; // always 0

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
    int  PlayerControlZelda(CPed* pPed, bool bAvoidJumpingAndDucking);

};

VALIDATE_SIZE(CTaskSimplePlayerOnFoot, 0x1C);
