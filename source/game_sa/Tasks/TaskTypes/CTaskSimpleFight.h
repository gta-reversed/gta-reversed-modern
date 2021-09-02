/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"
#include "CEntity.h"

enum eFightAttackType : int8 {
    FIGHT_ATTACK_HIT_1 = 0,
    FIGHT_ATTACK_HIT_2 = 1,
    FIGHT_ATTACK_HIT_3 = 2,
    FIGHT_ATTACK_FIGHT_BLOCK = 3,
    FIGHT_ATTACK_FIGHTIDLE = 4,
};

class CMeleeInfo {
public:
    int32            m_dwAnimGroup;
    float          m_fRanges;
    float          m_fHit[5];
    float          m_fChain[5];
    float          m_fRadius[5];
    float          m_fGroundLoop;
    int32            ABlockHit;
    int32            ABlockChain;
    char           m_nHitLevel;
    char           __pad0[3];
    int32            damage;
    int32            field_58;
    int32            hit[5];
    int32            altHit[5];
    uint16 m_wFlags;
    char           __pad1[2];
};

VALIDATE_SIZE(CMeleeInfo, 0x88);

class CTaskSimpleFight : public CTaskSimple {
public:
    bool                   m_bIsFinished;
    bool                   m_bIsInControl;
    bool                   m_bAnimsReferenced;
    char                   _pad;
    uint32           m_nRequiredAnimGroup;
    uint16         m_nIdlePeriod;
    uint16         m_nIdleCounter;
    char                   m_nContinueStrike;
    char                   m_nChainCounter;
    char                   _pad2[2];
    CEntity*               m_pTargetEntity;
    CAnimBlendAssociation* m_pAnim;
    CAnimBlendAssociation* m_pIdleAnim;
    char                   m_nComboSet;
    eFightAttackType       m_nCurrentMove;
    uint8          m_nNextCommand;
    uint8          m_nLastCommand;

    static CMeleeInfo* m_aComboData; // m_aComboData[12];

public:
    CTaskSimpleFight* Constructor(CEntity* pTargetEntity, int32 nCommand, uint32 nIdlePeriod = 10000);
    bool ControlFight(CEntity* pEntity, uint8 command);
    bool IsComboSet();
    bool IsHitComboSet();
    int32 GetComboAnimGroupID();
    static void LoadMeleeData();
};

VALIDATE_SIZE(CTaskSimpleFight, 0x28);
