    /*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CTaskSimple.h"
#include "CVector.h"
#include "CVector2D.h"
#include "CWeaponInfo.h"
#include "CAnimBlendAssociation.h"
#include "CEntity.h"

class CTaskSimpleUseGun : public CTaskSimple
{
public:
    bool m_bIsFinished;
    bool m_bIsInControl;
    bool m_bMoveControl;
    bool m_bFiredGun;
    bool m_bBlockedLOS;
    union
    {
        uint8 m_nFireGunThisFrame;
        struct
        {
                uint8 bRightHand : 1;
                uint8 bLefttHand : 1;
        };
    };
    bool m_bSkipAim;

    uint8 m_nNextCommand;   // 0x1 reloading - 0x2 firing
    uint8 m_nLastCommand;	// active command - 0x1 reloading - 0x2 firing
private:
    char _pad[3];
public:
    CVector2D m_vecMoveCommand;

    CEntity *m_pTarget;
    CVector m_vecTarget;

    CAnimBlendAssociation *m_pAnim;

    CWeaponInfo *m_pWeaponInfo;
    uint16 m_nBurstLength;
    uint16 m_nBurstShots;

    uint8 m_nCountDownFrames;
    bool m_ArmIKInUse;
    bool m_LookIKInUse;
    bool m_bAimImmediate;

    CTaskSimpleUseGun* Constructor(CEntity *pTargetEntity, CVector vecTarget, uint8 nCommand, uint16 nBurstLength = 1, bool bAimImmediate = false);
    bool ControlGunMove(CVector2D* moveSpeed);
    bool PlayerPassiveControlGun();
    static bool RequirePistolWhip(CPed* pPed, CEntity* pTargetEntity);
    bool ControlGun(CPed* pPed, CEntity* target, char nCount);
    int32 SkipAim(CPed* pPed);
    int32 ClearAnim(CPed* pPed);
};

VALIDATE_SIZE(CTaskSimpleUseGun, 0x3C);

