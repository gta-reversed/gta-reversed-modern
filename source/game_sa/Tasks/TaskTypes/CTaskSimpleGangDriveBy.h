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
#include "CWeaponInfo.h"

class CTaskSimpleGangDriveBy : public CTaskSimple {
public:
    bool m_bIsFinished;
    bool m_bAnimsReferenced;
    bool m_bSeatRHS;
    bool m_bInRangeToShoot;
    bool m_bInWeaponRange;
    bool m_bReachedAbortRange;
    bool m_bFromScriptCommand;
    char m_nNextCommand;
    char m_nLastCommand;
    char m_nBurstShots;
    char m_nDrivebyStyle;
    int8_t m_nFrequencyPercentage;
    char m_nFakeShootDirn;
    char _pad;
    short m_nAttackTimer;
    unsigned int m_nLOSCheckTime;
    bool m_nLOSBlocked;
    char _pad2[3];
    float m_fAbortRange;
    int m_nRequiredAnimID;
    int32_t m_nRequiredAnimGroup;
    CAnimBlendAssociation *m_pAnimAssoc;
    CWeaponInfo *m_pWeaponInfo;
    CEntity *m_pTargetEntity;
    CVector m_vecCoords;

public:
    CTaskSimpleGangDriveBy(CEntity *target, const CVector *targetPos, float abortRange, int8_t frequencyPercentage, int8_t drivebyStyle, bool seatRHS);
    ~CTaskSimpleGangDriveBy();

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_GANG_DRIVEBY; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
};

VALIDATE_SIZE(CTaskSimpleGangDriveBy, 0x44);

