#pragma once

#include "List_c.h"
#include "Interior_c.h"
#include "InteriorGroup_c.h"
#include "InteriorObject.h"
#include "InteriorEffectInfo_t.h"

class InteriorManager_c {
public:
    // TODO: Use TList_c instead of List_c

    Interior_c m_interiors[8] = {};           // 0
    List_c m_interiorList = {};               // 0x3CA0
    InteriorGroup_c m_interiorGroups[8] = {}; // 0x3CAC
    List_c m_interiorGroupList = {};          // 0x428C
    List_c m_interiorGroupsList = {};         // 0x4298
    int32 m_interiorCount = {};               // 0x42A4
    int32 m_InteriorIds[64] = {};             // 0x42A8
    int32 m_objectCount = {};                 // 0x43A8
    InteriorObject m_objects[32] = {};        // 0x43AC
    char m_interiorPedsAliveState[16] = {};   // 0x472C
    int32 dword473C = {};                     // 0x473C
    CRect field_4740 = {};                    // 0x4740
    bool m_bIsInitialised = {};               // 0x4750
    int8_t m_pruneVisibleEffects = {};        // 0x4751
    int8_t m_bPedsEnabled = {};               // 0x4752
    int8_t field_4753 = {};                   // 0x4753
    int32 m_lastUpdateTimeInMs = {};          // 0x4754

public:
    static void InjectHooks();

    ~InteriorManager_c();
    InteriorManager_c();

    static int8_t AddSameGroupEffectInfos(InteriorEffectInfo_t* a1, int32 a2);
    static bool AreAnimsLoaded(int32 animBlock);

    void PruneVisibleEffects(InteriorEffectInfo_t*, int32 a2, int32 a3, float a4);
    void Exit();
    int32 GetVisibleEffects(InteriorEffectInfo_t* interiorEffect, int32 totalEffects);
    int32 IsInteriorEffectVisible(C2dEffect* effect, CEntity* entity);
    int32 GetPedsInterior(CPed* a2);
    int32 ReturnInteriorToPool(Interior_c* a2);
    ListItem_c* GetInteriorFromPool();
    int32 GetVectorsInterior(CVector* a2);
    int32 SetStealableObjectStolen(CEntity* a2, uint8 a3);
    int32 FindStealableObjectId(CEntity* a2);
    int32 FindStealableObjectId(int32 interiorId, int32 modelId, CVector point);
    int8_t HasInteriorHadStealDataSetup(Interior_c* a2);
    int8_t IsGroupActive(int32 group);
    ListItem_c* GetPedsInteriorGroup(CPed*);
    int32 SetEntryExitPtr(CEntryExit* a2);
    int8_t GetBoundingBox(CEntity* a2, CVector* a3);
    int8_t ActivatePeds(uint8 enable);
    int8_t inlined_prune_visible_effects(int8_t prune);
    int8_t Update();
    void Init();

private:
    InteriorManager_c* Constructor();
    InteriorManager_c* Destructor();
};
VALIDATE_SIZE(InteriorManager_c, 0x4758);
