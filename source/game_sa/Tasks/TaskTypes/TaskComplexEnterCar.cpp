#include "StdInc.h"

#include "TaskComplexEnterCar.h"
#include "TaskComplexGoToCarDoorAndStandStill.h"
#include "TaskSimpleCarSlowDragPedOut.h"
#include "TaskSimpleWaitUntilPedIsOutCar.h"
#include "TaskSimpleCarSetPedOut.h"
#include "TaskSimpleCarCloseDoorFromOutside.h"
#include "TaskSimpleCarGetIn.h"
#include "TaskSimpleCarShuffle.h"
#include "TaskSimpleCarWaitForDoorNotToBeInUse.h"
#include "TaskSimpleCarSetPedInAsPassenger.h"
#include "TaskSimpleCarSetPedInAsDriver.h"
#include "TaskSimpleCarCloseDoorFromInside.h"
#include "TaskComplexGoToCarDoorAndStandStill.h"
#include "TaskSimpleCarAlign.h"
#include "TaskSimpleCarOpenDoorFromOutside.h"
#include "TaskSimpleCarOpenLockedDoorFromOutside.h"
#include "TaskSimplePickUpBike.h"
#include "TaskSimpleCarDriveTimed.h"
#include "TaskComplexLeaveCar.h"
#include "TaskComplexEnterBoatAsDriver.h"
#include "TaskComplexFallAndGetUp.h"
#include "TaskComplexFallAndGetUp.h"
#include "TaskSimpleLeaveGroup.h"
#include "TaskSimpleStandStill.h"

#include "EventCopCarBeingStolen.h"

void CTaskComplexEnterCar::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexEnterCar, 0x86e6f0, 12);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63A220);
    RH_ScopedInstall(Destructor, 0x63DFA0);

    RH_ScopedInstall(GetTargetPos, 0x63A300);
    RH_ScopedInstall(GetCameraAvoidVehicle, 0x63A690);
    RH_ScopedInstall(SetVehicleFlags, 0x63AB90);
    RH_ScopedInstall(CreateSubTask, 0x63E040);

    RH_ScopedVMTInstall(MakeAbortable, 0x63A730, { .reversed = false });
    RH_ScopedVMTInstall(CreateNextSubTask, 0x63E990, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x643A60, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x63A890, { .reversed = false });
    RH_ScopedVMTInstall(CreateNextSubTask_AfterSimpleCarAlign, 0x63F970, { .reversed = false });
}

// 0x63A220
CTaskComplexEnterCar::CTaskComplexEnterCar(CVehicle* targetVehicle, bool bAsDriver, bool bQuitAfterOpeningDoor, bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff) :
    m_bAsDriver{bAsDriver},
    m_bQuitAfterOpeningDoor{bQuitAfterOpeningDoor},
    m_bQuitAfterDraggingPedOut{bQuitAfterDraggingPedOut},
    m_bCarryOnAfterFallingOff{bCarryOnAfterFallingOff},
    m_Car{targetVehicle}
{
    CEntity::SafeRegisterRef(m_Car);
}

// 0x63DFA0
CTaskComplexEnterCar::~CTaskComplexEnterCar() {
    delete m_LineUpUtility;

    CEntity::SafeCleanUpRef(m_Car);
    if (m_Car) {
        m_Car->m_nNumGettingIn -= m_NumGettingInSet;
        m_Car->ClearGettingInFlags(m_DoorFlagsSet);
    }
}

// 0x63A730
bool CTaskComplexEnterCar::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x63A730, CTask*, CPed*, int32, const CEvent*>(this, ped, priority, event);
}

// 0x63E990
CTask* CTaskComplexEnterCar::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63E990, CTask*, CPed*>(this, ped);
}

// 0x643A60
CTask* CTaskComplexEnterCar::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x643A60, CTask*, CPed*>(this, ped);
}

// 0x63A890
CTask* CTaskComplexEnterCar::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63A890, CTask*, CPed*>(this, ped);
}

