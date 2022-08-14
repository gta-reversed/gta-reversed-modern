#include "StdInc.h"
#include "TaskComplexGoToBoatSteeringWheel.h"

void CTaskComplexGoToBoatSteeringWheel::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToBoatSteeringWheel);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x649090);
    RH_ScopedInstall(Destructor, 0x649100);

    // RH_ScopedInstall(Clone, 0x64A350);
    RH_ScopedInstall(GetTaskType, 0x6490F0);
    // RH_ScopedInstall(CreateNextSubTask, 0x64E350);
    // RH_ScopedInstall(CreateFirstSubTask, 0x64E390);
    // RH_ScopedInstall(ControlSubTask, 0x64E3B0);
}

// 0x649090
CTaskComplexGoToBoatSteeringWheel::CTaskComplexGoToBoatSteeringWheel(CVehicle*) {}

// 0x649100
CTaskComplexGoToBoatSteeringWheel::~CTaskComplexGoToBoatSteeringWheel() {}

// 0x64A350
CTask* CTaskComplexGoToBoatSteeringWheel::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x64A350, CTaskComplexGoToBoatSteeringWheel*>(this);
}

// 0x64E350
CTask* CTaskComplexGoToBoatSteeringWheel::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64E350, CTaskComplexGoToBoatSteeringWheel*, CPed*>(this, ped);
}

// 0x64E390
CTask* CTaskComplexGoToBoatSteeringWheel::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64E390, CTaskComplexGoToBoatSteeringWheel*, CPed*>(this, ped);
}

// 0x64E3B0
CTask* CTaskComplexGoToBoatSteeringWheel::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64E3B0, CTaskComplexGoToBoatSteeringWheel*, CPed*>(this, ped);
}
