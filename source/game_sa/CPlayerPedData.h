/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "CWanted.h"
#include "CPedClothesDesc.h"
#include "CVector.h"
#include "CVector2D.h"

class CEntity;
class CPed;
class CCopPed;

class CPlayerPedData {
public:
    CWanted* m_pWanted;
    CPedClothesDesc* m_pPedClothesDesc;
    CCopPed* m_pArrestingCop;
    CVector2D m_vecFightMovement;
    float m_fMoveBlendRatio;
    float m_fTimeCanRun;
    float m_fMoveSpeed;
    unsigned char m_nChosenWeapon;
    unsigned char m_nCarDangerCounter;
    char _pad0[2];
    unsigned int m_nStandStillTimer;
    unsigned int m_nHitAnimDelayTimer;
    float m_fAttackButtonCounter;
    void* m_pDangerCar;
    union {
        struct {
            unsigned int m_bStoppedMoving : 1;
            unsigned int m_bAdrenaline : 1;
            unsigned int m_bHaveTargetSelected : 1;             // Needed to work out whether we lost target this frame
            unsigned int m_bFreeAiming : 1;
            unsigned int m_bCanBeDamaged : 1;
            unsigned int m_bAllMeleeAttackPtsBlocked : 1;       // if all of m_pMeleeAttackers[] is blocked by collision, just attack straight ahead
            unsigned int m_bJustBeenSnacking : 1;               // If this bit is true we have just bought something from a vending machine
            unsigned int m_bRequireHandleBreath : 1;

            unsigned int m_bGroupStuffDisabled : 1;             // if this is true the player can't recrout or give his group commands.
            unsigned int m_bGroupAlwaysFollow : 1;              // The group is told to always follow the player (used for girlfriend missions)
            unsigned int m_bGroupNeverFollow : 1;               // The group is told to always follow the player (used for girlfriend missions)
            unsigned int m_bInVehicleDontAllowWeaponChange : 1; // stop weapon change once driveby weapon has been given
            unsigned int m_bRenderWeapon : 1;                   // set to false during cutscenes so that knuckledusters are not rendered
        };

        struct {
            unsigned char m_bPlayerFlagsByte1;
            unsigned char m_bPlayerFlagsByte2;
            unsigned char m_bPlayerFlagsByte3;
            unsigned char m_bPlayerFlagsByte4;
        };
        unsigned int m_nPlayerFlags;
    };
    unsigned int m_nPlayerGroup;
    unsigned int m_nAdrenalineEndTime;
    unsigned char m_nDrunkenness;
    unsigned char m_nFadeDrunkenness;
    unsigned char m_nDrugLevel;
    unsigned char m_nScriptLimitToGangSize;
    float m_fBreath;
    unsigned int m_nMeleeWeaponAnimReferenced;
    unsigned int m_nMeleeWeaponAnimReferencedExtra;
    float m_fFPSMoveHeading;
    float m_fLookPitch;
    float m_fSkateBoardSpeed;
    float m_fSkateBoardLean;
    RpAtomic* m_pSpecialAtomic;
    float m_fGunSpinSpeed;
    float m_fGunSpinAngle;
    unsigned int m_nLastTimeFiring;
    unsigned int m_nTargetBone;
    CVector m_vecTargetBoneOffset;
    unsigned int m_nBusFaresCollected;
    bool m_bPlayerSprintDisabled;
    bool m_bDontAllowWeaponChange;
    bool m_bForceInteriorLighting;
    char _pad1;
    unsigned short m_nPadDownPressedInMilliseconds;
    unsigned short m_nPadUpPressedInMilliseconds;
    unsigned char m_nWetness;
    bool m_bPlayersGangActive;
    unsigned char m_nWaterCoverPerc;
    char _pad2;
    float m_fWaterHeight;
    unsigned int m_nFireHSMissilePressedTime;
    CEntity* m_LastHSMissileTarget;
    unsigned int m_nModelIndexOfLastBuildingShot;
    unsigned int m_nLastHSMissileLOSTime : 31;
    unsigned int m_bLastHSMissileLOS : 1;
    CPed* m_pCurrentProstitutePed;
    CPed* m_pLastProstituteShagged;

public:
    static void InjectHooks();

    CPlayerPedData();
    CPlayerPedData * Constructor();

    ~CPlayerPedData();
    CPlayerPedData * Destructor();

    void AllocateData();
    void DeAllocateData();
    void SetInitialState();
};

VALIDATE_SIZE(CPlayerPedData, 0xAC);
