/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Pool.h"
#include "CopPed.h"
#include "Heli.h"
#include "Building.h"
#include "CutsceneObject.h"
#include "Dummy.h"
#include "ColModel.h"
#include "Task.h"
#include "PedIntelligence.h"
#include "PtrNodeSingleLink.h"
#include "PtrNodeDoubleLink.h"
#include "EntryInfoNode.h"
#include "PedGeometryAnalyser.h"
#include "TaskSimpleSlideToCoord.h"
// #include "PointRoute.h"
// #include "PatrolRoute.h"
// #include "TaskAllocator.h"

class CPedAttractor;

#ifdef GetObject
#undef GetObject
#endif

typedef CPool<CPed, CCopPed>                  CPedPool;
typedef CPool<CVehicle, CHeli>                CVehiclePool;
typedef CPool<CBuilding>                      CBuildingPool;
typedef CPool<CObject, CCutsceneObject>       CObjectPool;
typedef CPool<CDummy>                         CDummyPool;
typedef CPool<CColModel>                      CColModelPool;
typedef CPool<CTask, CTaskSimpleSlideToCoord> CTaskPool;
typedef CPool<CPedIntelligence>               CPedIntelligencePool;
typedef CPool<CPtrNodeSingleLink>             CPtrNodeSingleLinkPool;
typedef CPool<CPtrNodeDoubleLink>             CPtrNodeDoubleLinkPool;
typedef CPool<CEntryInfoNode>                 CEntryInfoNodePool;
typedef CPool<CPointRoute>                    CPointRoutePool;
// typedef CPool<CPatrolRoute>                   CPatrolRoutePool;
typedef CPool<CEvent>                         CEventPool;
// typedef CPool<CNodeRoute>                     CNodeRoutePool;
typedef CPool<CTaskAllocator>                 CTaskAllocatorPool;
// typedef CPool<CPedAttractor>                  CPedAttractorPool;

class CPools {
public:
    static inline CPedPool*&               ms_pPedPool               = *(CPedPool**)0xB74490;
    static inline CVehiclePool*&           ms_pVehiclePool           = *(CVehiclePool**)0xB74494;
    static inline CBuildingPool*&          ms_pBuildingPool          = *(CBuildingPool**)0xB74498;
    static inline CObjectPool*&            ms_pObjectPool            = *(CObjectPool**)0xB7449C;
    static inline CDummyPool*&             ms_pDummyPool             = *(CDummyPool**)0xB744A0;
    static inline CColModelPool*&          ms_pColModelPool          = *(CColModelPool**)0xB744A4;
    static inline CTaskPool*&              ms_pTaskPool              = *(CTaskPool**)0xB744A8;
    static inline CPedIntelligencePool*&   ms_pPedIntelligencePool   = *(CPedIntelligencePool**)0xB744C0;
    static inline CPtrNodeSingleLinkPool*& ms_pPtrNodeSingleLinkPool = *(CPtrNodeSingleLinkPool**)0xB74484;
    static inline CPtrNodeDoubleLinkPool*& ms_pPtrNodeDoubleLinkPool = *(CPtrNodeDoubleLinkPool**)0xB74488;
    static inline CEntryInfoNodePool*&     ms_pEntryInfoNodePool     = *(CEntryInfoNodePool**)0xB7448C;
    static inline CPointRoutePool*&        ms_pPointRoutePool        = *(CPointRoutePool**)0xB744B0;
    //static inline CPatrolRoutePool*&       ms_pPatrolRoutePool       = *(CPatrolRoutePool**)0xB744B4;
    static inline CEventPool*&             ms_pEventPool             = *(CEventPool**)0xB744AC;
    //static inline CNodeRoutePool*&         ms_pNodeRoutePool         = *(CNodeRoutePool**)0xB744B8;
    static inline CTaskAllocatorPool*&     ms_pTaskAllocatorPool     = *(CTaskAllocatorPool**)0xB744BC;
    //static inline CPedAttractorPool*&      ms_pPedAttractorPool      = *(CPedAttractorPool**)0xB744C4;

public:
    static void InjectHooks();

    static void Initialise();
    static void ShutDown();

    // dummy function; returns "-1"
    static int32 CheckBuildingAtomics();
    static void CheckPoolsEmpty();
    static CObject* GetObject(int32 handle);
    static int32 GetObjectRef(CObject* object);
    static CPed* GetPed(int32 handle);
    static int32 GetPedRef(CPed* ped);
    static CVehicle* GetVehicle(int32 handle);
    static int32 GetVehicleRef(CVehicle* vehicle);

    static bool Load();
    static bool LoadObjectPool();
    static bool LoadPedPool();
    static bool LoadVehiclePool();

    static void MakeSureSlotInObjectPoolIsEmpty(int32 slot);

    static bool Save();
    static bool SaveObjectPool();
    static bool SavePedPool();
    static bool SaveVehiclePool();

    static auto& GetPedPool()               { return ms_pPedPool; }               // 0x404550
    static auto& GetVehiclePool()           { return ms_pVehiclePool; }           // 0x404560
    static auto& GetBuildingPool()          { return ms_pBuildingPool; }          // 0x
    static auto& GetObjectPool()            { return ms_pObjectPool; }            // 0x
    static auto& GetDummyPool()             { return ms_pDummyPool; }             // 0x
    static auto& GetColModelPool()          { return ms_pColModelPool; }          // 0x
    static auto& GetTaskPool()              { return ms_pTaskPool; }              // 0x61A330
    static auto& GetPedIntelligencePool()   { return ms_pPedIntelligencePool; }   // 0x
    static auto& GetPtrNodeSingleLinkPool() { return ms_pPtrNodeSingleLinkPool; } // 0x
    static auto& GetPtrNodeDoubleLinkPool() { return ms_pPtrNodeDoubleLinkPool; } // 0x
    static auto& GetEntryInfoNodePool()     { return ms_pEntryInfoNodePool; }     // 0x
    static auto& GetPointRoutePool()        { return ms_pPointRoutePool; }        // 0x
    // static auto& GetPatrolRoutePool()       { return ms_pPatrolRoutePool; }       // 0x41B410
    static auto& GetEventPool()             { return ms_pEventPool; }             // 0x
    // static auto& GetNodeRoutePool()         { return ms_pNodeRoutePool; }         // 0x41B420
    static auto& GetTaskAllocatorPool()     { return ms_pTaskAllocatorPool; }     // 0x69BB70
    // static auto& GetPedAttractorPool()      { return ms_pPedAttractorPool; }      // 0x
};

/*
GetPoolObj(int32)
GetPoolPed(int32)
GetPoolVehicle(int32)
GettPoolObjRef(CObject* object)
GettPoolPedRef(CPed* ped)
GettPoolVehicleRef(CVehicle* vehicle)
*/