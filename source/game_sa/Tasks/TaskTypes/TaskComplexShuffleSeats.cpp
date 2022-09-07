#include "StdInc.h"
#include "TaskComplexShuffleSeats.h"
#include "TaskSimpleCarSetPedInAsDriver.h"
#include "TaskSimpleCarShuffle.h"
#include "TaskSimpleCarSetPedInAsPassenger.h"
#include "TaskSimpleCarSetPedOut.h"

void CTaskComplexShuffleSeats::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexShuffleSeats, 0x86ea40, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63D130);
    RH_ScopedInstall(Destructor, 0x63D1A0);

    RH_ScopedInstall(CreateSubTask, 0x63D240);
    RH_ScopedInstall(CreateTaskUtilityLineUpPedWithCar, 0x63D610);

    RH_ScopedVMTInstall(Clone, 0x63DEB0);
    RH_ScopedVMTInstall(GetTaskType, 0x63D190);
    RH_ScopedVMTInstall(MakeAbortable, 0x63D220);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x63D420);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x643700);
    RH_ScopedVMTInstall(ControlSubTask, 0x63D5C0);
}

// 0x63D130
CTaskComplexShuffleSeats::CTaskComplexShuffleSeats(CVehicle* veh) :
    m_veh{veh}
{
    CEntity::SafeRegisterRef(m_veh);
}

CTaskComplexShuffleSeats::CTaskComplexShuffleSeats(const CTaskComplexShuffleSeats& o) :
    CTaskComplexShuffleSeats{o.m_veh}
{
}

// 0x63D1A0
CTaskComplexShuffleSeats::~CTaskComplexShuffleSeats() {
    CEntity::SafeCleanUpRef(m_veh);
    delete m_utilityLineUp;
}

// 0x63D240
CTask* CTaskComplexShuffleSeats::CreateSubTask(eTaskType taskType, CPed* ped) {
    switch (taskType) {
    case TASK_SIMPLE_CAR_SET_PED_IN_AS_DRIVER:
        return new CTaskSimpleCarSetPedInAsDriver{m_veh, m_utilityLineUp};
    case TASK_SIMPLE_CAR_SHUFFLE:
        return new CTaskSimpleCarShuffle{ m_veh, m_startDoor, m_utilityLineUp };
    case TASK_SIMPLE_CAR_SET_PED_IN_AS_PASSENGER:
        return new CTaskSimpleCarSetPedInAsPassenger{ m_veh, (int32)m_targetDoor, m_utilityLineUp };
    case TASK_SIMPLE_CAR_SET_PED_OUT:
        return new CTaskSimpleCarSetPedOut{ m_veh, CCarEnterExit::ComputeTargetDoorToExit(m_veh, ped), true };
    case TASK_FINISHED: {
        if (!ped->bInVehicle) {
            ped->m_bUsesCollision = true;
        }
        return nullptr;
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x63D610
void CTaskComplexShuffleSeats::CreateTaskUtilityLineUpPedWithCar(CPed* ped) {
    m_startDoor = [this, ped] {
        if (m_veh->IsDriver(ped)) {
            return TARGET_DOOR_DRIVER;
        }
        if (const auto optPsgrIdx = m_veh->GetPassengerIndex(ped)) {
            switch (*optPsgrIdx) {
            case 0:
                return TARGET_DOOR_FRONT_RIGHT;
            case 1:
                return TARGET_DOOR_REAR_LEFT;
            }
        }
        return TARGET_DOOR_REAR_RIGHT;
    }();

    m_utilityLineUp = new CTaskUtilityLineUpPedWithCar{
        CCarEnterExit::GetPositionToOpenCarDoor(m_veh, m_startDoor) - ped->GetPosition(),
        600,
        0,
        (int32)m_startDoor
    };
}

// 0x63D220
bool CTaskComplexShuffleSeats::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return priority == ABORT_PRIORITY_IMMEDIATE && m_pSubTask->MakeAbortable(ped, priority, event);
}

// 0x63D420
CTask* CTaskComplexShuffleSeats::CreateNextSubTask(CPed* ped) {
    return CreateSubTask([this, ped]{
        if (m_abort) {
            switch (m_pSubTask->GetTaskType()) {
            case TASK_SIMPLE_CAR_SET_PED_IN_AS_PASSENGER:
            case TASK_SIMPLE_CAR_SHUFFLE:
            case TASK_SIMPLE_CAR_SET_PED_IN_AS_DRIVER:
                return TASK_SIMPLE_CAR_SET_PED_OUT;
            case TASK_NONE:
            case TASK_SIMPLE_CAR_SET_PED_OUT:
                return TASK_FINISHED;
            default:
                NOTSA_UNREACHABLE();
            }
        }

        switch (m_pSubTask->GetTaskType()) {
        case TASK_SIMPLE_CAR_SET_PED_IN_AS_DRIVER:
        case TASK_SIMPLE_CAR_SET_PED_IN_AS_PASSENGER:
        case TASK_NONE:
            return TASK_FINISHED;
        case TASK_SIMPLE_CAR_SHUFFLE: {
            m_targetDoor = [this, ped] {
                switch (m_startDoor) {
                case TARGET_DOOR_FRONT_RIGHT:
                    return TARGET_DOOR_DRIVER;
                case TARGET_DOOR_REAR_RIGHT:
                    return TARGET_DOOR_REAR_LEFT;
                case TARGET_DOOR_DRIVER:
                    return TARGET_DOOR_FRONT_RIGHT;
                case TARGET_DOOR_REAR_LEFT:
                    return TARGET_DOOR_REAR_RIGHT;
                default:
                    NOTSA_UNREACHABLE();
                }
            }();

            if (m_targetDoor == TARGET_DOOR_DRIVER) { // Inverted
                return m_veh->m_pDriver
                    ? TASK_FINISHED
                    : TASK_SIMPLE_CAR_SET_PED_IN_AS_DRIVER;
            } else {
                return m_veh->m_apPassengers[CCarEnterExit::ComputePassengerIndexFromCarDoor(m_veh, m_targetDoor)]
                    ? TASK_SIMPLE_CAR_SET_PED_IN_AS_PASSENGER
                    : TASK_FINISHED;
            }
        }
        default:
            NOTSA_UNREACHABLE();
        }
        
    }(), ped);
}

// 0x643700
CTask* CTaskComplexShuffleSeats::CreateFirstSubTask(CPed* ped) {
    return CreateSubTask([this, ped] {
        if (!m_veh || !CCarEnterExit::IsVehicleHealthy(m_veh) || !CCarEnterExit::IsPedHealthy(ped)) {
            return TASK_NONE;
        } else {
            CreateTaskUtilityLineUpPedWithCar(ped);
            return TASK_SIMPLE_CAR_SHUFFLE;
        }
    }(), ped);
}

// 0x63D5C0
CTask* CTaskComplexShuffleSeats::ControlSubTask(CPed* ped) {
    if (!m_veh || !CCarEnterExit::IsVehicleHealthy(m_veh) || !CCarEnterExit::IsPedHealthy(ped)) {
        m_abort = true;
        m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_LEISURE, nullptr);
    }
    return m_pSubTask;
}
