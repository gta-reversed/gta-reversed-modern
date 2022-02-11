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
#include "WeaponInfo.h"

class CTaskSimpleGangDriveBy : public CTaskSimple {
public:
    bool                   m_bIsFinished;
    bool                   m_bAnimsReferenced;
    bool                   m_bSeatRHS;
    bool                   m_bInRangeToShoot;
    bool                   m_bInWeaponRange;
    bool                   m_bReachedAbortRange;
    bool                   m_bFromScriptCommand;
    char                   m_nNextCommand;
    char                   m_nLastCommand;
    char                   m_nBurstShots;
    char                   m_nDrivebyStyle;
    int8                   m_nFrequencyPercentage;
    char                   m_nFakeShootDirn;
    char                   _pad;
    int16                  m_nAttackTimer;
    uint32                 m_nLOSCheckTime;
    bool                   m_nLOSBlocked;
    char                   _pad2[3];
    float                  m_fAbortRange;
    int32                  m_nRequiredAnimID;
    int32                  m_nRequiredAnimGroup;
    CAnimBlendAssociation* m_pAnimAssoc;
    CWeaponInfo*           m_pWeaponInfo;
    CEntity*               m_pTargetEntity;
    CVector                m_vecCoords;

public:
    CTaskSimpleGangDriveBy(CEntity *target, const CVector *targetPos, float abortRange, int8 frequencyPercentage, int8 drivebyStyle, bool seatRHS);
    ~CTaskSimpleGangDriveBy();

    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_SIMPLE_GANG_DRIVEBY; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
};

VALIDATE_SIZE(CTaskSimpleGangDriveBy, 0x44);

