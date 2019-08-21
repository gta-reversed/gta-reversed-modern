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

class CPed;
class  CTaskSimplePlayerOnFoot : public CTaskSimple {
protected:
    CTaskSimplePlayerOnFoot(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    int m_nAnimationBlockIndex;
    unsigned int m_nFrameCounter;
    int m_nTimer;
    int dword_14; // always 0
    int dword_18; // always 0

    CTaskSimplePlayerOnFoot* Constructor();
    CTaskSimplePlayerOnFoot* Destructor();
    bool ProcessPed(CPed* pPed);
    bool ProcessPlayerWeapon(CPlayerPed* pPlayerPed);
    void PlayIdleAnimations(CPed* pPed);
    void PlayerControlFighter(CPlayerPed* pPlayerPed);
    bool PlayerControlZeldaWeapon(CPed* pPed);
    void PlayerControlDucked(CPed* pPed);
    int  PlayerControlZelda(CPed* pPed, bool a3);

};

VALIDATE_SIZE(CTaskSimplePlayerOnFoot, 0x1C);
