#include "StdInc.h"

void CEventVehicleCollision::InjectHooks()
{
    ReversibleHooks::Install("CEventVehicleCollision", "Constructor",0x4AC840, &CEventVehicleCollision::Constructor);
    ReversibleHooks::Install("CEventVehicleCollision", "Clone",0x4B6BC0, &CEventVehicleCollision::Clone_Reversed);
    ReversibleHooks::Install("CEventVehicleCollision", "AffectsPed",0x4B2EE0, &CEventVehicleCollision::AffectsPed_Reversed);
}

CEventVehicleCollision::CEventVehicleCollision(int16 pieceType, float damageIntensity, CVehicle* vehicle, const CVector& collisionImpactVelocity, const CVector& collisionPosition, int8 moveState, int16 evadeType)
{
    m_pieceType = pieceType;
    m_evadeType = evadeType;
    m_fDamageIntensity = damageIntensity;
    m_vehicle = vehicle;
    m_collisionImpactVelocity = collisionImpactVelocity;
    m_collisionPosition = collisionPosition;
    m_moveState = moveState;
    field_31 = 0;
    if (vehicle)
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(m_vehicle));
}

CEventVehicleCollision::~CEventVehicleCollision()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(m_vehicle));
}

// 0x4AC840
CEventVehicleCollision* CEventVehicleCollision::Constructor(int16 pieceType, float damageIntensity, CVehicle* vehicle, const CVector& collisionImpactVelocity, const CVector& collisionPosition, int8 moveState, int16 evadeType)
{
    this->CEventVehicleCollision::CEventVehicleCollision(pieceType, damageIntensity, vehicle, collisionImpactVelocity, collisionPosition, moveState, evadeType);
    return this;
}

// 0x4B6BC0
CEvent* CEventVehicleCollision::Clone()
{
    return CEventVehicleCollision::Clone_Reversed();
}

// 0x4B2EE0
bool CEventVehicleCollision::AffectsPed(CPed* ped)
{
    return CEventVehicleCollision::AffectsPed_Reversed(ped);
}

CEvent* CEventVehicleCollision::Clone_Reversed()
{
    return new CEventVehicleCollision(m_pieceType, m_fDamageIntensity, m_vehicle, m_collisionImpactVelocity, m_collisionPosition, m_moveState, VEHICLE_EVADE_NONE);
}

bool CEventVehicleCollision::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->IsAlive())
        return false;

    if (m_evadeType)
        return true;

    if (!m_vehicle)
        return false;

    if (ped->bInVehicle
        || m_vehicle->m_vehicleType == VEHICLE_BOAT
        || -DotProduct(m_collisionImpactVelocity, ped->GetForward()) < 0.35f)
    {
        return false;
    }

    CTask* pSimplestActiveTask = ped->GetTaskManager().GetSimplestActiveTask();
    if (pSimplestActiveTask && CTask::IsGoToTask(pSimplestActiveTask)) {
        auto* pGoToTask = static_cast<CTaskSimpleGoTo*>(pSimplestActiveTask);
        int32 hitSide = CPedGeometryAnalyser::ComputeEntityHitSide(*ped, *m_vehicle);
        if (hitSide == CPedGeometryAnalyser::ComputeEntityHitSide(pGoToTask->m_vecTargetPoint, *m_vehicle)) {
            if (!m_vehicle->m_pTractor && !m_vehicle->m_pTrailer)
                return false;

            CVector boundingBoxPlanes[4];
            float planes_D[4];
            CPedGeometryAnalyser::ComputeEntityBoundingBoxPlanes(ped->GetPosition().z, *m_vehicle, boundingBoxPlanes, planes_D);
            int32 targetPointInPlanes = 0, pedInPlanes = 0;
            for (int32 i = 0; i < 4; i++) {
                CVector& plane = boundingBoxPlanes[i];
                if (DotProduct(pGoToTask->m_vecTargetPoint, plane) + planes_D[i] < 0.0f)
                    ++targetPointInPlanes;
                if (DotProduct(ped->GetPosition(), plane) + planes_D[i] < 0.0f)
                    ++pedInPlanes;
            }
            if (targetPointInPlanes != 4 && pedInPlanes != 4)
                return false;
        }
    }

    CTask* pActiveTask = ped->GetTaskManager().GetActiveTask();
    if (pActiveTask) {
        if (pActiveTask->GetId() == TASK_COMPLEX_WALK_ROUND_CAR) {
            auto pTaskWalkRoundCar = reinterpret_cast<CTaskComplexWalkRoundCar*>(pActiveTask);
            CVehicle* walkRoundVehicle = pTaskWalkRoundCar->m_vehicle;
            if (walkRoundVehicle == m_vehicle)
                return false;
            if ((m_vehicle->m_pTrailer && m_vehicle->m_pTrailer == walkRoundVehicle) ||
                (m_vehicle->m_pTractor && m_vehicle->m_pTractor == walkRoundVehicle))
            {
                pTaskWalkRoundCar->SetNewVehicle(m_vehicle, 0);
            }
        }
        else {
            auto pTaskHitPedWithCar = reinterpret_cast<CTaskComplexHitPedWithCar*>(pActiveTask);
            if (pActiveTask->GetId() == TASK_COMPLEX_HIT_PED_WITH_CAR && pTaskHitPedWithCar->m_vehicle == m_vehicle)
                return false;
        }
    }

    return true;
}
