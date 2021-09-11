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
    char                m_cLinesCount;
    char                m_cUnkn;
    CVector             m_aVectors[3];
    float               m_fRadiuses[3];

public:
    bool IsPointWithinOcclusionArea(float fX, float fY, float fRadius);
    bool IsPointBehindOccluder(CVector vecPos, float fRadius);
};
VALIDATE_SIZE(CActiveOccluder, 0xAC);

struct COccluder {
    uint16 m_fMidX;
    uint16 m_fMidY;
    uint16 m_fMidZ;
    uint16 m_fWidthY;
    uint16 m_fWidthX;
    uint16 m_fHeight;
    char   m_cRotX;
    char   m_cRotY;
    char   m_cRotZ;
    char   m_cPad;
    uint16 m_nFlags;

public:
    void ProcessOneOccluder(CActiveOccluder* pActiveOccluder);
    void ProcessLineSegment(int32 iInd1, int32 iInd2, CActiveOccluder* pActiveOccluder);
};
VALIDATE_SIZE(COccluder, 0x12);

class COcclusion {
public:
    static constexpr int32 MAX_INTERIOR_OCCLUDERS = 40;
    static constexpr int32 MAX_MAP_OCCLUDERS = 1000;
    static constexpr int32 MAX_ACTIVE_OCCLUDERS = 28;

    static COccluder(&aInteriorOccluders)[MAX_INTERIOR_OCCLUDERS];
    static COccluder(&aOccluders)[MAX_MAP_OCCLUDERS];
    static CActiveOccluder(&aActiveOccluders)[MAX_ACTIVE_OCCLUDERS];

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

    static bool(&gOccluderCoorsValid)[8];
    static CVector(&gOccluderCoors)[8];
    static CVector(&gOccluderCoorsOnScreen)[8];
    static CVector& gCenterOnScreen;

public:
    static void InjectHooks();

public:
    static void Init();
    static void AddOne(float dirMidX, float dirMidY, float dirMidZ, float widthX, float widthY, float height, float rotX, float rotY, float rotZ, int32 flags, bool isInterior);
    static bool OccluderHidesBehind(CActiveOccluder* first, CActiveOccluder* second);
    static bool IsPositionOccluded(CVector vecPos, float fRadius);
    static void ProcessBeforeRendering();
};