// 0x63E040
CTask* CTaskComplexEnterCar::CreateSubTask(eTaskType taskType, CPed* ped) {
    switch (taskType) {
    case TASK_SIMPLE_CAR_SLOW_DRAG_PED_OUT: { // 0x63E8CD
        if (ped && ped->IsPlayer() && !ped->AsPlayer()->bHasDisplayedPlayerQuitEnterCarHelpText) {
            ped->AsPlayer()->bHasDisplayedPlayerQuitEnterCarHelpText = true;

            // To stop Carl from entering a car once he has opened the door or dragged out a
            // driver or passenger, use the movement controls or press ~k~~PED_FIREWEAPON~.
            CHud::SetHelpMessage(TheText.Get("JCK_HLP"));
        }
        return new CTaskSimpleCarSlowDragPedOut{ m_Car, (eTargetDoor)m_TargetDoor, m_LineUpUtility, m_bQuitAfterDraggingPedOut };
    }
    case TASK_SIMPLE_WAIT_UNTIL_PED_OUT_CAR: // 0x63E846
        return new CTaskSimpleWaitUntilPedIsOutCar{ m_DraggedPed, IsTargetDoorOnTheLeft() ? -m_Car->GetRight() : m_Car->GetRight() };
    case TASK_FINISHED: { // 0x63E674
        if (!ped) {
            return nullptr;
        }

        if (!ped->bInVehicle && !ped->m_bUsesCollision) { // 0x63E67A
            ped->m_bUsesCollision = true;
            if (m_Car && m_TargetDoor != 0) { // TODO: Enum
                CTaskSimpleCarSetPedOut::PositionPedOutOfCollision(ped, m_Car, m_TargetDoor);
            }
        }

        if (m_bAsDriver && !m_bQuitAfterOpeningDoor && !m_bQuitAfterDraggingPedOut) { // Moved this common piece out here
            if (ped->IsPlayer()) { // 0x63E6AA
                if (m_Car && m_Car->IsLawEnforcementVehicle()) {
                    if (m_DoorFlagsSet) {
                        GetEventGlobalGroup()->Add(CEventCopCarBeingStolen{ ped, m_Car });
                    }
                }
            }

            if (!ped->bInVehicle) { // 0x63E717
                if (const auto pedGrp = ped->GetGroup()) {
                    if (pedGrp->GetMembership().IsLeader(ped)) {
                        pedGrp->GetIntelligence().AddEvent(CEventLeaderQuitEnteringCarAsDriver{});
                    }
                }
            }
        }

        if (m_Car && m_CruiseSpeed >= 0.f) {
            if (ped->IsPlayer() ? !ped->bInVehicle && m_Car->m_pDriver && m_bQuitAfterOpeningDoor : ped->bInVehicle) {  // 0x63E7A4 - NOTE/BUG: Why is it checking `!bInVehicle` for the player? Typo?
                m_Car->m_autoPilot.m_nCruiseSpeed = (uint32)m_CruiseSpeed;
            }
        }

        return nullptr;
    }
    case TASK_SIMPLE_CAR_SET_PED_OUT: // 0x63E619
        return new CTaskSimpleCarSetPedOut{ m_Car, (eTargetDoor)m_TargetDoor, true };
    case TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_OUTSIDE: // 0x63E60D
        return new CTaskSimpleCarCloseDoorFromOutside{ m_Car, (uint32)m_TargetDoor, m_LineUpUtility };
    case TASK_SIMPLE_CAR_GET_IN: // 0x63E50F
        return new CTaskSimpleCarGetIn{ m_Car, (uint32)m_TargetDoor, m_LineUpUtility };
    case TASK_SIMPLE_CAR_SHUFFLE: // 0x63E56F
        return new CTaskSimpleCarShuffle{ m_Car, m_TargetDoor, m_LineUpUtility };
    case TASK_SIMPLE_CAR_WAIT_FOR_DOOR_NOT_TO_BE_IN_USE: // 0x63E503
        return new CTaskSimpleCarWaitForDoorNotToBeInUse{m_Car, (uint32)m_TargetDoor, (uint32)m_TargetDoorOppositeToFlag };
    case TASK_SIMPLE_CAR_SET_PED_IN_AS_PASSENGER: // 0x63E5D7
        return new CTaskSimpleCarSetPedInAsPassenger{ m_Car, (eTargetDoor)m_TargetDoor, false, m_LineUpUtility };
    case TASK_SIMPLE_CAR_SET_PED_IN_AS_DRIVER: // 0x63E5A1
        return new CTaskSimpleCarSetPedInAsDriver{ m_Car, m_LineUpUtility };
    case TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_INSIDE: // 0x0063E387
        return new CTaskSimpleCarCloseDoorFromInside{ m_Car, (uint32)m_TargetDoor, m_LineUpUtility };
    case TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL: // 0x63E387
        return new CTaskComplexGoToCarDoorAndStandStill{ m_Car, m_MoveState, m_bAsDriver, m_TargetSeat, 0.5f, 4.f, 50.f, 30'000 };
    case TASK_SIMPLE_CAR_ALIGN: // 0x63E3C1
        return new CTaskSimpleCarAlign{ m_Car, m_TargetDoorPos, (uint32)m_TargetDoor, m_LineUpUtility };
    case TASK_SIMPLE_CAR_OPEN_DOOR_FROM_OUTSIDE: // 0x63E405
        return new CTaskSimpleCarOpenDoorFromOutside{ m_Car, m_TargetDoor, m_LineUpUtility, m_bQuitAfterOpeningDoor };
    case TASK_SIMPLE_CAR_OPEN_LOCKED_DOOR_FROM_OUTSIDE: // 0x63E43B
        return new CTaskSimpleCarOpenLockedDoorFromOutside{ m_Car, m_TargetDoor, m_LineUpUtility };
    case TASK_SIMPLE_BIKE_PICK_UP: // 0x63E471
        return new CTaskSimplePickUpBike{ m_Car, m_TargetDoor, m_LineUpUtility };
    case TASK_SIMPLE_CAR_DRIVE_TIMED: // 0x63E314
        return new CTaskSimpleCarDriveTimed{ m_Car };
    case TASK_COMPLEX_LEAVE_CAR:
        return new CTaskComplexLeaveCar{ m_Car, 0, 0, true, false }; // 0x63E2E8
    case TASK_COMPLEX_ENTER_BOAT_AS_DRIVER: // 0x63E2AE
        return new CTaskComplexEnterBoatAsDriver{ m_Car };
    case TASK_COMPLEX_FALL_AND_GET_UP: { // 0x63E15E
        if (FindPlayerPed() == ped) {
            FindPlayerInfo().SetLastTargetVehicle(m_Car);
        }
        if (ped && !ped->bInVehicle) {
            ped->m_bUsesCollision = true;
        }
        if (m_Car) {
            CTaskSimpleCarSetPedOut::PositionPedOutOfCollision(ped, m_Car, m_TargetDoor);

            assert(m_Car->m_nNumGettingIn < m_NumGettingInSet);
            m_Car->m_nNumGettingIn -= m_NumGettingInSet;
            m_NumGettingInSet       = false;

            m_Car->ClearGettingInFlags(m_DoorFlagsSet);
            m_DoorFlagsSet = 0;

            if (m_Car->IsAutomobile()) {
                if (!m_Car->IsDoorMissing((eDoors)m_TargetDoor)) { // Important to cast!
                    m_Car->AsAutomobile()->m_damageManager.SetDoorOpen((eDoors)m_TargetDoor);
                }
            }
        }
        return new CTaskComplexFallAndGetUp{ IsTargetDoorOnTheLeft() ? ANIM_ID_KO_SPIN_L : ANIM_ID_KO_SPIN_R, ANIM_GROUP_DEFAULT, 2000 };
    }
    case TASK_NONE:
        return new CTaskSimpleLeaveGroup{}; // 0x63E0F8 - NOTE/TODO: Weird
    case TASK_SIMPLE_STAND_STILL:
        return new CTaskSimpleStandStill{}; // 0x63E0CE
    default:
        NOTSA_UNREACHABLE("taskType = {}", taskType);
    }
}

// 0x63F970
CTask* CTaskComplexEnterCar::CreateNextSubTask_AfterSimpleCarAlign(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63F970, CTask*, CPed*>(this, ped);
}

// 0x63AB90
void CTaskComplexEnterCar::SetVehicleFlags(CPed* ped) {
    m_DoorFlagsSet = CCarEnterExit::ComputeDoorFlag(m_Car, m_TargetDoor, true);
    m_Car->SetGettingInFlags(m_DoorFlagsSet);

    m_NumGettingInSet = true;
    m_Car->m_nNumGettingIn++;

    if (m_TargetDoorOppositeToFlag) {
        const auto oppositeDoorFlag = CCarEnterExit::ComputeDoorFlag(m_Car, m_TargetDoorOppositeToFlag, true);
        if (oppositeDoorFlag != m_DoorFlagsSet) {
            m_Car->SetGettingInFlags(oppositeDoorFlag);
            m_DoorFlagsSet |= oppositeDoorFlag;
        }
    }
}

CVector CTaskComplexEnterCar::GetTargetPos() const {
    if (m_TargetDoor != 0) { // TODO: Enum
        return m_TargetDoorPos;
    }
    if (const auto tGoTo = CTask::DynCast<CTaskComplexGoToCarDoorAndStandStill>(m_pSubTask)) {
        return tGoTo->GetTargetPt();
    }
    return {};
}

// 0x63A690
CVehicle* CTaskComplexEnterCar::GetCameraAvoidVehicle() {
    if (m_Car && m_pSubTask) {
        switch (m_pSubTask->GetTaskType()) {
        case TASK_COMPLEX_LEAVE_CAR:
        case TASK_SIMPLE_CAR_OPEN_DOOR_FROM_OUTSIDE:
        case TASK_SIMPLE_CAR_OPEN_LOCKED_DOOR_FROM_OUTSIDE:
        case TASK_SIMPLE_BIKE_PICK_UP:
        case TASK_SIMPLE_STAND_STILL:
        case TASK_SIMPLE_CAR_QUICK_DRAG_PED_OUT:
        case TASK_SIMPLE_CAR_SLOW_DRAG_PED_OUT:
        case TASK_SIMPLE_CAR_SET_PED_OUT:
        case TASK_COMPLEX_ENTER_BOAT_AS_DRIVER:
        case TASK_SIMPLE_CAR_DRIVE_TIMED:
        case TASK_SIMPLE_CAR_GET_IN:
        case TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_INSIDE:
        case TASK_SIMPLE_CAR_SHUFFLE:
        case TASK_SIMPLE_CAR_ALIGN:
        case TASK_SIMPLE_CAR_SET_PED_IN_AS_DRIVER:
        case TASK_SIMPLE_CAR_SET_PED_IN_AS_PASSENGER:
            return m_Car;
        }
    }
    return nullptr;
}
