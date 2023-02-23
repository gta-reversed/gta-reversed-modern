#pragma once

#include <span>

#include "Vector.h"
#include "ActiveOccluder.h"
#include "Occluder.h"

class COcclusion {
public:
    static constexpr int32 MAX_INTERIOR_OCCLUDERS            = 40;
    static constexpr int32 MAX_MAP_OCCLUDERS                 = 1000;
    static constexpr int32 MAX_ACTIVE_OCCLUDERS              = 28;
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
    static auto GetActiveOccluders() { return aActiveOccluders | rng::views::take((size_t)NumActiveOccluders); }
};
