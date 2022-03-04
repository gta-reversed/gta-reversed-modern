/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Rect.h"
#include "Vector.h"

class CObject;
class CPed;
class CEntryExit;

class CEntryExit {
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
    // char        _pad37;
    CEntryExit* m_pLink;

    static bool& ms_bWarping;
    static CObject*& ms_pDoor;
    static CEntryExit*& ms_spawnPoint;

public:
    static void InjectHooks();

    void GenerateAmbientPeds(const CVector& posn);
    CEntryExit* GetEntryExitToDisplayNameOf();
    void GetPositionRelativeToOutsideWorld(CVector& outPos);
    bool IsInArea(const CVector& position);
    void RequestAmbientPeds();
    void RequestObjectsInFrustum() const;
    bool TransitionFinished(CPed* ped);
    bool TransitionStarted(CPed* ped);
    void WarpGangWithPlayer(CPed* ped);
    void ProcessStealableObjects(CPed* ped);
    void FindValidTeleportPoint(CVector* point);
};

VALIDATE_SIZE(CEntryExit, 0x3C);
