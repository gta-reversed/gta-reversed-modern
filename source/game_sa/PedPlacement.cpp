/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

void CPedPlacement::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CPedPlacement", "IsPositionClearForPed", 0x616860, &CPedPlacement::IsPositionClearForPed);
    Install("CPedPlacement", "IsPositionClearOfCars_Pos", 0x6168E0, static_cast<CVehicle*(*)(CVector const*)>(&CPedPlacement::IsPositionClearOfCars));
    Install("CPedPlacement", "FindZCoorForPed", 0x616920, &CPedPlacement::FindZCoorForPed);
    Install("CPedPlacement", "IsPositionClearOfCars_Ped", 0x616A40, static_cast<CVehicle *(*)(CPed const*)>(&CPedPlacement::IsPositionClearOfCars));
}

bool CPedPlacement::FindZCoorForPed(CVector& inoutPos) {
    CEntity* hitEntity{};

    float firstHitZ = -100.f;
    if (CColPoint cp{}; CWorld::ProcessVerticalLine(inoutPos + CVector{ 0.f, 0.f, 0.5f }, inoutPos.z - 100.0f, cp, hitEntity, true, true, false, false, true, false, nullptr))
        firstHitZ = cp.m_vecPoint.z;

    float secondHitZ = -100.f;
    if (CColPoint cp{}; CWorld::ProcessVerticalLine(inoutPos + CVector{ 0.1f, 0.1f, 0.5f }, inoutPos.z - 100.0f, cp, hitEntity, true, true, false, false, true, false, nullptr))
        secondHitZ = cp.m_vecPoint.z;

    const auto highestZ = std::max(firstHitZ, secondHitZ);
    if (highestZ <= -99.0f)
        return false;

    inoutPos.z = highestZ + 1.0f;
    return true;
}

bool CPedPlacement::IsPositionClearForPed(CVector const& pos, float radius, int32 maxHitEntities, CEntity** outHitEntities, bool bCheckVehicles, bool bCheckPeds, bool bCheckObjects) {
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

CVehicle* CPedPlacement::IsPositionClearOfCars(CVector const* pos) {
    return static_cast<CVehicle*>(CWorld::TestSphereAgainstWorld(*pos, 0.25, nullptr, false, true, false, false, false, false));
}

CVehicle* CPedPlacement::IsPositionClearOfCars(CPed const* ped) {
    const auto pedPos = ped->GetPosition();
    if (const auto vehHit = IsPositionClearOfCars(&pedPos)) {
        if (vehHit->IsAutomobile() || vehHit->vehicleFlags.bIsBig) {
            static CColPoint unusedColPoint{};
            if (CCollision::ProcessColModels(
                *ped->m_matrix,
                *CModelInfo::GetModelInfo(ped->m_nModelIndex)->GetColModel(),

                *vehHit->m_matrix,
                *CModelInfo::GetModelInfo(vehHit->m_nModelIndex)->GetColModel(),

                &unusedColPoint, nullptr, nullptr, false
            )) {
                return vehHit;
            }
        }
    }
    return nullptr;
}
