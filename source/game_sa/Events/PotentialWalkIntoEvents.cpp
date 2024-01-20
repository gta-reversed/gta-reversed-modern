#include "StdInc.h"

#include "PotentialWalkIntoEvents.h"

#include "TaskComplexEnterCarAsDriver.h"
#include "TaskSimpleGoTo.h"
#include "TaskComplexWalkRoundCar.h"
#include "TaskComplexWalkRoundObject.h"
#include "TaskComplexFollowPedFootsteps.h"
#include "TaskComplexKillPedOnFoot.h"

void CEventPotentialWalkIntoVehicle::InjectHooks()
{
    RH_ScopedClass(CEventPotentialWalkIntoVehicle);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AE320);
    RH_ScopedVirtualInstall(AffectsPed, 0x4AE420);
}

void CEventPotentialWalkIntoObject::InjectHooks()
{
    RH_ScopedClass(CEventPotentialWalkIntoObject);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AE5D0);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B4950);
}

void CEventPotentialWalkIntoFire::InjectHooks()
{
    RH_ScopedClass(CEventPotentialWalkIntoFire);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1E20);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B6890);
}

void CEventPotentialWalkIntoPed::InjectHooks()
{
    RH_ScopedClass(CEventPotentialWalkIntoPed);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AE6E0);
    RH_ScopedVirtualInstall(AffectsPed, 0x4AE800);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4AE950);
}

CEventPotentialWalkIntoVehicle::CEventPotentialWalkIntoVehicle(CVehicle* vehicle, eMoveState moveState) {
    NOTSA_LOG_DEBUG("CEventPotentialWalkIntoVehicle({:x})", LOG_PTR(vehicle));

    m_vehicle = vehicle;
    m_moveState = moveState;
    CEntity::SafeRegisterRef(m_vehicle);
}

// 0x4AE3C0
CEventPotentialWalkIntoVehicle::~CEventPotentialWalkIntoVehicle() {
    CEntity::SafeCleanUpRef(m_vehicle);
}

CEventPotentialWalkIntoVehicle* CEventPotentialWalkIntoVehicle::Constructor(CVehicle* vehicle, eMoveState moveState) {
    this->CEventPotentialWalkIntoVehicle::CEventPotentialWalkIntoVehicle(vehicle, moveState);
    return this;
}

// 0x4AE420
bool CEventPotentialWalkIntoVehicle::AffectsPed(CPed* ped) {
    return CEventPotentialWalkIntoVehicle::AffectsPed_Reversed(ped);
}

bool CEventPotentialWalkIntoVehicle::AffectsPed_Reversed(CPed* ped) {
    auto taskEnterCarAsDriver = ped->GetTaskManager().Find<CTaskComplexEnterCarAsDriver>();
    auto goToTask = reinterpret_cast<CTaskSimpleGoTo*>(ped->GetTaskManager().GetSimplestActiveTask());
    if (ped->IsPlayer() && !taskEnterCarAsDriver && !CTask::IsGoToTask(goToTask))
        return false;

    if (!ped->IsAlive() || ped->bInVehicle || m_moveState == PEDMOVE_STILL)
        return false;

    if (const auto task = ped->GetTaskManager().Find<CTaskComplexWalkRoundCar>()) {
        if (task->m_Veh != m_vehicle) {
            if ((m_vehicle->m_pTrailer && m_vehicle->m_pTrailer == task->m_Veh) ||
                (m_vehicle->m_pTractor && m_vehicle->m_pTractor == task->m_Veh)
            ) {
                task->SetNewVehicle(m_vehicle, 0);
            }
            return false;
        }
    }

    if (!ped->m_pAttachedTo && m_vehicle && m_vehicle->IsSubVehicleTypeValid() && !m_vehicle->IsSubFakeAircraft()) {
        bool isGoToPointTask = false;
        CVector targetPos;
        if (goToTask->GetTaskType() == TASK_SIMPLE_GO_TO_POINT) {
            targetPos = goToTask->m_vecTargetPoint;
            isGoToPointTask = true;
        }
        if (taskEnterCarAsDriver) {
            if (m_vehicle == taskEnterCarAsDriver->GetTargetCar() && m_vehicle->IsSubPlane())
                return false;

            targetPos = taskEnterCarAsDriver->GetTargetPos();
        }
        if (isGoToPointTask || taskEnterCarAsDriver) {
            CVector surfacePoint;
            CPedGeometryAnalyser::ComputeClosestSurfacePoint(*ped, *m_vehicle, surfacePoint);
            int32 hitSide = CPedGeometryAnalyser::ComputeEntityHitSide(surfacePoint, *m_vehicle);
            if (hitSide != CPedGeometryAnalyser::ComputeEntityHitSide(targetPos, *m_vehicle))
                return true;

            return false;
        }
        return true;
    }
    return false;
}

CEventPotentialWalkIntoObject::CEventPotentialWalkIntoObject(CObject* object, int32 moveState) {
    m_object = object;
    m_moveState = moveState;
    CEntity::SafeRegisterRef(m_object);
}

CEventPotentialWalkIntoObject::~CEventPotentialWalkIntoObject() {
    CEntity::SafeCleanUpRef(m_object);
}

CEventPotentialWalkIntoObject* CEventPotentialWalkIntoObject::Constructor(CObject* object, int32 moveState) {
    this->CEventPotentialWalkIntoObject::CEventPotentialWalkIntoObject(object, moveState);
    return this;
}

