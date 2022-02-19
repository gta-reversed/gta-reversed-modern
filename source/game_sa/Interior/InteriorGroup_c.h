#pragma once

#include "Base.h"

#include "Vector.h"

class CEntity;
class CPed;
class Interior_c;
class InteriorInfo_t;

class InteriorGroup_c : public ListItem_c {
    CEntity* m_pEntity = {};           // 0x8
    uint8 m_nId = {};                  // 0xC
    uint8 m_furnitureId = {};          // 0xD
    uint8 m_animType[1] = {};          // 0xE
    uint8 m_interiorCount = {};        // 0xF
    Interior_c* m_interiors[8] = {};   // 0x10
    int32 field_30 = {};               // 0x30
    int8_t m_isVisible = {};           // 0x34
    int8_t m_removePeds = {};          // 0x35
    int8_t m_pedCount = {};            // 0x36
    int8_t field_37 = {};              // 0x37
    CPed* m_peds[16] = {};             // 0x38
    int32 field_78[16] = {};           // 0x78
    int8_t m_pathSetupComplete = {};   // 0xB8
    int8_t m_updatePeds = {};          // 0xB9
    int8_t m_animBlockReferenced = {}; // 0xBA
    int8_t field_BB = {};              // 0xBB

public:
    static void InjectHooks();

    ~InteriorGroup_c();
    InteriorGroup_c();

    CEntity* Init(CEntity* entity, int32 a3);
    void Update();
    void SetupPeds();
    void UpdatePeds();
    int32 SetupHousePeds();
    int8_t SetupPaths();
    int8_t ArePathsLoaded();
    void Setup();
    int8_t Exit();
    int8_t ContainsInteriorType(int32 a2);
    int8_t CalcIsVisible();
    int8_t DereferenceAnims();
    void ReferenceAnims();
    void UpdateOfficePeds();
    int8_t RemovePed(CPed* a2);
    int32 SetupShopPeds();
    void SetupOfficePeds();
    CEntity* GetEntity();
    CPed* GetPed(int32);
    bool FindClosestInteriorInfo(int32 a, CVector point, float b, InteriorInfo_t** interiorInfo, Interior_c** interior, float* pSome);
    bool FindInteriorInfo(int32 a2, InteriorInfo_t** a3, Interior_c** a4);
    int32 GetNumInteriorInfos(int32 a2);
    int32 GetRandomInterior();
    int32 AddInterior(Interior_c* a2);

private:
    InteriorGroup_c* Constructor();
    InteriorGroup_c* Destructor();
};
VALIDATE_SIZE(InteriorGroup_c, 0xBC);
