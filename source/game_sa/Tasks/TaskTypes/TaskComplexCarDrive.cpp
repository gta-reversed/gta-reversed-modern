#include "StdInc.h"

#include "TaskComplexCarDrive.h"
#include "TaskComplexEnterCarAsPassenger.h"
#include "TaskComplexEnterCarAsDriver.h"
#include "TaskSimpleCarDrive.h"
#include "TaskComplexWander.h"

void CTaskComplexCarDrive::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexCarDrive, 0x86E934, 14);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor_0, 0x63C9D0, { .enabled = false});
    RH_ScopedInstall(Constructor_1, 0x63C940, { .enabled = false});
    RH_ScopedInstall(Destructor, 0x63CA40);

    RH_ScopedInstall(CreateSubTask, 0x642FA0, { .enabled = false, .locked = true });

    RH_ScopedVMTInstall(CreateSubTaskCannotGetInCar, 0x643200, { .enabled = false});
    RH_ScopedVMTInstall(SetUpCar, 0x63CAE0, { .enabled = false});
    RH_ScopedVMTInstall(Drive, 0x63CAD0, { .enabled = false});
    RH_ScopedVMTInstall(Clone, 0x63DC90, { .enabled = false});
    RH_ScopedVMTInstall(CreateNextSubTask, 0x644E20, { .enabled = false, .locked = true });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x645100, { .enabled = false, .locked = true});
    RH_ScopedVMTInstall(ControlSubTask, 0x645240, { .enabled = false});
}

// 0x63C9D0
// asDriver stuff is NOTSA
CTaskComplexCarDrive::CTaskComplexCarDrive(CVehicle* vehicle, bool asDriver) :
    m_asDriver{asDriver}
{
    m_pVehicle              = vehicle;
    m_fSpeed                = 0.0f;
    m_carModelIndexToCreate = -1;
    m_nCarDrivingStyle      = DRIVING_STYLE_STOP_FOR_CARS;
    m_bSavedVehicleBehavior = false;
    CEntity::SafeRegisterRef(m_pVehicle);
}

// 0x63C940
CTaskComplexCarDrive::CTaskComplexCarDrive(CVehicle* vehicle, float speed, int32 carModelIndexToCreate, eCarDrivingStyle carDrivingStyle) : CTaskComplex() {
    m_fSpeed                = speed;
    m_carModelIndexToCreate = carModelIndexToCreate;
    m_pVehicle              = vehicle;
    m_nCarDrivingStyle      = carDrivingStyle;
    m_bSavedVehicleBehavior = false;
    CEntity::SafeRegisterRef(m_pVehicle);
}

// 0x63CA40
CTaskComplexCarDrive::~CTaskComplexCarDrive() {
    if (m_pVehicle) {
        if (m_bSavedVehicleBehavior) {
            m_pVehicle->m_autoPilot.m_nCarDrivingStyle = static_cast<eCarDrivingStyle>(m_nOldCarDrivingStyle);
            m_pVehicle->m_autoPilot.m_nCarMission      = static_cast<eCarMission>(m_nCarMission);
            m_pVehicle->m_autoPilot.m_nCruiseSpeed     = m_nSpeed;
        }
        CEntity::SafeCleanUpRef(m_pVehicle);
    }
}

// 0x63DC90
CTask* CTaskComplexCarDrive::Clone() const {
    auto* task = new CTaskComplexCarDrive(m_pVehicle, m_fSpeed, m_carModelIndexToCreate, static_cast<eCarDrivingStyle>(m_nCarDrivingStyle));
    task->m_asDriver = m_asDriver;
    return task;
}

// 0x644E20
CTask* CTaskComplexCarDrive::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x644E20, CTaskComplexCarDrive*, CPed*>(this, ped);
}

