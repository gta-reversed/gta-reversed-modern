/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class CEntity;
class CPed;

class  CCoverPoint {
public:
    char m_nMaxPedsInCover;
    char m_nCoverType;
    char m_nDirection;
private:
    char _pad3;
public:
    CVector m_vecOffset;
    CEntity *m_pCoverEntity;
    CPed *m_apCoveredPeds[2];

     bool CanAccomodateAnotherPed();
     void ReleaseCoverPointForPed(CPed *ped);
     void ReserveCoverPointForPed(CPed *ped);
};

VALIDATE_SIZE(CCoverPoint, 0x1C);

//#include "meta/meta.CCoverPoint.h"
