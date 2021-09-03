/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CVehicle.h"
#include "CBaseModelInfo.h"
#include "CPtrListDoubleLink.h"

enum eRendererVisiblity {
    RENDERER_INVISIBLE = 0,
    RENDERER_VISIBLE,
    RENDERER_CULLED,
    RENDERER_STREAMME
};

struct tScanLists {
    CPtrListDoubleLink* buildingsList;
    CPtrListDoubleLink* objectsList;
    CPtrListDoubleLink* vehiclesList;
    CPtrListDoubleLink* pedsList;
    CPtrListDoubleLink* dummiesList;
};

VALIDATE_SIZE(tScanLists, 0x14);

struct tRenderListEntry {
    CEntity* pEntity;
    float distance;
};

VALIDATE_SIZE(tRenderListEntry, 8);

extern int32 MAX_INVISIBLE_ENTITY_PTRS; // default 150
extern int32 MAX_VISIBLE_ENTITY_PTRS;   // default 1000
extern int32 MAX_VISIBLE_LOD_PTRS;      // default 1000
extern int32 MAX_VISIBLE_SUPERLOD_PTRS; // default 50

class CWorldScan {
public:
    using tScanFunction = void(__cdecl*)(int32, int32);
    static void ScanWorld(CVector2D* points, int32 pointsCount, tScanFunction scanFunction);
    static void SetExtraRectangleToScan(float minX, float maxX, float minY, float maxY);
};

class CRenderer {
public:
    static bool& ms_bRenderTunnels;
    static bool& ms_bRenderOutsideTunnels;
    static tRenderListEntry*& ms_pLodDontRenderList;
    static tRenderListEntry*& ms_pLodRenderList;
    static CVehicle*& m_pFirstPersonVehicle;
    static CEntity** ms_aInVisibleEntityPtrs; // static CEntity *ms_aInVisibleEntityPtrs[MAX_INVISIBLE_ENTITY_PTRS];
    static CEntity** ms_aVisibleSuperLodPtrs; // static CEntity *ms_aVisibleSuperLodPtrs[MAX_VISIBLE_SUPERLOD_PTRS];
    static CEntity** ms_aVisibleLodPtrs;      // static CEntity *ms_aVisibleLodPtrs[MAX_VISIBLE_LOD_PTRS];
    static CEntity** ms_aVisibleEntityPtrs;   // static CEntity *ms_aVisibleEntityPtrs[MAX_VISIBLE_ENTITY_PTRS];
    static int32& ms_nNoOfVisibleSuperLods;
    static int32& ms_nNoOfInVisibleEntities;
    static int32& ms_nNoOfVisibleLods;
    static int32& ms_nNoOfVisibleEntities;
    static float& ms_fFarClipPlane;
    static float& ms_fCameraHeading;
    static bool& m_loadingPriority;
    static bool& ms_bInTheSky;
    static CVector& ms_vecCameraPosition;
    static float& ms_lodDistScale;    // default 1.2
    static float& ms_lowLodDistScale; // default 1.0

public:
    static void InjectHooks();

    // dummy function
    static void Init();
    // dummy function
    static void Shutdown();
    static void RenderFadingInEntities();
    static void RenderFadingInUnderwaterEntities();
    static void RenderOneRoad(CEntity* entity);
    static void RenderOneNonRoad(CEntity* entity);
    static void RemoveVehiclePedLights(CPhysical* entity);
    static void AddEntityToRenderList(CEntity* entity, float distance);
    static tRenderListEntry* GetLodRenderListBase();
    static tRenderListEntry* GetLodDontRenderListBase();
    static void ResetLodRenderLists();
    static void AddToLodRenderList(CEntity* entity, float distance);
    // unused
    static void AddToLodDontRenderList(CEntity* entity, float distance);
    static void ProcessLodRenderLists();
    static void PreRender();
    static void RenderRoads();
    static void RenderEverythingBarRoads();
    static void RenderFirstPersonVehicle();
    static bool SetupLightingForEntity(CPhysical* entity);
    static int32 SetupMapEntityVisibility(CEntity* entity, CBaseModelInfo* modelInfo, float distance, bool bIsTimeInRange);
    static int32 SetupEntityVisibility(CEntity* entity, float* outDistance);
    static int32 SetupBigBuildingVisibility(CEntity* entity, float* outDistance);
    static void ScanSectorList_ListModels(int32 sectorX, int32 sectorY);
    static void ScanSectorList_ListModelsVisible(int32 sectorX, int32 sectorY);
    static void ScanSectorList(int32 sectorX, int32 sectorY);
    static void ScanBigBuildingList(int32 sectorX, int32 sectorY);
    static bool ShouldModelBeStreamed(CEntity* entity, CVector const& origin, float farClip);
    static void ScanPtrList_RequestModels(CPtrList& list);
    static void ConstructRenderList();
    static void ScanSectorList_RequestModels(int32 sectorX, int32 sectorY);
    static void ScanWorld();
    // returns objects count
    static int32 GetObjectsInFrustum(CEntity** outEntities, float farPlane, RwMatrix* transformMatrix);
    static void RequestObjectsInFrustum(RwMatrix* transformMatrix, int32 modelRequestFlags);
    static void RequestObjectsInDirection(CVector const& posn, float angle, int32 modelRequestFlags);
    static void SetupScanLists(int32 sectorX, int32 sectorY);
};

extern uint32& gnRendererModelRequestFlags;
extern CEntity**& gpOutEntitiesForGetObjectsInFrustum;
