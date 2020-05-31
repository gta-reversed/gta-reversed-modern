/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVehicle.h"
#include "CBaseModelInfo.h"
#include "CPtrListDoubleLink.h"

enum eRendererVisiblity
{
    RENDERER_INVISIBLE = 0,
    RENDERER_VISIBLE,
    RENDERER_CULLED,
    RENDERER_STREAMME
};

struct tScanLists {
    CPtrListDoubleLink *buildingsList;
    CPtrListDoubleLink *objectsList;
    CPtrListDoubleLink *vehiclesList;
    CPtrListDoubleLink *pedsList;
    CPtrListDoubleLink *dummiesList;
};

VALIDATE_SIZE(tScanLists, 0x14);

struct tRenderListEntry {
    CEntity *pEntity;
    float distance;
};

VALIDATE_SIZE(tRenderListEntry, 8);

extern std::int32_t MAX_INVISIBLE_ENTITY_PTRS; // default 150
extern std::int32_t MAX_VISIBLE_ENTITY_PTRS; // default 1000
extern std::int32_t MAX_VISIBLE_LOD_PTRS; // default 1000
extern std::int32_t MAX_VISIBLE_SUPERLOD_PTRS; // default 50

class CWorldScan
{
public:
    using tScanFunction = void(__cdecl*)(std::int32_t, std::int32_t);
    static void ScanWorld(CVector2D* points, std::int32_t pointsCount, tScanFunction scanFunction);
    static void SetExtraRectangleToScan(float minX, float maxX, float minY, float maxY);
};

class CRenderer {
public:
    static bool &ms_bRenderTunnels;
    static bool &ms_bRenderOutsideTunnels;
    static tRenderListEntry *&ms_pLodDontRenderList;
    static tRenderListEntry *&ms_pLodRenderList;
    static CVehicle *&m_pFirstPersonVehicle;
    static CEntity **ms_aInVisibleEntityPtrs; // static CEntity *ms_aInVisibleEntityPtrs[MAX_INVISIBLE_ENTITY_PTRS];
    static CEntity **ms_aVisibleSuperLodPtrs; // static CEntity *ms_aVisibleSuperLodPtrs[MAX_VISIBLE_SUPERLOD_PTRS];
    static CEntity **ms_aVisibleLodPtrs; // static CEntity *ms_aVisibleLodPtrs[MAX_VISIBLE_LOD_PTRS];     
    static CEntity **ms_aVisibleEntityPtrs; // static CEntity *ms_aVisibleEntityPtrs[MAX_VISIBLE_ENTITY_PTRS];  
    static int &ms_nNoOfVisibleSuperLods;
    static int &ms_nNoOfInVisibleEntities;
    static int &ms_nNoOfVisibleLods;
    static int &ms_nNoOfVisibleEntities;
    static float &ms_fFarClipPlane;
    static float &ms_fCameraHeading;
    static bool &m_loadingPriority;
    static bool &ms_bInTheSky;
    static CVector &ms_vecCameraPosition;
    static float &ms_lodDistScale; // default 1.2
    static float &ms_lowLodDistScale; // default 1.0

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
    static int SetupMapEntityVisibility(CEntity* entity, CBaseModelInfo* modelInfo, float distance, bool bIsTimeInRange);
    static int SetupEntityVisibility(CEntity* entity, float* outDistance);
    static int SetupBigBuildingVisibility(CEntity* entity, float* outDistance);
    static void ScanSectorList_ListModels(std::int32_t sectorX, std::int32_t sectorY);
    static void ScanSectorList_ListModelsVisible(std::int32_t sectorX, std::int32_t sectorY);
    static void ScanSectorList(std::int32_t sectorX, std::int32_t sectorY);
    static void ScanBigBuildingList(std::int32_t sectorX, std::int32_t sectorY);
    static bool ShouldModelBeStreamed(CEntity* entity, CVector const& origin, float farClip);
    static void ScanPtrList_RequestModels(CPtrList& list);
    static void ConstructRenderList();
    static void ScanSectorList_RequestModels(std::int32_t sectorX, std::int32_t sectorY);
    static void ScanWorld();
    // returns objects count
    static std::int32_t GetObjectsInFrustum(CEntity** outEntities, float farPlane, RwMatrix* transformMatrix);
    static void RequestObjectsInFrustum(RwMatrix* transformMatrix, std::int32_t modelRequestFlags);
    static void RequestObjectsInDirection(CVector const& posn, float angle, std::int32_t modelRequesFlags);
    static void SetupScanLists(std::int32_t sectorX, std::int32_t sectorY);
};

extern unsigned int &gnRendererModelRequestFlags;
extern CEntity **&gpOutEntitiesForGetObjectsInFrustum;
