#pragma once

#include "Base.h"

#include "Vector.h"

class CEntity;
class CPed;
class Interior_c;
class InteriorInfo_t;

class InteriorGroup_c : public ListItem_c {
    CEntity*    m_pEntity;
    uint8       m_nId;
    uint8       m_furnitureId;
    uint8       m_animType;
    uint8       m_interiorCount;
    Interior_c* m_interiors[8];
    int32       field_30;
    int8        m_isVisible;
    int8        m_removePeds;
    int8        m_pedCount;
    int8        field_37;
    CPed*       m_peds[16];
    int32       field_78[16];
    int8        m_pathSetupComplete;
    int8        m_updatePeds;
    int8        m_animBlockReferenced;
    int8        field_BB;

public:
    static void InjectHooks();

    InteriorGroup_c() = default;  // 0x597FE0
    ~InteriorGroup_c() = default; // 0x597FF0

    void Init(CEntity* entity, int32 a3);
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
};
VALIDATE_SIZE(InteriorGroup_c, 0xBC);