// 0x645100
CTask* CTaskComplexCarDrive::CreateFirstSubTask(CPed* ped) {
    if (!m_pVehicle) {
        if (ped->m_pVehicle && ped->bInVehicle) {
            m_pVehicle = ped->m_pVehicle;
            m_pVehicle->RegisterReference(reinterpret_cast<CEntity**>(m_pVehicle));
            return CreateSubTask(TASK_SIMPLE_CAR_DRIVE, ped);
        }
        return m_asDriver ? CreateSubTask(TASK_COMPLEX_ENTER_ANY_CAR_AS_DRIVER, ped) : nullptr;
    }

    if (ped->m_pVehicle && ped->bInVehicle) {
        if (ped->m_pVehicle == m_pVehicle)
            return CreateSubTask(TASK_SIMPLE_CAR_DRIVE, ped);
        else
            return CreateSubTask(TASK_COMPLEX_LEAVE_ANY_CAR, ped);
    } else {
        if (!m_pVehicle->IsBike()) {
            CUpsideDownCarCheck carCheck;
            if (carCheck.IsCarUpsideDown(m_pVehicle) == 0) {
                return CreateSubTask(m_asDriver ? TASK_COMPLEX_ENTER_CAR_AS_DRIVER : TASK_COMPLEX_ENTER_CAR_AS_PASSENGER, ped);
            }
            return m_asDriver ? CreateSubTask(TASK_COMPLEX_ENTER_ANY_CAR_AS_DRIVER, ped) : nullptr;
        }
        return CreateSubTask(m_asDriver ? TASK_COMPLEX_ENTER_CAR_AS_DRIVER : TASK_COMPLEX_ENTER_CAR_AS_PASSENGER, ped);
    }
}

// 0x645240
CTask* CTaskComplexCarDrive::ControlSubTask(CPed* ped) {
    if (ped->m_pVehicle && ped->bInVehicle) {
        switch (m_pSubTask->GetTaskType()) {
        case TASK_SIMPLE_CAR_DRIVE:
            return Drive(ped);
        case TASK_COMPLEX_GO_TO_POINT_ANY_MEANS:
            if (ped->m_pVehicle && ped->bInVehicle) {
                m_pVehicle = ped->m_pVehicle;
                m_pVehicle->RegisterReference(reinterpret_cast<CEntity**>(m_pVehicle));
                return CreateSubTask(TASK_SIMPLE_CAR_DRIVE, ped);
            }
        }
    }
    return m_pSubTask;
}

// 0x63CAE0
void CTaskComplexCarDrive::SetUpCar() {
    m_nOldCarDrivingStyle   = m_pVehicle->m_autoPilot.m_nCarDrivingStyle;
    m_nCarMission           = m_pVehicle->m_autoPilot.m_nCarMission;
    m_nSpeed                = m_pVehicle->m_autoPilot.m_nCruiseSpeed;
    m_bSavedVehicleBehavior = true;
}

// 0x643200
CTask* CTaskComplexCarDrive::CreateSubTaskCannotGetInCar(CPed* ped) {
    return CreateSubTask(TASK_FINISHED, ped);
}

// 0x63CAD0
CTask* CTaskComplexCarDrive::Drive(CPed* ped) {
    return m_pSubTask;
}

// 0x642FA0
CTask* CTaskComplexCarDrive::CreateSubTask(eTaskType taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x642FA0, CTaskComplexCarDrive*, eTaskType, CPed*>(this, taskType, ped);

    /*
    if (taskType <= TASK_COMPLEX_ENTER_ANY_CAR_AS_DRIVER) {
        if (taskType != TASK_COMPLEX_ENTER_ANY_CAR_AS_DRIVER) {
            switch (taskType) {
            case TASK_COMPLEX_ENTER_CAR_AS_PASSENGER:
                return new CTaskComplexEnterCarAsPassenger(m_pVehicle, 0, false);
            case TASK_COMPLEX_ENTER_CAR_AS_DRIVER:
                return new CTaskComplexEnterCarAsDriver(m_pVehicle);
            case TASK_SIMPLE_CAR_DRIVE:
                SetUpCar();
                return new CTaskSimpleCarDrive(m_pVehicle, nullptr, false);
            case TASK_COMPLEX_LEAVE_ANY_CAR:
                return new CTaskComplexLeaveAnyCar(0, true, false); // todo:
            default:
                return nullptr;
            }
            return nullptr;
        }
        return new CTaskComplexEnterAnyCarAsDriver(); // todo:
    }
    return nullptr;

    switch (taskType) {
    case TASK_SIMPLE_CREATE_CAR_AND_GET_IN:
        return new CTaskSimpleCreateCarAndGetIn(&ped->GetPosition(), m_carModelIndexToCreate); // todo:
    case TASK_COMPLEX_WANDER:
        return CTaskComplexWander::GetWanderTaskByPedType(ped);
    case TASK_FINISHED:
        return nullptr;
    }
    return nullptr;
    */
}
