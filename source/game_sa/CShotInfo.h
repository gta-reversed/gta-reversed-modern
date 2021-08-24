/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "eWeaponType.h"

class CEntity;

class  CShotInfo {
public:
    int      m_nWeaponType;
    CVector  m_vecOrigin;
    CVector  m_vecTargetOffset;
    float    m_fRange;
    CEntity *m_pCreator;
    int      m_nDestroyTime;
    bool     m_bExist;
    bool     m_bExecuted;
private:
    char _pad2A[2];
public:

    static float *ms_afRandTable; // static float ms_afRandTable[20]

    static void Initialise();
    // dummy function
    static void Shutdown();
    static bool AddShot(CEntity* creator, eWeaponType weaponType, CVector origin, CVector target);
    static bool GetFlameThrowerShotPosn(unsigned char shotId, CVector* outPosn);
    static void Update();
};

VALIDATE_SIZE(CShotInfo, 0x2C);

extern unsigned int MAX_SHOT_INFOS; // default 100
extern CShotInfo *aShotInfos; // CShotInfo aShotInfos[MAX_SHOT_INFOS]
