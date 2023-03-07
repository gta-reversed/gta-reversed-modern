#include "StdInc.h"

#include "TaskComplexEnterCar.h"

void CTaskComplexEnterCar::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexEnterCar, 0x86e6f0, 12);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63A220);
    RH_ScopedInstall(Destructor, 0x63DFA0);

    RH_ScopedInstall(GetTargetPos, 0x63A300, { .reversed = false });
    RH_ScopedInstall(GetCameraAvoidVehicle, 0x63A690);
    //RH_ScopedInstall(SetVehicleFlags, 0x63AB90, { .reversed = false });
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
    m_car{targetVehicle}
{
    CEntity::SafeRegisterRef(m_car);
}

// 0x63DFA0
CTaskComplexEnterCar::~CTaskComplexEnterCar() {
    delete m_lineUpUtil;

    CEntity::SafeCleanUpRef(m_car);
    if (m_car) {
        m_car->m_nNumGettingIn -= m_numGettingInSet;
        m_car->ClearGettingInFlags(m_doorFlagsSet);
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

CVector CTaskComplexEnterCar::GetTargetPos() {
    CVector temp;
    plugin::CallMethod<0x63A300, CTaskComplexEnterCar*, CVector&>(this, temp);
    return temp;
}

// 0x63A690
CVehicle* CTaskComplexEnterCar::GetCameraAvoidVehicle() {
    if (m_car) {
        if (const auto st = GetSubTask()) {
            switch (st->GetTaskType()) {
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
                return m_car;
            }
        }
    }
    return nullptr;
}
