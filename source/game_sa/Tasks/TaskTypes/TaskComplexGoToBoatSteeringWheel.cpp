#include "StdInc.h"

#include "TaskComplexGoToBoatSteeringWheel.h"
#include "TaskSimpleStandStill.h"
#include "TaskComplexGoToPointAndStandStill.h"

void CTaskComplexGoToBoatSteeringWheel::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToBoatSteeringWheel);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x649090);
    RH_ScopedInstall(Destructor, 0x649100);
    RH_ScopedInstall(Clone, 0x64A350, { .reversed = false });
    RH_ScopedInstall(CreateNextSubTask, 0x64E350, { .reversed = false });
    RH_ScopedInstall(CreateFirstSubTask, 0x64E390, { .reversed = false });
    RH_ScopedInstall(ControlSubTask, 0x64E3B0, { .reversed = false });
}

// 0x649090
CTaskComplexGoToBoatSteeringWheel::CTaskComplexGoToBoatSteeringWheel(CVehicle* vehicle) : CTaskComplex() {
    m_Vehicle = vehicle;
    byte1C = false;
    m_FirstSubTaskStartTime = 0;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x649100
CTaskComplexGoToBoatSteeringWheel::~CTaskComplexGoToBoatSteeringWheel() {
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x64E350
CTask* CTaskComplexGoToBoatSteeringWheel::CreateNextSubTask(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_STAND_STILL:
        return CreateSubTask(TASK_FINISHED);
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
        byte1C = true;
        return CreateSubTask(TASK_FINISHED);
    default:
        return nullptr;
    }
}

// 0x649160
void CTaskComplexGoToBoatSteeringWheel::ComputeTargetPos() {
    assert(false);
}

// 0x64CDA0
CTask* CTaskComplexGoToBoatSteeringWheel::CreateSubTask(eTaskType taskType) {
    switch (taskType) {
    case TASK_SIMPLE_STAND_STILL:
        return new CTaskSimpleStandStill(-1, false, false, 8.0f);
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
        ComputeTargetPos();
        return new CTaskComplexGoToPointAndStandStill(PEDMOVE_WALK, m_TargetPos, 0.5f, 2.0f, false, false);
    case TASK_FINISHED:
        return nullptr;
    default:
        return nullptr;
    }
}

// 0x64E390
CTask* CTaskComplexGoToBoatSteeringWheel::CreateFirstSubTask(CPed* ped) {
    m_FirstSubTaskStartTime = CTimer::GetTimeInMS();
    return CreateSubTask(TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL);
}

// 0x64E3B0
CTask* CTaskComplexGoToBoatSteeringWheel::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64E3B0, CTaskComplexGoToBoatSteeringWheel*, CPed*>(this, ped);
}