// 0x4B4950
bool CEventPotentialWalkIntoObject::AffectsPed(CPed* ped) {
    return CEventPotentialWalkIntoObject::AffectsPed_Reversed(ped);
}

bool CEventPotentialWalkIntoObject::AffectsPed_Reversed(CPed* ped) {
    if (ped->IsPlayer() || !ped->IsAlive() || !m_object)
        return false;

    if (m_moveState != PEDMOVE_STILL
        && !ped->m_pAttachedTo
        && m_object->m_pAttachedTo != ped
        && !m_object->physicalFlags.bDisableMoveForce
    ) {
        CColModel* colModel = m_object->GetModelInfo()->GetColModel();
        CVector length = colModel->GetBoundingBox().GetSize();
        if (length.x >= 0.01f && length.y >= 0.01f && length.z >= 0.01f) {
            CTask* activeTask = ped->GetTaskManager().GetActiveTask();
            if (!activeTask)
                return true;

            assert(activeTask->GetTaskType() != TASK_COMPLEX_AVOID_ENTITY); // unused task
            if (activeTask->GetTaskType() == TASK_COMPLEX_WALK_ROUND_OBJECT) {
                auto taskWalkRoundObject = reinterpret_cast<CTaskComplexWalkRoundObject*>(activeTask);
                if (taskWalkRoundObject->m_object == m_object)
                    return false;
            }
            return true;
        }
    }

    return false;
}

// 0x4B1E20
CEventPotentialWalkIntoFire::CEventPotentialWalkIntoFire(const CVector& firePos, float fireSize, eMoveState moveState) :
    m_firePos{firePos},
    m_fireSize{fireSize},
    m_moveState{moveState}
{
    if (fireSize < 1.0f) {
        m_radius = 0.7f;
    } else {
        m_radius = fireSize >= 2.0f
            ? 1.5f
            : 1.0f;
    }
    m_radius += 0.35f;
}

CEventPotentialWalkIntoFire* CEventPotentialWalkIntoFire::Constructor(const CVector& firePos, float fireSize, eMoveState moveState) {
    this->CEventPotentialWalkIntoFire::CEventPotentialWalkIntoFire(firePos, fireSize, moveState);
    return this;
}

// 0x4B6890
bool CEventPotentialWalkIntoFire::AffectsPed(CPed* ped) {
    return CEventPotentialWalkIntoFire::AffectsPed_Reversed(ped);
}

bool CEventPotentialWalkIntoFire::AffectsPed_Reversed(CPed* ped) {
    if (ped->IsAlive() && m_moveState != PEDMOVE_STILL) {
        auto goToTask = static_cast<CTaskSimpleGoTo*>(ped->GetTaskManager().GetSimplestActiveTask());
        if (goToTask && CTask::IsGoToTask(goToTask)) {
            CColSphere colSphere;
            colSphere.Set(m_radius, m_firePos, SURFACE_DEFAULT, 0, tColLighting(0xFF));
            CVector intersectPoint2;
            CVector intersectPoint1;
            return colSphere.IntersectEdge(ped->GetPosition(), goToTask->m_vecTargetPoint, intersectPoint1, intersectPoint2);
        }
    }
    return false;
}

CEventPotentialWalkIntoPed::CEventPotentialWalkIntoPed(CPed* ped, const CVector& targetPoint, eMoveState moveState) :
    m_targetPoint{targetPoint},
    m_ped{ped},
    m_moveState{moveState}
{
    CEntity::SafeRegisterRef(m_ped);
}

CEventPotentialWalkIntoPed::~CEventPotentialWalkIntoPed() {
    CEntity::SafeCleanUpRef(m_ped);
}

// 0x4AE800
bool CEventPotentialWalkIntoPed::AffectsPed(CPed* ped) {
    return CEventPotentialWalkIntoPed::AffectsPed_Reversed(ped);
}

// 0x4AE950
bool CEventPotentialWalkIntoPed::TakesPriorityOver(const CEvent& refEvent) {
    return CEventPotentialWalkIntoPed::TakesPriorityOver_Reversed(refEvent);
}

bool CEventPotentialWalkIntoPed::AffectsPed_Reversed(CPed* ped) {
    if (!ped->IsAlive() || !m_ped || m_moveState == PEDMOVE_STILL) {
        return false;
    }

    if (ped->GetTaskManager().IsFirstFoundTaskMatching<TASK_COMPLEX_PARTNER_DEAL, TASK_COMPLEX_BE_IN_COUPLE, TASK_COMPLEX_PARTNER_GREET>(m_ped->GetTaskManager())) {
        return false;
    }

    if (const auto task = ped->GetTaskManager().Find<CTaskComplexFollowPedFootsteps>()) {
        if (task->m_targetPed == m_ped) {
            return false;
        }
    }

    if (const auto task = ped->GetTaskManager().Find<CTaskComplexKillPedOnFoot>()) {
        if (task->m_target == m_ped) {
            return false;
        }
    }

    if (const auto simplest = ped->GetTaskManager().GetSimplestActiveTask()) {
        if (CTask::IsGoToTask(simplest)) {
            return true;
        }
    }

    return false;
}

bool CEventPotentialWalkIntoPed::TakesPriorityOver_Reversed(const CEvent& refEvent) {
    return CEventHandler::IsTemporaryEvent(refEvent) ? true : CEvent::TakesPriorityOver(refEvent);
}
