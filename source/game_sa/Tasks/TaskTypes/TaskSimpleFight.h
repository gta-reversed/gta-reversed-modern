/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "AnimBlendAssociation.h"
#include "Entity.h"

enum eFightAttackType : int8 {
    FIGHT_ATTACK_HIT_1 = 0,
    FIGHT_ATTACK_HIT_2 = 1,
    FIGHT_ATTACK_HIT_3 = 2,
    FIGHT_ATTACK_FIGHT_BLOCK = 3,
    FIGHT_ATTACK_FIGHTIDLE = 4,
};

class CMeleeInfo {
public:
    int32  m_dwAnimGroup;
    float  m_fRanges;
    float  m_fHit[5];
    float  m_fChain[5];
    float  m_fRadius[5];
    float  m_fGroundLoop;
    int32  ABlockHit;
    int32  ABlockChain;
    uint8  m_nHitLevel;
    char   _pad0[3];
    int32  damage;
    int32  field_58;
    int32  hit[5];
    int32  altHit[5];
    uint16 m_wFlags;
    char   _pad1[2];
};

VALIDATE_SIZE(CMeleeInfo, 0x88);

class CPed;
class CPlayerPed;

class CTaskSimpleFight : public CTaskSimple {
public:
    bool                   m_bIsFinished;
    bool                   m_bIsInControl;
    bool                   m_bAnimsReferenced;
    char                   _pad;
    uint32                 m_nRequiredAnimGroup;
    uint16                 m_nIdlePeriod;
    uint16                 m_nIdleCounter;
    char                   m_nContinueStrike;
    char                   m_nChainCounter;
    char                   _pad2[2];
    CEntity*               m_pTargetEntity;
    CAnimBlendAssociation* m_pAnim;
    CAnimBlendAssociation* m_pIdleAnim;
    uint8                  m_nComboSet;
    eFightAttackType       m_nCurrentMove;
    uint8                  m_nNextCommand;
    uint8                  m_nLastCommand;

    static CMeleeInfo* m_aComboData; // m_aComboData[12];

public:
    CTaskSimpleFight(CEntity* entity, int32 nCommand, uint32 nIdlePeriod = 10000);
    ~CTaskSimpleFight() override;

    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_SIMPLE_FIGHT_CTRL; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    static void LoadMeleeData();

    void BeHitWhileBlocking(CPed* ped1, CPed* ped2, int8, int8);
    void ChooseAttackAI(CPed* ped);
    void ChooseAttackPlayer(CPed* ped);
    bool ControlFight(CEntity* entity, uint8 command);

    void FightHitCar(CPed* ped, CVehicle* vehicle, CVector& posn1, CVector& posn2, int16, int8);
    void FightHitObj(CPed* ped, CObject* object, CVector& posn1, CVector& posn2, int16, int8);
    void FightHitPed(CPed* creator, CPed* victim, CVector& posn1, CVector& posn2, int16);
    void FightSetUpCol(float);
    void FightStrike(CPed* ped, CVector& posn);

    void FindTargetOnGround(CPed* ped);
    void FinishMeleeAnimCB(CAnimBlendAssociation*, void*);

    bool IsComboSet();
    bool IsHitComboSet();

    void GetAvailableComboSet(CPed* ped, int8);
    void GetComboType(char*);
    int32 GetComboAnimGroupID();
    void GetHitLevel(const char*);
    void GetHitSound(int32);
    void GetRange();
    void GetStrikeDamage(CPed* ped);

    void SetPlayerMoveAnim(CPlayerPed* player);
    void StartAnim(CPed* ped, int32);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleFight* Constructor(CEntity* entity, int32 nCommand, uint32 nIdlePeriod);
    CTaskSimpleFight* Destructor();

    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleFight, 0x28);


