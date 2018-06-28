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
#include "CWeaponInfo.h"



class  CTaskSimpleGangDriveBy : public CTaskSimple {
protected:
    CTaskSimpleGangDriveBy(plugin::dummy_func_t a) : CTaskSimple(a) {}
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
    char m_nFrequencyPercentage;
    char m_nFakeShootDirn;
private:
    char _pad;
public:
    short m_nAttackTimer;
    unsigned int m_nLOSCheckTime;
    bool m_nLOSBlocked;
private:
    char _pad2[3];
public:
    float m_fAbortRange;
    int m_nRequiredAnimID;
    int m_nRequiredAnimGroup;
    CAnimBlendAssociation *m_pAnim;
    CWeaponInfo *m_pWeaponInfo;
    CEntity *m_pTargetEntity;
    CVector m_vecCoords;

    CTaskSimpleGangDriveBy(CEntity *pTargetEntity, const CVector *pVecTarget, float fAbortRange, 
        char FrequencyPercentage, char nDrivebyStyle, bool bSeatRHS);
};

VALIDATE_SIZE(CTaskSimpleGangDriveBy, 0x44);

