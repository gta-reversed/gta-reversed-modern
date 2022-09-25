#include "StdInc.h"

#include "TaskComplexGetOnBoatSeat.h"

void CTaskComplexGetOnBoatSeat::InjectHooks() {
    RH_ScopedClass(CTaskComplexGetOnBoatSeat);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x649210);
    RH_ScopedInstall(Destructor, 0x649280);
    RH_ScopedInstall(Clone, 0x64A3B0, { .reversed = false });
    RH_ScopedInstall(CreateFirstSubTask, 0x649310, { .reversed = false });
}

// 0x649210
CTaskComplexGetOnBoatSeat::CTaskComplexGetOnBoatSeat(CVehicle* vehicle) {
    m_Vehicle = vehicle;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x649280
CTaskComplexGetOnBoatSeat::~CTaskComplexGetOnBoatSeat() {
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x6492E0
bool CTaskComplexGetOnBoatSeat::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return priority == ABORT_PRIORITY_IMMEDIATE && m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_IMMEDIATE, event);
}

// 0x649300
CTask* CTaskComplexGetOnBoatSeat::CreateNextSubTask(CPed* ped) {
    return nullptr;
}

// 0x649310
CTask* CTaskComplexGetOnBoatSeat::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x649310, CTaskComplexGetOnBoatSeat*, CPed*>(this, ped);
}

// 0x6493D0
CTask* CTaskComplexGetOnBoatSeat::ControlSubTask(CPed* ped) {
    return m_pSubTask;
}
