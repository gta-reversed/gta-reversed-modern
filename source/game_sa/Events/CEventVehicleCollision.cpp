#include "StdInc.h"

void CEventVehicleCollision::InjectHooks()
{
    HookInstall(0x4AC840, &CEventVehicleCollision::Constructor);
    HookInstall(0x4B6BC0, &CEventVehicleCollision::Clone_Reversed);
    HookInstall(0x4B2EE0, &CEventVehicleCollision::AffectsPed_Reversed);
}

CEventVehicleCollision::CEventVehicleCollision(std::int16_t pieceType, float damageIntensity, CVehicle* vehicle, const CVector& collisionImpactVelocity, const CVector& collisionPosition, std::int8_t moveState, std::int16_t evadeType)
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

CEventVehicleCollision* CEventVehicleCollision::Constructor(std::int16_t pieceType, float damageIntensity, CVehicle* vehicle, const CVector& collisionImpactVelocity, const CVector& collisionPosition, std::int8_t moveState, std::int16_t evadeType)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventVehicleCollision*, 0x4AC840, CEvent*, std::int16_t, float, CVehicle*, const CVector&, const CVector&, std::int8_t, std::int16_t>
        (this, pieceType, damageIntensity, vehicle, collisionImpactVelocity, collisionPosition, moveState, evadeType);
#else
    this->CEventVehicleCollision::CEventVehicleCollision(pieceType, damageIntensity, vehicle, collisionImpactVelocity, collisionPosition, moveState, evadeType);
    return this;
#endif
}

CEvent* CEventVehicleCollision::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4B6BC0, CEvent*>(this);
#else
    return CEventVehicleCollision::Clone_Reversed();
#endif
}

bool CEventVehicleCollision::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B2EE0, CEvent*, CPed*>(this, ped);
#else
    return CEventVehicleCollision::AffectsPed_Reversed(ped);
#endif
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
        CTaskSimpleGoTo* pGoToTask = static_cast<CTaskSimpleGoTo*>(pSimplestActiveTask);
        std::int32_t hitSide = CPedGeometryAnalyser::ComputeEntityHitSide(*ped, *m_vehicle);
        if (hitSide == CPedGeometryAnalyser::ComputeEntityHitSide(pGoToTask->m_vecTargetPoint, *m_vehicle)) {
            if (!m_vehicle->m_pTractor && !m_vehicle->m_pTrailer)
                return false;
            CVector boundingBoxPlanes[4];
            float planes_D[4];
            CPedGeometryAnalyser::ComputeEntityBoundingBoxPlanes(ped->GetPosition().z, *m_vehicle, boundingBoxPlanes, planes_D);
            std::int32_t targetPointInPlanes = 0, pedInPlanes = 0;
            for (std::int32_t i = 0; i < 4; i++) {
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
