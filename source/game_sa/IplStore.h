/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "IplDef.h"
#include "QuadTreeNode.h"
#include "Pool.h"

class CEntity;

class CIplStore {
public:
    static CQuadTreeNode*& ms_pQuadTree;
    static CPool<IplDef>*& ms_pPool;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();

    // returns slot index
    static int32 AddIplSlot(char const* name);
    static void AddIplsNeededAtPosn(CVector const& posn);
    static void ClearIplsNeededAtPosn();
    static void EnableDynamicStreaming(int32 iplSlotIndex, bool enable);
    static void EnsureIplsAreInMemory(CVector const& posn);
    // returns -1 if slot not found
    static int32 FindIplSlot(char const* name);
    static CRect* GetBoundingBox(int32 iplSlotIndex);
    static CEntity** GetIplEntityIndexArray(int32 arrayIndex);
    static char* GetIplName(int32 iplSlotIndex);
    // returns array index
    static int32 GetNewIplEntityIndexArray(int32 entitiesCount);
    static bool HaveIplsLoaded(CVector const& coords, int32 playerNumber);
    static void IncludeEntity(int32 iplSlotIndex, CEntity* entity);
    static void Save();
    static void Load();
    static void LoadAllRemainingIpls();
    static bool LoadIpl(int32 iplSlotIndex, uint8* data, int32 dataSize);
    static bool LoadIplBoundingBox(int32 iplSlotIndex, uint8* data, int32 dataSize);
    static void LoadIpls(CVector posn, bool bAvoidLoadInPlayerVehicleMovingDirection);
    static void RemoveAllIpls();
    static void RemoveIpl(int32 iplSlotIndex);
    static void RemoveIplAndIgnore(int32 iplSlotIndex);
    static void RemoveIplSlot(int32 iplSlotIndex);
    static void RemoveIplWhenFarAway(int32 iplSlotIndex);
    static void RemoveRelatedIpls(int32 entityArraysIndex);
    static void RequestIplAndIgnore(int32 iplSlotIndex);
    static void RequestIpls(CVector const& posn, int32 playerNumber);
    static void SetIplsRequired(CVector const& posn, int32 playerNumber);
    static void SetIsInterior(int32 iplSlotIndex, bool isInterior);
    static int32 SetupRelatedIpls(char const* iplName, int32 entityArraysIndex, CEntity** instances);

    // 0x59EB20
    inline static bool HasDynamicStreamingDisabled(int32 iplSlotIndex) { return ms_pPool->GetAt(iplSlotIndex)->m_bDisableDynamicStreaming; }
};

extern uint32 MAX_IPL_ENTITY_INDEX_ARRAYS; // default 40
extern uint32 MAX_IPL_INSTANCES;           // default 1000

extern CEntity** ppCurrIplInstance;
extern uint32& NumIplEntityIndexArrays;
static inline CEntity** (&IplEntityIndexArrays)[40] = *(CEntity * *(*)[40])0x8E3F08;
extern bool& gbIplsNeededAtPosn;
extern CVector& gvecIplsNeededAtPosn;
extern uint32& gCurrIplInstancesCount;
extern CEntity** gCurrIplInstances; // CEntity *gCurrIplInstances[1000]

void SetIfInteriorIplIsRequired(CVector2D const& posn, void* data);
void SetIfIplIsRequired(CVector2D const& posn, void* data);
void SetIfIplIsRequiredReducedBB(CVector2D const& posn, void* data);
