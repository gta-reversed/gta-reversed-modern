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
    RH_ScopedInstall(AffectsPed_Reversed, 0x4AE420);
}

void CEventPotentialWalkIntoObject::InjectHooks()
{
    RH_ScopedClass(CEventPotentialWalkIntoObject);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AE5D0);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B4950);
}

void CEventPotentialWalkIntoFire::InjectHooks()
{
    RH_ScopedClass(CEventPotentialWalkIntoFire);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1E20);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B6890);
}

void CEventPotentialWalkIntoPed::InjectHooks()
{
    RH_ScopedClass(CEventPotentialWalkIntoPed);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AE6E0);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4AE800);
    RH_ScopedInstall(TakesPriorityOver_Reversed, 0x4AE950);
}

CEventPotentialWalkIntoVehicle::CEventPotentialWalkIntoVehicle(CVehicle* vehicle, int32 moveState)
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

CEventPotentialWalkIntoVehicle* CEventPotentialWalkIntoVehicle::Constructor(CVehicle* vehicle, int32 moveState)
{
    this->CEventPotentialWalkIntoVehicle::CEventPotentialWalkIntoVehicle(vehicle, moveState);
    return this;
}

// 0x4AE420
bool CEventPotentialWalkIntoVehicle::AffectsPed(CPed* ped)
{
    return CEventPotentialWalkIntoVehicle::AffectsPed_Reversed(ped);
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
            if (!ped->m_pAttachedTo && m_vehicle && m_vehicle->IsSubVehicleTypeValid() && !m_vehicle->IsSubFakeAircraft()) {
                bool isGoToPointTask = false;
                CVector targetPos;
                if (goToTask->GetTaskType() == TASK_SIMPLE_GO_TO_POINT) {
                    targetPos = goToTask->m_vecTargetPoint;
                    isGoToPointTask = true;
                }
                if (taskEnterCarAsDriver) {
                    if (m_vehicle == taskEnterCarAsDriver->m_pTargetVehicle && m_vehicle->IsSubPlane())
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
        }
    }
    return false;
}

CEventPotentialWalkIntoObject::CEventPotentialWalkIntoObject(CObject* object, int32 moveState)
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

CEventPotentialWalkIntoObject* CEventPotentialWalkIntoObject::Constructor(CObject* object, int32 moveState)
{
    this->CEventPotentialWalkIntoObject::CEventPotentialWalkIntoObject(object, moveState);
    return this;
}

// 0x4B4950
bool CEventPotentialWalkIntoObject::AffectsPed(CPed* ped)
{
    return CEventPotentialWalkIntoObject::AffectsPed_Reversed(ped);
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
                    assert(activeTask->GetTaskType() != TASK_COMPLEX_AVOID_ENTITY); // unused task
                    if (activeTask->GetTaskType() == TASK_COMPLEX_WALK_ROUND_OBJECT) {
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

CEventPotentialWalkIntoFire::CEventPotentialWalkIntoFire(CVector* firePos, float fireSize, int32 moveState)
{
    m_firePos = *firePos;
    m_fireSize = fireSize;
    m_moveState = moveState;
    if (fireSize < 1.0f) {
        m_radius = 0.7f + 0.35f;
    }
    else {
        if (fireSize >= 2.0f)
            m_radius = 1.5f;
        else
            m_radius = 1.0f;

        m_radius += 0.35f;
    }
}

CEventPotentialWalkIntoFire* CEventPotentialWalkIntoFire::Constructor(CVector* firePos, float fireSize, int32 moveState)
{
    this->CEventPotentialWalkIntoFire::CEventPotentialWalkIntoFire(firePos, fireSize, moveState);
    return this;
}

// 0x4B6890
bool CEventPotentialWalkIntoFire::AffectsPed(CPed* ped)
{
    return CEventPotentialWalkIntoFire::AffectsPed_Reversed(ped);
}

bool CEventPotentialWalkIntoFire::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && m_moveState != PEDMOVE_STILL) {
        auto goToTask = static_cast<CTaskSimpleGoTo*>(ped->GetTaskManager().GetSimplestActiveTask());
        if (goToTask && CTask::IsGoToTask(goToTask)) {
            CColSphere colSphere;
            colSphere.Set(m_radius, m_firePos, 0, 0, 255u);
            CVector intersectPoint2;
            CVector intersectPoint1;
            return colSphere.IntersectEdge(ped->GetPosition(), goToTask->m_vecTargetPoint, intersectPoint1, intersectPoint2);
        }
    }
    return false;
}

CEventPotentialWalkIntoPed::CEventPotentialWalkIntoPed(CPed* ped, CVector* targetPoint, int32 moveState)
{
    m_targetPoint = *targetPoint;
    m_ped = ped;
    m_moveState = moveState;
    ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventPotentialWalkIntoPed::~CEventPotentialWalkIntoPed()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventPotentialWalkIntoPed* CEventPotentialWalkIntoPed::Constructor(CPed* ped, CVector* targetPoint, int32 moveState)
{
    this->CEventPotentialWalkIntoPed::CEventPotentialWalkIntoPed(ped, targetPoint, moveState);
    return this;
}

// 0x4AE800
bool CEventPotentialWalkIntoPed::AffectsPed(CPed* ped)
{
    return CEventPotentialWalkIntoPed::AffectsPed_Reversed(ped);
}

// 0x4AE950
bool CEventPotentialWalkIntoPed::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventPotentialWalkIntoPed::TakesPriorityOver_Reversed(refEvent);
}

bool CEventPotentialWalkIntoPed::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && m_ped && m_moveState != PEDMOVE_STILL) {
        CTask* partnerTask = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL);
        if (!partnerTask)
            partnerTask = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_BE_IN_COUPLE);

        if (!partnerTask)
            partnerTask = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET);

        if (partnerTask) {
            CTask* thisPedPartnerTask = m_ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL);
            if (!thisPedPartnerTask)
                thisPedPartnerTask = m_ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_BE_IN_COUPLE);
            if (!thisPedPartnerTask)
                thisPedPartnerTask = m_ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET);
            if (thisPedPartnerTask) {
                if (partnerTask->GetTaskType() == thisPedPartnerTask->GetTaskType())
                    return false;
            }
        }
        auto followFootstepsTask = reinterpret_cast<CTaskComplexFollowPedFootsteps*>(ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_FOLLOW_PED_FOOTSTEPS));
        if (followFootstepsTask && followFootstepsTask->m_targetPed == m_ped)
            return false;

        auto killPedOnFootTask = reinterpret_cast<CTaskComplexKillPedOnFoot*>(ped->GetIntelligence()->FindTaskByType(TASK_COMPLEX_KILL_PED_ON_FOOT));
        if (killPedOnFootTask && killPedOnFootTask->m_target == m_ped) 
            return false;

        CTask* activeTask = ped->GetTaskManager().GetSimplestActiveTask();
        if (!activeTask || !CTask::IsGoToTask(activeTask))
            return false;

        return true;
    }
    return false;
}

bool CEventPotentialWalkIntoPed::TakesPriorityOver_Reversed(const CEvent& refEvent)
{
    if (CEventHandler::IsTemporaryEvent(refEvent))
        return true;
    return CEvent::TakesPriorityOver(refEvent);
}
