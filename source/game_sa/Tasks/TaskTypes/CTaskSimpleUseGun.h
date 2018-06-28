    /*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CVector.h"
#include "CVector2D.h"
#include "CWeaponInfo.h"
#include "CAnimBlendAssociation.h"
#include "CEntity.h"

class CTaskSimpleUseGun : public CTaskSimple
{
protected:
    CTaskSimpleUseGun(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    bool m_bIsFinished;
    bool m_bIsInControl;
    bool m_bMoveControl;
    bool m_bFiredGun;
    bool m_bBlockedLOS;
    union
    {
        unsigned char m_nFireGunThisFrame;
        struct
        {
                unsigned char bRightHand : 1;
                unsigned char bLefttHand : 1;
        };
    };
    bool m_bSkipAim;

    unsigned char m_nNextCommand;   // 0x1 reloading - 0x2 firing
    unsigned char m_nLastCommand;	// active command - 0x1 reloading - 0x2 firing
private:
    char _pad[3];
public:
    CVector2D m_vecMoveCommand;

    CEntity *m_pTarget;
    CVector m_vecTarget;

    CAnimBlendAssociation *m_pAnim;

    CWeaponInfo *m_pWeaponInfo;
    unsigned short m_nBurstLength;
    unsigned short m_nBurstShots;

    unsigned char m_nCountDownFrames;
    bool m_ArmIKInUse;
    bool m_LookIKInUse;
    bool m_bAimImmediate;

    CTaskSimpleUseGun(CEntity *pTargetEntity, CVector vecTarget, unsigned char nCommand, unsigned short nBurstLength = 1, bool bAimImmediate = false);
};

VALIDATE_SIZE(CTaskSimpleUseGun, 0x3C);

