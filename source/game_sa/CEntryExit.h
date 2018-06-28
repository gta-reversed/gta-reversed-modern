/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CRect.h"
#include "CVector.h"
#include "CObject.h"

class CPed;

class  CEntryExit {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CEntryExit)

public:
    char m_szName[8];
    CRect m_recEntrance;
    float m_fEntranceZ;
    float m_fEntranceAngle;
    CVector m_vecExitPos;
    float m_fExitAngle;
    struct {
        unsigned short bUnknownInterior : 1;
        unsigned short bUnknownPairing : 1;
        unsigned short bCreateLinkedPair : 1;
        unsigned short bRewardInterior : 1;
        unsigned short bUsedRewardEntrance : 1;
        unsigned short bCarsAndAircraft : 1;
        unsigned short bBikesAndMotorcycles : 1;
        unsigned short bDisableOnFoot : 1;

        unsigned short bAcceptNpcGroup : 1;
        unsigned short bFoodDateFlag : 1;
        unsigned short bUnknownBurglary : 1;
        unsigned short bDisableExit : 1;
        unsigned short bBurglaryAccess : 1;
        unsigned short bEnteredWithoutExit : 1;
        unsigned short bEnableAccess : 1;
        unsigned short bDeleteEnex : 1;
    } m_nFlags;
    unsigned char m_nArea;
    unsigned char m_nSkyColor;
    unsigned char m_nTimeOn;
    unsigned char m_nTimeOff;
    unsigned char m_nNumberOfPeds;
private:
    char _pad37;
public:
    CEntryExit *m_pLink;

     static bool &ms_bWarping;
     static CObject *&ms_pDoor;
     static CEntryExit *&ms_spawnPoint;

     void GenerateAmbientPeds(CVector const &position);
     CEntryExit *GetEntryExitToDisplayNameOf();
     void GetPositionRelativeToOutsideWorld(CVector &positionInOut);
     bool IsInArea(CVector const &position);
     void RequestAmbientPeds();
     void RequestObjectsInFrustum();
     bool TransitionFinished(CPed *player);
     bool TransitionStarted(CPed *player);
     void WarpGangWithPlayer(CPed *player);
};

VALIDATE_SIZE(CEntryExit, 0x3C);

//#include "meta/meta.CEntryExit.h"
