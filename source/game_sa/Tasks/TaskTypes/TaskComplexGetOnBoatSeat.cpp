#include "StdInc.h"
#include "TaskComplexGetOnBoatSeat.h"

void CTaskComplexGetOnBoatSeat::InjectHooks() {
    RH_ScopedClass(CTaskComplexGetOnBoatSeat);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x649210);
    RH_ScopedInstall(Destructor, 0x649280);

    // RH_ScopedInstall(Clone, 0x64A3B0);
    RH_ScopedInstall(GetTaskType, 0x649270);
    // RH_ScopedInstall(MakeAbortable, 0x6492E0);
    // RH_ScopedInstall(CreateNextSubTask, 0x649300);
    // RH_ScopedInstall(CreateFirstSubTask, 0x649310);
    // RH_ScopedInstall(ControlSubTask, 0x6493D0);
}

// 0x649210
CTaskComplexGetOnBoatSeat::CTaskComplexGetOnBoatSeat(CVehicle*) {}

// 0x649280
CTaskComplexGetOnBoatSeat::~CTaskComplexGetOnBoatSeat() {}

// 0x64A3B0
CTask* CTaskComplexGetOnBoatSeat::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x64A3B0, CTaskComplexGetOnBoatSeat*>(this);
}

// 0x6492E0
bool CTaskComplexGetOnBoatSeat::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x6492E0, CTaskComplexGetOnBoatSeat*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x649300
CTask* CTaskComplexGetOnBoatSeat::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x649300, CTaskComplexGetOnBoatSeat*, CPed*>(this, ped);
}

// 0x649310
CTask* CTaskComplexGetOnBoatSeat::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x649310, CTaskComplexGetOnBoatSeat*, CPed*>(this, ped);
}

// 0x6493D0
CTask* CTaskComplexGetOnBoatSeat::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6493D0, CTaskComplexGetOnBoatSeat*, CPed*>(this, ped);
}
