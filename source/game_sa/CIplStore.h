/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "IplDef.h"
#include "CEntity.h"
#include "CQuadTreeNode.h"
#include "CEntity.h"

class  CIplStore {
public:
    static CQuadTreeNode *&ms_pQuadTree;
    static CPool<IplDef> *&ms_pPool;

    // returns slot index
    static int AddIplSlot(char const* name);
    static void AddIplsNeededAtPosn(CVector const& posn);
    static void ClearIplsNeededAtPosn();
    static void EnableDynamicStreaming(int iplSlotIndex, bool enable);
    static void EnsureIplsAreInMemory(CVector const& posn);
    // returns -1 if slot not found
    static int FindIplSlot(char const* name);
    static CRect* GetBoundingBox(int iplSlotIndex);
    static int* GetIplEntityIndexArray(int arrayIndex);
    static char* GetIplName(int iplSlotIndex);
    // returns array index
    static int GetNewIplEntityIndexArray(int entitiesCount);
    static bool HaveIplsLoaded(CVector const& coords, int playerNumber);
    static void IncludeEntity(int iplSlotIndex, CEntity* entity);
    static void Initialise();
    static bool Load();
    static void LoadAllRemainingIpls();
    static bool LoadIpl(int iplSlotIndex, unsigned char* data, int dataSize);
    static bool LoadIplBoundingBox(int iplSlotIndex, unsigned char* data, int dataSize);
    static void LoadIpls(CVector posn, bool bAvoidLoadInPlayerVehicleMovingDirection);
    static void RemoveAllIpls();
    static void RemoveIpl(int iplSlotIndex);
    static void RemoveIplAndIgnore(int iplSlotIndex);
    static void RemoveIplSlot(int iplSlotIndex);
    static void RemoveIplWhenFarAway(int iplSlotIndex);
    static void RemoveRelatedIpls(int entityArraysIndex);
    static void RequestIplAndIgnore(int iplSlotIndex);
    static void RequestIpls(CVector const& posn, int playerNumber);
    static bool Save();
    static void SetIplsRequired(CVector const& posn, int playerNumber);
    static void SetIsInterior(int iplSlotIndex, bool isInterior);
    static int SetupRelatedIpls(char const* iplName, int entityArraysIndex, CEntity** instances);
    static void Shutdown();
};

extern unsigned int MAX_IPL_ENTITY_INDEX_ARRAYS; // default 40
extern unsigned int MAX_IPL_INSTANCES; // default 1000

extern CEntity **ppCurrIplInstance;
extern unsigned int &NumIplEntityIndexArrays;
extern int **IplEntityIndexArrays; // int *IplEntityIndexArrays[40]
extern bool &gbIplsNeededAtPosn;
extern CVector &gvecIplsNeededAtPosn;
extern unsigned int &gCurrIplInstancesCount;
extern CEntity **gCurrIplInstances; // CEntity *gCurrIplInstances[1000]

void SetIfInteriorIplIsRequired(CVector2D const& posn, void* data);
void SetIfIplIsRequired(CVector2D const& posn, void* data);
void SetIfIplIsRequiredReducedBB(CVector2D const& posn, void* data);
