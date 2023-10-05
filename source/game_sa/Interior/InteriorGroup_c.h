#pragma once

#include "Base.h"

#include "Vector.h"

class CEntity;
class CPed;
class Interior_c;
struct InteriorInfo_t;

class InteriorGroup_c : public ListItem_c<InteriorGroup_c> {
public:
    CEntity*    m_pEntity;             // 0x8
    uint8       m_id;                  // 0xC
    uint8       m_groupId;             // 0xD
    uint8       m_groupType;           // 0xE
    uint8       m_numInteriors;        // 0xF
    Interior_c* m_interiors[8];        // 0x10
    CEntryExit* m_enex;                // 0x30
    bool        m_isVisible;           // 0x34
    bool        m_lastIsVisible;       // 0x35
    int8        m_numPeds;             // 0x36
    CPed*       m_peds[16];            // 0x38
    CPed*       m_pedsToRemove[16];    // 0x78
    int8        m_pathSetupComplete;   // 0xB8
    int8        m_updatePeds;          // 0xB9
    int8        m_animBlockReferenced; // 0xBA

public:
    static void InjectHooks();

    InteriorGroup_c() = default;  // 0x597FE0
    ~InteriorGroup_c() = default; // 0x597FF0

    auto GetInteriors() { return m_interiors | rng::views::take(m_numInteriors); }
    auto GetPeds() { return m_peds | rng::views::take(m_numPeds); }

    void Init(CEntity* entity, int32 id);
    void Update();
    int32 AddInterior(Interior_c* interior);
    void SetupPeds();
    void UpdatePeds();
    int32 SetupHousePeds();
    int8 SetupPaths();
    int8 ArePathsLoaded();
    void Setup();
    int8 Exit();
    int8 ContainsInteriorType(int32 a2);
    int8 CalcIsVisible();
    int8 DereferenceAnims();
    void ReferenceAnims();
    void UpdateOfficePeds();
    int8 RemovePed(CPed* a2);
    int32 SetupShopPeds();
    void SetupOfficePeds();
    CEntity* GetEntity();
    CPed* GetPed(int32);
    bool FindClosestInteriorInfo(int32 a, CVector point, float b, InteriorInfo_t** interiorInfo, Interior_c** interior, float* pSome);
    bool FindInteriorInfo(int32 a2, InteriorInfo_t** a3, Interior_c** a4);
    int32 GetNumInteriorInfos(int32 a2);
    int32 GetRandomInterior();
    auto GetId() const { return m_id; }

    auto GetInteriors() const { return m_interiors | std::views::take(m_numInteriors); }
};
VALIDATE_SIZE(InteriorGroup_c, 0xBC);
