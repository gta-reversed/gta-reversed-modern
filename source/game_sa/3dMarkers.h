/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "3dMarker.h"
#include "RGBA.h"
#include "Vector.h"

struct RpClump;
struct RpAtomic;

struct tUser3dMarker {
    bool    m_bIsUsed;
    CVector m_vecPosition;
    uint32  m_nRed;
    uint32  m_nGreen;
    uint32  m_nBlue;
};

VALIDATE_SIZE(tUser3dMarker, 0x1C);

struct tDirectionArrow {
    bool    m_bIsUsed;
    CVector m_vecPosition;
    float   m_fSize;
    CVector m_vecDirection;
    uint32  m_nRed;
    uint32  m_nGreen;
    uint32  m_nBlue;
    uint32  m_nAlpha;
};

VALIDATE_SIZE(tDirectionArrow, 0x30);

extern uint32 MAX_NUM_3DMARKERS; // default 32
extern uint32 MAX_NUM_USER_3DMARKERS; // default 5
extern uint32 MAX_NUM_DIRECTION_ARROWS; // default 5

class C3dMarkers {
public:
    static uint8 &m_colDiamond; // default 255
    static tDirectionArrow *ms_directionArrows;
    static CRGBA &m_user3dMarkerColor;
    static tUser3dMarker *ms_user3dMarkers;
    static bool &IgnoreRenderLimit;
    static float &m_angleDiamond;
    static uint32 &NumActiveMarkers;
    static C3dMarker *m_aMarkerArray;
    static RpClump **m_pRpClumpArray;

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void Shutdown();
    // returns slot index; -1 if not found
    static int32 DirectionArrowFindFirstFreeSlot();
    static void DirectionArrowSet(CVector posn, float size, int32 red, int32 green, int32 blue, int32 alpha, float dir_x, float dir_y, float dir_z);
    static void DirectionArrowsDraw();
    static void DirectionArrowsInit();
    static void ForceRender(uint8 bEnable);
    static RpClump* LoadMarker(const char* modelName);

    static C3dMarker* PlaceMarker(uint32 id, uint16 type, CVector& posn, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate, float nrm_x, float nrm_y, float nrm_z, bool zCheck);
    static void PlaceMarkerCone(uint32 id, CVector& posn, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate, uint8 bEnableCollision);
    static void PlaceMarkerSet(uint32 id, uint16 type, const CVector& posn, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate);
    static void Render();

    // load user 3d markers from save file; always return true
    static bool LoadUser3dMarkers();
    // save user 3d markers to save file; always return true
    static bool SaveUser3dMarkers();

    // only set material color (m_user3dMarkerColor) for first material in first atomic; 'data' is unused
    static RpAtomic* User3dMarkerAtomicCB(RpAtomic* atomic, void* _IGNORED_ data);
    static void User3dMarkerDelete(int32 slotIndex);
    static void User3dMarkerDeleteAll();
    // returns slot index; -1 if not found
    static int32 User3dMarkerFindFirstFreeSlot();
    // returns slot index; -1 if not created; for 'colour', see eHudColours 
    static int32 User3dMarkerSet(float x, float y, float z, int32 colour);
    static void User3dMarkersDraw();
};

// 'data' is a pointer to store atomic (RpAtomic **)
RpAtomic* MarkerAtomicCB(RpAtomic* atomic, void* data);
