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

extern unsigned int MAX_INVISIBLE_ENTITY_PTRS; // default 150
extern unsigned int MAX_VISIBLE_ENTITY_PTRS; // default 1000
extern unsigned int MAX_VISIBLE_LOD_PTRS; // default 1000
extern unsigned int MAX_VISIBLE_SUPERLOD_PTRS; // default 50

class  CRenderer {
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
    static unsigned int &ms_nNoOfVisibleSuperLods;
    static unsigned int &ms_nNoOfInVisibleEntities;
    static unsigned int &ms_nNoOfVisibleLods;
    static unsigned int &ms_nNoOfVisibleEntities;
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
    static void ScanSectorList_ListModels(int sector_x, int sector_y);
    static void ScanSectorList_ListModelsVisible(int sector_x, int sector_y);
    static tRenderListEntry* GetLodRenderListBase();
    static tRenderListEntry* GetLodDontRenderListBase();
    static void ResetLodRenderLists();
    static void AddToLodRenderList(CEntity* entity, float distance);
    static void AddToLodDontRenderList(CEntity* entity, float distance);
    static void ProcessLodRenderLists();
    static void PreRender();
    static void RenderRoads();
    static void RenderEverythingBarRoads();
    static void RenderFirstPersonVehicle();
    static bool SetupLightingForEntity(CEntity* entity);
    static int SetupMapEntityVisibility(CEntity* entity, CBaseModelInfo* modelInfo, float distance, bool arg3);
    static int SetupEntityVisibility(CEntity* entity, float* outDistance);
    static int SetupBigBuildingVisibility(CEntity* entity, float* outDistance);
    static void ScanSectorList(int sectorX, int sectorY);
    static void ScanBigBuildingList(int sector_x, int sector_y);
    // returns objects count
    static int GetObjectsInFrustum(CEntity** outEntities, float distance, RwMatrixTag* transformMat);
    static bool ShouldModelBeStreamed(CEntity* entity, CVector const& origin, float farClip);
    static void ScanWorld();
    static void ScanPtrList_RequestModels(CPtrList& ptrList);
    static void ConstructRenderList();
    static void ScanSectorList_RequestModels(int sector_x, int sector_y);
    static void RequestObjectsInFrustum(RwMatrixTag* transformMat, int modelRequesFlags);
    static void RequestObjectsInDirection(CVector const& posn, float angle, int modelRequesFlags);
    static void SetupScanLists(int sectorX, int sectorY);
};

extern unsigned int &gnRendererModelRequestFlags;
extern CEntity **&gpOutEntitiesForGetObjectsInFrustum;
