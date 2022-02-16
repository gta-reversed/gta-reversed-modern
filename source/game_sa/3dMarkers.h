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

class C3dMarkers {
public:
    static inline uint8& m_colDiamond = *(uint8*)0x8D5D8B; // default 255
    static inline CRGBA& m_user3dMarkerColor = *(CRGBA*)0xC7C620;
    static inline bool& IgnoreRenderLimit = *(bool*)0xC7C704;
    static inline float& m_angleDiamond = *(float*)0xC7C700;
    static inline uint32& NumActiveMarkers = *(uint32*)0xC7C6D8;
    static inline std::array<RpClump*, 7>& m_pRpClumpArray = *(std::array<RpClump*, 7>*)0xC7C6DC;
    static inline std::array<tDirectionArrow, MAX_NUM_DIRECTION_ARROWS>& ms_directionArrows = *(std::array<tDirectionArrow, MAX_NUM_DIRECTION_ARROWS>*)0xC802E8;
    static inline std::array<tUser3dMarker, MAX_NUM_USER_3DMARKERS>& ms_user3dMarkers = *(std::array<tUser3dMarker, MAX_NUM_USER_3DMARKERS>*)0xC80258;
    static inline std::array<C3dMarker, MAX_NUM_3DMARKERS>& m_aMarkerArray = *(std::array<C3dMarker, MAX_NUM_3DMARKERS>*)0xC7DD58;

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void Shutdown();
    static void Render();

    static int32 DirectionArrowFindFirstFreeSlot();
    static void  DirectionArrowSet(CVector posn, float size, int32 red, int32 green, int32 blue, int32 alpha, float dir_x, float dir_y, float dir_z);
    static void  DirectionArrowsDraw();
    static void  DirectionArrowsInit();
    static void  ForceRender(bool ignore);
    static inline RpClump* LoadMarker(const char* modelName);

    static C3dMarker* PlaceMarker(uint32 id, e3dMarkerType type, CVector& posn, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate, float nrm_x, float nrm_y, float nrm_z, bool zCheck);
    static void PlaceMarkerCone(uint32 id, CVector& point, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate, bool bEnableCollision);
    static void PlaceMarkerSet(uint32 id, e3dMarkerType type, CVector& posn, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate);

    static RpAtomic* User3dMarkerAtomicCB(RpAtomic* atomic, void* data);
    static void User3dMarkerDelete(int32 slotIndex);
    static void User3dMarkerDeleteAll();
    static int32 User3dMarkerFindFirstFreeSlot();
    static int32 User3dMarkerSet(float x, float y, float z, int32 color);
    static void User3dMarkersDraw();

    static bool LoadUser3dMarkers();
    static bool SaveUser3dMarkers();
};

RpAtomic* MarkerAtomicCB(RpAtomic* atomic, void* data);
