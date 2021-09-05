#pragma once

#include "CVector2D.h"
#include "CVector.h"

struct CActiveOccluderLine {
    CVector2D m_vecOrigin;
    CVector2D m_vecDirection;
    float     m_fLength;
};
VALIDATE_SIZE(CActiveOccluderLine, 0x14);

struct CActiveOccluder {
    CActiveOccluderLine m_aLines[6];
    int16               m_wDepth;
    uint8               m_cLinesCount;
    uint8               m_cNumVectors;
    CVector             m_aVectors[3];
    float               m_afRadiuses[3];

public:
    bool IsPointWithinOcclusionArea(float fX, float fY, float fRadius);
    bool IsPointBehindOccluder(CVector vecPos, float fRadius);
};
VALIDATE_SIZE(CActiveOccluder, 0xAC);

struct COccluder {
    int16 m_wMidX;
    int16 m_wMidY;
    int16 m_wMidZ;
    int16 m_wLength;
    int16 m_wWidth;
    int16 m_wHeight;
    uint8 m_cRotZ;
    uint8 m_cRotY;
    uint8 m_cRotX;
    char  _pad;
    struct {
        int16 m_nNextIndex : 15;
        int16 m_bFarAway : 1;
    };

public:
    bool ProcessOneOccluder(CActiveOccluder* pActiveOccluder);
    bool ProcessLineSegment(int32 iInd1, int32 iInd2, CActiveOccluder* pActiveOccluder);
    bool NearCamera();
};
VALIDATE_SIZE(COccluder, 0x12);

class COcclusion {
public:
    static constexpr int32 MAX_INTERIOR_OCCLUDERS = 40;
    static constexpr int32 MAX_MAP_OCCLUDERS = 1000;
    static constexpr int32 MAX_ACTIVE_OCCLUDERS = 28;
    static constexpr int32 NUM_OCCLUDERS_PROCESSED_PER_FRAME = 16;

    static COccluder (&aInteriorOccluders)[MAX_INTERIOR_OCCLUDERS];
    static COccluder (&aOccluders)[MAX_MAP_OCCLUDERS];
    static CActiveOccluder (&aActiveOccluders)[MAX_ACTIVE_OCCLUDERS];

    static int32& NumInteriorOcculdersOnMap;
    static int32& NumOccludersOnMap;
    static int32& NumActiveOccluders;
    static int16& FarAwayList;
    static int16& NearbyList;
    static int16& ListWalkThroughFA;
    static int16& PreviousListWalkThroughFA;

    static float& gMinXInOccluder;
    static float& gMaxXInOccluder;
    static float& gMinYInOccluder;
    static float& gMaxYInOccluder;

    static bool (&gOccluderCoorsValid)[8];
    static CVector (&gOccluderCoors)[8];
    static CVector (&gOccluderCoorsOnScreen)[8];
    static CVector& gCenterOnScreen;

public:
    static void InjectHooks();

public:
    static void Init();
    static void AddOne(float centerX, float centerY, float centerZ, float width, float length, float height, float rotZ, float rotY, float rotX, uint32 flags, bool isInterior);
    static bool OccluderHidesBehind(CActiveOccluder* first, CActiveOccluder* second);
    static bool IsPositionOccluded(CVector vecPos, float fRadius);
    static void ProcessBeforeRendering();
};
