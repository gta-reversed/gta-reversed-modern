/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "3dMarker.h"

struct tUser3dMarker {
    bool m_bIsUsed;
    CVector m_vecPosition;
    uint32 m_nRed;
    uint32 m_nGreen;
    uint32 m_nBlue;
};
VALIDATE_SIZE(tUser3dMarker, 0x1C);

struct tDirectionArrow {
    bool m_bIsUsed;
    CVector m_vecPosition;
    float m_fSize;
    CVector m_vecDirection;
    uint32 m_nRed;
    uint32 m_nGreen;
    uint32 m_nBlue;
    uint32 m_nAlpha;
};
VALIDATE_SIZE(tDirectionArrow, 0x30);

#define MAX_NUM_3DMARKERS 32
#define MAX_NUM_USER_3DMARKERS 5
#define MAX_NUM_DIRECTION_ARROWS 5

class C3dMarkers {
public:
    static uint8& m_colDiamond; // default 255
    static CRGBA& m_user3dMarkerColor;
    static int32& NumActiveMarkers;
    static RpClump* (&m_pRpClumpArray)[e3dMarkerType::MARKER3D_NUM];
    static float& m_angleDiamond;
    static bool& IgnoreRenderLimit;
    static C3dMarker (&m_aMarkerArray)[MAX_NUM_3DMARKERS];
    static tUser3dMarker (&ms_user3dMarkers)[MAX_NUM_USER_3DMARKERS];
    static tDirectionArrow (&ms_directionArrows)[MAX_NUM_DIRECTION_ARROWS];

public:
    static void InjectHooks();

    // load user 3d markers from save file; always return true
    static int32 LoadUser3dMarkers();
    static C3dMarker* PlaceMarker(uint32 id, uint16 type, CVector& posn, float size, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction,
                                  uint16 rotateRate, float nrm_x, float nrm_y, float nrm_z, bool zCheck);
    static int32 Render();
    static int32 Init();
    static void User3dMarkersDraw();
    static void ForceRender(uint8 enable);
    static RpClump* LoadMarker(char const* name);
    static void Update();
    static void Shutdown();
    static void PlaceMarkerSet(uint32 id, uint16 type, CVector& posn, float size, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction);
    static void DirectionArrowsDraw();
    // returns slot index; -1 if not found
    static int32 DirectionArrowFindFirstFreeSlot();
    static void DirectionArrowsInit();
    // only set material color (m_user3dMarkerColor) for first material in first atomic; 'data' is unused
    static RpAtomic* User3dMarkerAtomicCB(RpAtomic* a1);
    static void User3dMarkerDeleteAll();
    static void User3dMarkerDelete(int32 a1);
    // returns slot index; -1 if not created; for 'colour', see eHudColours
    static int32 User3dMarkerSet(float x, float y, float z, int32 color);
    // returns slot index; -1 if not found
    static int32 User3dMarkerFindFirstFreeSlot();
    // save user 3d markers to save file; always return true
    static int32 SaveUser3dMarkers();
    static void DirectionArrowSet(CVector posn, float size, int red, int green, int blue, int alpha, float dir_x, float dir_y, float dir_z);
    static void DirectionArrowSet(CVector posn, float size, CRGBA color, CVector dir) {
        return DirectionArrowSet(posn, size, color.r, color.g, color.b, color.a, dir.x, dir.y, dir.z);
    }
    static void PlaceMarkerCone(uint32 id, CVector& posn, float size, uint8 r, uint8 g, uint8 b, uint8 alpha, uint16 pulsePeriod, float pulseFraction, uint16 type,
                                uint8 bEnableCollision);
};
