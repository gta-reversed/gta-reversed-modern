#pragma once

#include "List_c.h"
#include "Interior_c.h"
#include "InteriorGroup_c.h"
#include "InteriorObject.h"
#include "InteriorEffectInfo_t.h"

class InteriorManager_c {
public:
    // TODO: Use TList_c instead of List_c

    Interior_c               m_interiors[8];               // 0x0
    List_c                   m_interiorList;               // 0x3CA0
    InteriorGroup_c          m_interiorGroups[8];          // 0x3CAC
    TList_c<InteriorGroup_c> m_interiorGroupList;          // 0x428C
    List_c                   m_interiorGroupsList;         // 0x4298
    int32                    m_interiorCount;              // 0x42A4
    int32                    m_InteriorIds[64];            // 0x42A8
    int32                    m_objectCount;                // 0x43A8
    InteriorObject           m_objects[32];                // 0x43AC
    char                     m_interiorPedsAliveState[16]; // 0x472C
    int32                    dword473C;                    // 0x473C
    CRect                    m_Rect;                       // 0x4740
    bool                     m_bIsInitialised;             // 0x4750
    int8                     m_pruneVisibleEffects;        // 0x4751
    int8                     m_bPedsEnabled;               // 0x4752
    int8                     field_4753;                   // 0x4753
    int32                    m_lastUpdateTimeInMs;         // 0x4754

public:
    static void InjectHooks();

    InteriorManager_c() = default;  // 0x5984C0
    ~InteriorManager_c() = default; // 0x598580

    void Init();
    int8 Update();
    void Exit();

    static int8 AddSameGroupEffectInfos(InteriorEffectInfo_t* effectInfo, int32 a2);
    static bool AreAnimsLoaded(int32 animBlock);

    void PruneVisibleEffects(InteriorEffectInfo_t* effectInfo, int32 a2, int32 a3, float a4);
    int32 GetVisibleEffects(InteriorEffectInfo_t* effectInfo, int32 totalEffects);
    int32 IsInteriorEffectVisible(C2dEffect* effect, CEntity* entity);
    int32 GetPedsInterior(CPed* ped);
    int32 ReturnInteriorToPool(Interior_c* interior);
    ListItem_c* GetInteriorFromPool();
    int32 GetVectorsInterior(CVector* pos);
    int32 SetStealableObjectStolen(CEntity* entity, uint8 a3);
    int32 FindStealableObjectId(CEntity* entity);
    int32 FindStealableObjectId(int32 interiorId, int32 modelId, CVector point);
    bool HasInteriorHadStealDataSetup(Interior_c* interior);
    int8 IsGroupActive(int32 group);
    ListItem_c* GetPedsInteriorGroup(CPed* ped);
    int32 SetEntryExitPtr(CEntryExit* exit);
    bool GetBoundingBox(FurnitureEntity_c* entity, CVector* pos);
    int8 ActivatePeds(uint8 enable);

    void inlined_prune_visible_effects(bool prune) { m_pruneVisibleEffects = prune; } // 0x598070
};
VALIDATE_SIZE(InteriorManager_c, 0x4758);

static inline InteriorManager_c& g_interiorMan = *reinterpret_cast<InteriorManager_c*>(0xBAF670);
