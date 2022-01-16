/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Rect.h"
#include "Vector.h"
#include "Object.h"

class CPed;

// Each area code can have one or more interiors.
// For more info, check https://wiki.mtasa.com/wiki/Interior_IDs
enum eAreaCodes {
    AREA_CODE_NORMAL_WORLD,
    AREA_CODE_1,
    AREA_CODE_2,
    AREA_CODE_3,
    AREA_CODE_4,
    AREA_CODE_5,
    AREA_CODE_6,
    AREA_CODE_7,
    AREA_CODE_8,
    AREA_CODE_9,
    AREA_CODE_10,
    AREA_CODE_11,
    AREA_CODE_12,
    AREA_CODE_13,
    AREA_CODE_14,
    AREA_CODE_15,
    AREA_CODE_16,
    AREA_CODE_17,
    AREA_CODE_18,
};

class CEntryExit {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CEntryExit)

public:
    char    m_szName[8];
    CRect   m_recEntrance;
    float   m_fEntranceZ;
    float   m_fEntranceAngle;
    CVector m_vecExitPos;
    float   m_fExitAngle;
    struct {
        uint16 bUnknownInterior : 1;
        uint16 bUnknownPairing : 1;
        uint16 bCreateLinkedPair : 1;
        uint16 bRewardInterior : 1;
        uint16 bUsedRewardEntrance : 1;
        uint16 bCarsAndAircraft : 1;
        uint16 bBikesAndMotorcycles : 1;
        uint16 bDisableOnFoot : 1;

        uint16 bAcceptNpcGroup : 1;
        uint16 bFoodDateFlag : 1;
        uint16 bUnknownBurglary : 1;
        uint16 bDisableExit : 1;
        uint16 bBurglaryAccess : 1;
        uint16 bEnteredWithoutExit : 1;
        uint16 bEnableAccess : 1;
        uint16 bDeleteEnex : 1;
    } m_nFlags;
    uint8       m_nArea;
    uint8       m_nSkyColor;
    uint8       m_nTimeOn;
    uint8       m_nTimeOff;
    uint8       m_nNumberOfPeds;
    char        _pad37;
    CEntryExit* m_pLink;

    static bool &ms_bWarping;
     static CObject *&ms_pDoor;
     static CEntryExit *&ms_spawnPoint;

 public:
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
