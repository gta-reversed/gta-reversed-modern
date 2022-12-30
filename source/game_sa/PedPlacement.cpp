/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "PedPlacement.h"

void CPedPlacement::InjectHooks() {
    RH_ScopedClass(CPedPlacement);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(IsPositionClearForPed, 0x616860);
    RH_ScopedInstall(FindZCoorForPed, 0x616920);
    RH_ScopedOverloadedInstall(IsPositionClearOfCars, "Pos", 0x6168E0, CVehicle * (*)(const CVector*));
    RH_ScopedOverloadedInstall(IsPositionClearOfCars, "Ped", 0x616A40, CVehicle * (*)(const CPed*));
}

// 0x616920
bool CPedPlacement::FindZCoorForPed(CVector& inoutPos) {
    CEntity* hitEntity{};

    float firstHitZ = MAP_Z_LOW_LIMIT;
    if (CColPoint cp{}; CWorld::ProcessVerticalLine(inoutPos + CVector{ 0.f, 0.f, 0.5f }, inoutPos.z - 100.0f, cp, hitEntity, true, true, false, false, true, false, nullptr))
        firstHitZ = cp.m_vecPoint.z;

    float secondHitZ = MAP_Z_LOW_LIMIT;
    if (CColPoint cp{}; CWorld::ProcessVerticalLine(inoutPos + CVector{ 0.1f, 0.1f, 0.5f }, inoutPos.z - 100.0f, cp, hitEntity, true, true, false, false, true, false, nullptr))
        secondHitZ = cp.m_vecPoint.z;

    const auto highestZ = std::max(firstHitZ, secondHitZ);
    if (highestZ <= MAP_Z_LOW_LIMIT + 1.0f) // -99.0f
        return false;

    inoutPos.z = highestZ + 1.0f;
    return true;
}

// 0x616860
bool CPedPlacement::IsPositionClearForPed(const CVector& pos, float radius, int32 maxHitEntities, CEntity** outHitEntities, bool bCheckVehicles, bool bCheckPeds, bool bCheckObjects) {
    int16 hitCount{};
    CWorld::FindObjectsKindaColliding(
        pos,
        radius == -1.0f ? 0.75f : radius,
        true,
        &hitCount,
        maxHitEntities == -1 ? 2 : maxHitEntities,
        outHitEntities,
        false,
        bCheckVehicles,
        bCheckPeds,
        bCheckObjects,
        false
    );
    return hitCount == 0;
}

// 0x6168E0
CVehicle* CPedPlacement::IsPositionClearOfCars(const CVector* pos) {
    return CWorld::TestSphereAgainstWorld(*pos, 0.25, nullptr, false, true, false, false, false, false)->AsVehicle();
}

// 0x616A40
CVehicle* CPedPlacement::IsPositionClearOfCars(const CPed* ped) {
    const auto pedPos = ped->GetPosition();
    const auto vehHit = IsPositionClearOfCars(&pedPos);

    if (!vehHit)
        return nullptr;

    if (vehHit->IsAutomobile() || vehHit->vehicleFlags.bIsBig) {
        static CColPoint unusedColPoint[32]; // 0xC102A0
        if (CCollision::ProcessColModels(
            *ped->m_matrix,
            *CModelInfo::GetModelInfo(ped->m_nModelIndex)->GetColModel(),

            *vehHit->m_matrix,
            *CModelInfo::GetModelInfo(vehHit->m_nModelIndex)->GetColModel(),

            unusedColPoint, nullptr, nullptr, false
        )) {
            return vehHit;
        }
    }
    return nullptr;
}
