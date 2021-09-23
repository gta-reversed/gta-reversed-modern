#include "StdInc.h"

#include "CTaskComplexDriveFireTruck.h"

#include "CTaskComplexDriveToPoint.h"
#include "CTaskComplexDriveWander.h"
#include "CTaskComplexUseWaterCannon.h"
#include "CTaskSimpleCarDrive.h"

void CTaskComplexDriveFireTruck::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CTaskComplexDriveFireTruck", "Constructor", 0x659310, &CTaskComplexDriveFireTruck::Constructor);
    Install("CTaskComplexDriveFireTruck", "CreateSubTask", 0x65A240, &CTaskComplexDriveFireTruck::CreateSubTask);
    Install("CTaskComplexDriveFireTruck", "Clone", 0x659BC0, &CTaskComplexDriveFireTruck::Clone_Reversed);
    Install("CTaskComplexDriveFireTruck", "CreateFirstSubTask", 0x65B140, &CTaskComplexDriveFireTruck::CreateFirstSubTask_Reversed);
    Install("CTaskComplexDriveFireTruck", "CreateNextSubTask", 0x65B090, &CTaskComplexDriveFireTruck::CreateNextSubTask_Reversed);
    Install("CTaskComplexDriveFireTruck", "ControlSubTask", 0x65B1E0, &CTaskComplexDriveFireTruck::ControlSubTask_Reversed);
}

CTaskComplexDriveFireTruck* CTaskComplexDriveFireTruck::Constructor(CVehicle* vehicle, CPed* partnerFireman, bool bIsDriver) {
    this->CTaskComplexDriveFireTruck::CTaskComplexDriveFireTruck(vehicle, partnerFireman, bIsDriver);
    return this;
}

// 0x659310
CTaskComplexDriveFireTruck::CTaskComplexDriveFireTruck(CVehicle* vehicle, CPed* partnerFireman, bool bIsDriver) : CTaskComplex() {
    m_pVehicle        = vehicle;
    m_pPartnerFireman = partnerFireman;
    m_bIsDriver       = bIsDriver;
    m_pFire           = nullptr;

    if (m_pVehicle)
        m_pVehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pVehicle));

    if (m_pPartnerFireman)
        m_pPartnerFireman->RegisterReference(reinterpret_cast<CEntity**>(&m_pPartnerFireman));
}

// 0x6593A0
CTaskComplexDriveFireTruck::~CTaskComplexDriveFireTruck() {
    if (m_pVehicle)
        m_pVehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pVehicle));

    if (m_pPartnerFireman)
        m_pPartnerFireman->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pPartnerFireman));
}

// 0x659BC0
CTask* CTaskComplexDriveFireTruck::Clone() {
    return Clone_Reversed();
}

// 0x65B090
CTask* CTaskComplexDriveFireTruck::CreateNextSubTask(CPed* ped) {
    return CreateNextSubTask_Reversed(ped);
}

// 0x65B140
CTask* CTaskComplexDriveFireTruck::CreateFirstSubTask(CPed* ped) {
    return CreateFirstSubTask_Reversed(ped);
}

// 0x65B1E0
CTask* CTaskComplexDriveFireTruck::ControlSubTask(CPed* ped) {
    return ControlSubTask_Reversed(ped);
}

CTask* CTaskComplexDriveFireTruck::Clone_Reversed() {
    return new CTaskComplexDriveFireTruck(m_pVehicle, m_pPartnerFireman, m_bIsDriver);
}

CTask* CTaskComplexDriveFireTruck::CreateNextSubTask_Reversed(CPed* ped) {
    eTaskType subTaskType = m_pSubTask->GetTaskType();

    if (subTaskType == TASK_COMPLEX_CAR_DRIVE_WANDER)
        return CreateSubTask(TASK_FINISHED, ped);

    if (subTaskType == TASK_COMPLEX_CAR_DRIVE_TO_POINT)
        return ped->bInVehicle ? CreateSubTask(TASK_COMPLEX_USE_WATER_CANNON, ped) : CreateSubTask(TASK_FINISHED, ped);

    if (subTaskType == TASK_COMPLEX_USE_WATER_CANNON)
        return ped->bInVehicle ? CreateFirstSubTask(ped) : CreateSubTask(TASK_FINISHED, ped);

    if (subTaskType == TASK_SIMPLE_CAR_DRIVE)
        return CreateSubTask(TASK_FINISHED, ped);

    return nullptr;
}

CTask* CTaskComplexDriveFireTruck::CreateFirstSubTask_Reversed(CPed* ped) {
    if (!m_pVehicle || !ped->bInVehicle)
        return CreateSubTask(TASK_FINISHED, ped);

    if (!m_bIsDriver)
        return CreateSubTask(TASK_SIMPLE_CAR_DRIVE, ped);

    m_pFire = gFireManager.FindNearestFire(m_pVehicle->GetPosition(), true, true);
    return CreateSubTask(m_pFire ? TASK_COMPLEX_CAR_DRIVE_TO_POINT : TASK_COMPLEX_CAR_DRIVE_WANDER, ped);
}

CTask* CTaskComplexDriveFireTruck::ControlSubTask_Reversed(CPed* ped) {
    eTaskType subTaskId = m_pSubTask->GetTaskType();

    if (!m_pVehicle || !ped->bInVehicle)
        return CreateFirstSubTask(ped);

    if (subTaskId == TASK_COMPLEX_CAR_DRIVE_TO_POINT) {
        if (m_bIsDriver && m_pFire->m_nFlags.bBeingExtinguished) {
            CFire* newFire = gFireManager.FindNearestFire(m_pVehicle->GetPosition(), true, true);

            if (!newFire)
                return CreateSubTask(TASK_COMPLEX_CAR_DRIVE_WANDER, ped);

            if (newFire != m_pFire) {
                m_pFire = newFire;
                reinterpret_cast<CTaskComplexDriveToPoint*>(m_pSubTask)->point = m_pFire->m_vecPosition;
            }
        }
    }

    if (subTaskId == TASK_COMPLEX_CAR_DRIVE_WANDER) {
        if (m_bIsDriver && gFireManager.FindNearestFire(m_pVehicle->GetPosition(), true, true))
            return CreateFirstSubTask(ped);
    }

    return m_pSubTask;
}

// 0x65A240
CTask* CTaskComplexDriveFireTruck::CreateSubTask(eTaskType taskType, CPed* ped) {
    switch (taskType) {
    case TASK_COMPLEX_CAR_DRIVE_WANDER:
        return new CTaskComplexCarDriveWander(m_pVehicle, 0, 10.0F);
    case TASK_COMPLEX_CAR_DRIVE_TO_POINT:
        return new CTaskComplexDriveToPoint(m_pVehicle, m_pFire->m_vecPosition, 30.0F, 0, -1, 25.0F, 2);
    case TASK_COMPLEX_USE_WATER_CANNON:
        return new CTaskComplexUseWaterCannon(m_pFire);
    case TASK_SIMPLE_CAR_DRIVE:
        return new CTaskSimpleCarDrive(m_pVehicle, nullptr, false);
    default:
        return nullptr;
    }
}
