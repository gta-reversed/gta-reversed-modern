#include "StdInc.h"

#include "TaskComplexEnterCar.h"
#include "TaskComplexGoToCarDoorAndStandStill.h"

void CTaskComplexEnterCar::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexEnterCar, 0x86e6f0, 12);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63A220);
    RH_ScopedInstall(Destructor, 0x63DFA0);

    RH_ScopedInstall(GetTargetPos, 0x63A300);
    RH_ScopedInstall(GetCameraAvoidVehicle, 0x63A690);
    RH_ScopedInstall(SetVehicleFlags, 0x63AB90);
    RH_ScopedInstall(CreateSubTask, 0x63E040, { .reversed = false });

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
CTask* CTaskComplexEnterCar::CreateSubTask(eTaskType type, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63E040, CTaskComplexEnterCar*, eTaskType, CPed*>(this, type, ped);
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
