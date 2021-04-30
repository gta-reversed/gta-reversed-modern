/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "C3dMarker.h"

struct tUser3dMarker {
    bool         m_bIsUsed;
private:
    char _pad1[3];
public:
    CVector      m_vecPosition;
    unsigned int m_nRed;
    unsigned int m_nGreen;
    unsigned int m_nBlue;
};

VALIDATE_SIZE(tUser3dMarker, 0x1C);

struct tDirectionArrow {
    bool         m_bIsUsed;
private:
    char _pad1[3];
public:
    CVector      m_vecPosition;
    float        m_fSize;
    CVector      m_vecDirection;
    unsigned int m_nRed;
    unsigned int m_nGreen;
    unsigned int m_nBlue;
    unsigned int m_nAlpha;
};

VALIDATE_SIZE(tDirectionArrow, 0x30);

extern unsigned int MAX_NUM_3DMARKERS; // default 32
extern unsigned int MAX_NUM_USER_3DMARKERS; // default 5
extern unsigned int MAX_NUM_DIRECTION_ARROWS; // default 5

class C3dMarkers {
public:
    static unsigned char &m_colDiamond; // default 255
    static tDirectionArrow *ms_directionArrows;
    static CRGBA &m_user3dMarkerColor;
    static tUser3dMarker *ms_user3dMarkers;
    static bool &IgnoreRenderLimit;
    static float &m_angleDiamond;
    static unsigned int &NumActiveMarkers;
    static C3dMarker *m_aMarkerArray;
    static RpClump **m_pRpClumpArray;

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void Shutdown();
    // returns slot index; -1 if not found
    static int DirectionArrowFindFirstFreeSlot();
    static void DirectionArrowSet(CVector posn, float size, int red, int green, int blue, int alpha, float dir_x, float dir_y, float dir_z);
    static void DirectionArrowsDraw();
    static void DirectionArrowsInit();
    static void ForceRender(unsigned char bEnable);
    static RpClump* LoadMarker(char const* modelName);
    // load user 3d markers from save file; always return true
    static bool LoadUser3dMarkers();
    static C3dMarker* PlaceMarker(unsigned int id, unsigned short type, CVector& posn, float size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, unsigned short pulsePeriod, float pulseFraction, short rotateRate, float nrm_x, float nrm_y, float nrm_z, bool zCheck);
    static void PlaceMarkerCone(unsigned int id, CVector& posn, float size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, unsigned short pulsePeriod, float pulseFraction, short rotateRate, unsigned char bEnableCollision);
    static void PlaceMarkerSet(unsigned int id, unsigned short type, CVector& posn, float size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, unsigned short pulsePeriod, float pulseFraction, short rotateRate);
    static void Render();
    // save user 3d markers to save file; always return true
    static void SaveUser3dMarkers();
    // only set material color (m_user3dMarkerColor) for first material in first atomic; 'data' is unused
    static RpAtomic* User3dMarkerAtomicCB(RpAtomic* atomic, void* _IGNORED_ data);
    static void User3dMarkerDelete(int slotIndex);
    static void User3dMarkerDeleteAll();
    // returns slot index; -1 if not found
    static int User3dMarkerFindFirstFreeSlot();
    // returns slot index; -1 if not created; for 'colour', see eHudColours 
    static int User3dMarkerSet(float x, float y, float z, int colour);
    static void User3dMarkersDraw();
};

// 'data' is a pointer to store atomic (RpAtomic **)
RpAtomic* MarkerAtomicCB(RpAtomic* atomic, void* data);
