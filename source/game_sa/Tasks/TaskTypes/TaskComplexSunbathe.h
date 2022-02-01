/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskComplex.h"
#include "TaskTimer.h"
#include "AnimBlock.h"
#include "Object.h"

enum eSunbatherType : uint32
{
    SUNBATHER_MALE_1 = 0,
    SUNBATHER_MALE_2,
    SUNBATHER_FEMALE_1,
    SUNBATHER_FEMALE_2,
    SUNBATHER_FEMALE_3,
};

class CTaskComplexSunbathe : public CTaskComplex {
public:
    bool                m_bStartStanding;
    bool                m_bBathing;
    bool                m_bBeachAnimsReferenced;
    bool                m_bSunbatheAnimsReferenced;
    bool                m_bAborted;
private:
    char _pad[3];
public:
    CTaskTimer          m_BathingTimer;
    eSunbatherType      m_SunbatherType;
    CAnimBlock*         m_pBeachAnimBlock;
    CAnimBlock*         m_pSunbatheAnimBlock;
    int32               m_BeachAnimBlockIndex;
    int32               m_SunbatheAnimBlockIndex;
    CObject*            m_pTowel;

    CTaskComplexSunbathe(CObject* pTowel, bool bStartStanding);
};

VALIDATE_SIZE(CTaskComplexSunbathe, 0x38);

