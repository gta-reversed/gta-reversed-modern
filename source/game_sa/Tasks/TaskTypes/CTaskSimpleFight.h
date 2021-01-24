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
#include "CEntity.h"

enum eFightAttackType {
    FIGHT_ATTACK_HIT_1 = 0,
    FIGHT_ATTACK_HIT_2 = 1,
    FIGHT_ATTACK_HIT_3 = 2,
    FIGHT_ATTACK_FIGHT_BLOCK = 3,
    FIGHT_ATTACK_FIGHTIDLE = 4,
};

class CMeleeInfo {
public:
    int m_dwAnimGroup;
    float m_fRanges;
    float m_fHit[5];
    float m_fChain[5];
    float m_fRadius[5];
    float m_fGroundLoop;
    int ABlockHit;
    int ABlockChain;
    char m_nHitLevel;
private:
    char __pad0[3];
public:
    int damage;
    int field_58;
    int hit[5];
    int altHit[5];
    unsigned short m_wFlags;
private:
    char __pad1[2];
};

VALIDATE_SIZE(CMeleeInfo, 0x88);

class CTaskSimpleFight : public CTaskSimple {
public:

   bool m_bIsFinished;
   bool m_bIsInControl;

   bool m_bAnimsReferenced;
private:
    char _pad;
public:
   unsigned int m_nRequiredAnimGroup;

   unsigned short m_nIdlePeriod;
   unsigned short m_nIdleCounter;
   char m_nContinueStrike;
   char m_nChainCounter;
private:
    char _pad2[2];
public:

   CEntity *m_pTargetEntity;
   CAnimBlendAssociation *m_pAnim;
   CAnimBlendAssociation *m_pIdleAnim;

   char m_nComboSet;
   char m_nCurrentMove; // see eFightAttackType
   unsigned char m_nNextCommand;
   unsigned char m_nLastCommand;
    
   static CMeleeInfo* m_aComboData; // m_aComboData[12];

   CTaskSimpleFight* Constructor(CEntity *pTargetEntity, int nCommand, unsigned int nIdlePeriod = 10000);
   bool ControlFight(CEntity* pEntity, unsigned char command);
   bool IsComboSet();
   bool IsHitComboSet();
   int GetComboAnimGroupID();
   static void LoadMeleeData();
};

VALIDATE_SIZE(CTaskSimpleFight, 0x28);
