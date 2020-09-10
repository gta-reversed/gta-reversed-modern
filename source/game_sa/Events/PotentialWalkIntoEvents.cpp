#include "StdInc.h"


void CEventPotentialWalkIntoVehicle::InjectHooks()
{
    HookInstall(0x4AE320, &CEventPotentialWalkIntoVehicle::Constructor);
    HookInstall(0x4AE420, &CEventPotentialWalkIntoVehicle::AffectsPed_Reversed);
}

void CEventPotentialWalkIntoObject::InjectHooks()
{
    HookInstall(0x4AE5D0, &CEventPotentialWalkIntoObject::Constructor);
    HookInstall(0x4B4950, &CEventPotentialWalkIntoObject::AffectsPed_Reversed);
}

CEventPotentialWalkIntoVehicle::CEventPotentialWalkIntoVehicle(CVehicle* vehicle, std::int32_t moveState)
{
    m_vehicle = vehicle;
    m_moveState = moveState;
    if (vehicle)
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventPotentialWalkIntoVehicle::~CEventPotentialWalkIntoVehicle()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventPotentialWalkIntoVehicle* CEventPotentialWalkIntoVehicle::Constructor(CVehicle* vehicle, std::int32_t moveState)
{
    this->CEventPotentialWalkIntoVehicle::CEventPotentialWalkIntoVehicle(vehicle, moveState);
    return this;
}

bool CEventPotentialWalkIntoVehicle::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AE420, CEventPotentialWalkIntoVehicle*, CPed*>(this, ped);
#else
    return CEventPotentialWalkIntoVehicle::AffectsPed_Reversed(ped);
#endif
}

bool CEventPotentialWalkIntoVehicle::AffectsPed_Reversed(CPed* ped)
{
    auto taskEnterCarAsDriver = reinterpret_cast<CTaskComplexEnterCarAsDriver*>(ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_ENTER_CAR_AS_DRIVER));
    auto goToTask = reinterpret_cast<CTaskSimpleGoTo*>(ped->GetTaskManager().GetSimplestActiveTask());
    if (!ped->IsPlayer() || taskEnterCarAsDriver || CTask::IsGoToTask(goToTask)) {
        if (ped->IsAlive() && !ped->bInVehicle && m_moveState != PEDMOVE_STILL) {
            auto pTaskWalkRoundCar = reinterpret_cast<CTaskComplexWalkRoundCar*>(ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_WALK_ROUND_CAR));
            if (pTaskWalkRoundCar && pTaskWalkRoundCar->m_vehicle != m_vehicle) {
                if ((m_vehicle->m_pTrailer && m_vehicle->m_pTrailer == pTaskWalkRoundCar->m_vehicle) ||
                    (m_vehicle->m_pTractor && m_vehicle->m_pTractor == pTaskWalkRoundCar->m_vehicle))
                {
                    pTaskWalkRoundCar->SetNewVehicle(m_vehicle, 0);
                }
                return false;
            }
            if (!ped->m_pAttachedTo && m_vehicle && m_vehicle->IsVehicleTypeValid() && !m_vehicle->IsFakeAircraft()) {
                bool isGoToPointTask = false;
                CVector targetPos;
                if (goToTask->GetId() == TASK_SIMPLE_GO_TO_POINT) {
                    targetPos = goToTask->m_vecTargetPoint;
                    isGoToPointTask = true;
                }
                if (taskEnterCarAsDriver) {
                    if (m_vehicle == taskEnterCarAsDriver->m_pTargetVehicle && m_vehicle->IsPlane())
                        return false;
                    targetPos = taskEnterCarAsDriver->GetTargetPos();
                }
                if (isGoToPointTask || taskEnterCarAsDriver) {
                    CVector surfacePoint;
                    CPedGeometryAnalyser::ComputeClosestSurfacePoint(ped, m_vehicle, &surfacePoint);
                    std::int32_t hitSide = CPedGeometryAnalyser::ComputeEntityHitSide(&surfacePoint, m_vehicle);
                    if (hitSide != CPedGeometryAnalyser::ComputeEntityHitSide(&targetPos, m_vehicle))
                        return true;
                    return false;
                }
                return true;
            }
        }
    }
    return false;
}

CEventPotentialWalkIntoObject::CEventPotentialWalkIntoObject(CObject* object, std::int32_t moveState)
{
    m_object = object;
    m_moveState = moveState;
    if (object)
        object->RegisterReference(reinterpret_cast<CEntity**>(&m_object));
}

CEventPotentialWalkIntoObject::~CEventPotentialWalkIntoObject()
{
    if (m_object)
        m_object->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_object));
}

CEventPotentialWalkIntoObject* CEventPotentialWalkIntoObject::Constructor(CObject* object, std::int32_t moveState)
{
    this->CEventPotentialWalkIntoObject::CEventPotentialWalkIntoObject(object, moveState);
    return this;
}

bool CEventPotentialWalkIntoObject::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B4950, CEventPotentialWalkIntoObject*, CPed*>(this, ped);
#else
    return CEventPotentialWalkIntoObject::AffectsPed_Reversed(ped);
#endif
}

bool CEventPotentialWalkIntoObject::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->IsPlayer() && ped->IsAlive() && m_object) {
        if (m_moveState != PEDMOVE_STILL
            && !ped->m_pAttachedTo
            && m_object->m_pAttachedTo != ped
            && !m_object->physicalFlags.bDisableMoveForce)
        {
            CColModel* colModel = CModelInfo::GetModelInfo(m_object->m_nModelIndex)->GetColModel();
            CVector length = colModel->m_boundBox.m_vecMax - colModel->m_boundBox.m_vecMin;
            if (length.x >= 0.01f && length.y >= 0.01f && length.z >= 0.01f) {
                CTask* activeTask = ped->GetTaskManager().GetActiveTask();
                if (activeTask) {
                    assert(activeTask->GetId() != TASK_COMPLEX_AVOID_ENTITY); // unused task
                    if (activeTask->GetId() == TASK_COMPLEX_WALK_ROUND_OBJECT) {
                        auto taskWalkRoundObject = reinterpret_cast<CTaskComplexWalkRoundObject*>(activeTask);
                        if (taskWalkRoundObject->m_object == m_object)
                            return false;
                    }
                }
                return true;
            }
        }
         
    }
    return false;
}

