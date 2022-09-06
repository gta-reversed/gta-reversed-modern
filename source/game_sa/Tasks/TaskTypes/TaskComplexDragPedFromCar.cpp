#include "StdInc.h"

#include "TaskComplexDragPedFromCar.h"

void CTaskComplexDragPedFromCar__InjectHooks() {
    RH_ScopedClass(CTaskComplexDragPedFromCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(ControlSubTask_Reversed, 0x640530);
    // RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x643D00);
}
CTask* CTaskComplexDragPedFromCar::ControlSubTask(CPed* ped) { return ControlSubTask_Reversed(ped); }
CTask* CTaskComplexDragPedFromCar::CreateFirstSubTask(CPed* ped) { return CreateFirstSubTask_Reversed(ped); }

// 0x640430
CTaskComplexDragPedFromCar::CTaskComplexDragPedFromCar(CPed* ped, int32 draggedPedDownTime) : CTaskComplexEnterCar(nullptr, false, false, true, false) {
    m_Ped = ped;
    CEntity::SafeRegisterRef(m_Ped);
    m_nDraggedPedDownTime = draggedPedDownTime;
}

// 0x6404D0
CTaskComplexDragPedFromCar::~CTaskComplexDragPedFromCar() {
    CEntity::SafeCleanUpRef(m_Ped);
}

// 0x640530
CTask* CTaskComplexDragPedFromCar::ControlSubTask_Reversed(CPed* ped) {
    if (m_nNumGettingInSet)
        return CTaskComplexEnterCar::ControlSubTask(ped);

    if (!m_Ped || m_Ped->bInVehicle || !m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr))
        return CTaskComplexEnterCar::ControlSubTask(ped);

    return CTaskComplexEnterCar::CreateSubTask(TASK_NONE, nullptr);
}

// 0x643D00
CTask* CTaskComplexDragPedFromCar::CreateFirstSubTask_Reversed(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x643D00, CTaskComplexDragPedFromCar*, CPed*>(this, ped);
}
