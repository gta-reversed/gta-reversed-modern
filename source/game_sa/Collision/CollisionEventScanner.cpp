#include "StdInc.h"

#include "CollisionEventScanner.h"

void CCollisionEventScanner::ScanForCollisionEvents(CPed* ped, CEventGroup* eg) {
    if (!ped->m_pDamageEntity || ped->m_fDamageIntensity == 0.f) {
        m_bAlreadyHitByCar = false;
        return;
    }

    const auto pedMoveState = ped->GetIntelligence()->GetMoveStateFromGoToTask();

    switch (ped->m_pDamageEntity->GetType()) {
    case eEntityType::ENTITY_TYPE_BUILDING: { // 0x605127
        const auto o = ped->m_pDamageEntity->AsBuilding();
        eg->Add(CEventBuildingCollision{
            ped->m_nPieceType,
            ped->m_fDamageIntensity,
            o,
            &ped->m_vecLastCollisionImpactVelocity,
            &ped->m_vecLastCollisionPosn,
            pedMoveState
        });
        break;
    }
    case eEntityType::ENTITY_TYPE_VEHICLE: { // 0x6045A1
        const auto v = ped->m_pDamageEntity->AsVehicle();
        if (m_bAlreadyHitByCar) {
            break;
        }
        const auto vehMoveSpdSq = v->GetMoveSpeed().SquaredMagnitude();
        if (v->IsSubTrain() && v->physicalFlags.bDisableCollisionForce && ped->m_bIsStuck && ped->bIsStanding && !ped->m_standingOnEntity && vehMoveSpdSq >= sq(0.01f)) { // 0x604613
            ped->KillPedWithCar(v, 15.f, false);
        }
        if (vehMoveSpdSq >= sq(0.05f)) { // 0x604631
            auto dmgIntensity = ped->m_fDamageIntensity;
            if (ped->bIsStanding) {
                const auto shiftDotColDir = CVector2D{ ped->m_vecLastCollisionImpactVelocity }.Dot(ped->m_vecAnimMovingShift);
                if (shiftDotColDir < 0.f) { // Opposite directions
                    dmgIntensity = std::max(0.f, shiftDotColDir * ped->m_fMass + dmgIntensity);
                }
            }
            if (ped->IsPlayer()) {
                dmgIntensity = std::min(20.f, dmgIntensity);
                const auto vehBB         = &v->GetColModel()->GetBoundingBox();
                const auto vehBBCenterOS = vehBB->GetCenter();
                const auto colHeading    = v->GetHeading() - (v->GetMatrix() * vehBBCenterOS - ped->GetPosition()).Heading();
                const auto vehBBHeading  = std::atan2(vehBB->m_vecMax.x - vehBB->m_vecMin.x, vehBB->m_vecMax.y - vehBB->m_vecMin.y); // NOTE: Pretty sure they fucked this up, missing `-` before the 1st arg
                if ([&]{
                    if (std::abs(colHeading) < vehBBHeading || std::abs(colHeading) > PI - vehBBHeading) { // 0x6048DF
                        return (ped->GetPosition() - v->GetPosition()).Normalized().Dot(v->GetMoveSpeed());
                    }
                    return std::copysign(v->GetRight().Dot(v->GetMoveSpeed()), -colHeading);
                }() > 0.1f) { // 0x60491B
                    ped->KillPedWithCar(v, dmgIntensity, false);
                }

            }
        }
        break;
    }
    }
}

void CCollisionEventScanner::InjectHooks() {
    RH_ScopedClass(CCollisionEventScanner);
    RH_ScopedCategory("Collision");

    RH_ScopedInstall(ScanForCollisionEvents, 0x604500, { .reversed = false });
}
