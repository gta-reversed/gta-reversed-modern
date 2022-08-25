#include "StdInc.h"

#include "TaskComplexDestroyCar.h"
// #include "TaskComplexDestroyCarArmed.h"
// #include "TaskComplexDestroyCarMelee.h"
#include "TaskComplexLeaveCar.h"

void CTaskComplexDestroyCar__InjectHooks() {
    RH_ScopedClass(CTaskComplexDestroyCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(MakeAbortable_Reversed, 0x621C80);
    // RH_ScopedInstall(ControlSubTask_Reversed, 0x6288C0);
    RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x62DA90);
    // RH_ScopedInstall(CreateNextSubTask_Reversed, 0x62D9E0);
    // RH_ScopedInstall(CreateSubTask, 0x6287A0);
}
bool CTaskComplexDestroyCar::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) { return MakeAbortable_Reversed(ped, priority, event); }
CTask* CTaskComplexDestroyCar::ControlSubTask(CPed* ped) { return ControlSubTask_Reversed(ped); }
CTask* CTaskComplexDestroyCar::CreateFirstSubTask(CPed* ped) { return CreateFirstSubTask_Reversed(ped); }
CTask* CTaskComplexDestroyCar::CreateNextSubTask(CPed* ped) { return CreateNextSubTask_Reversed(ped); }

// 0x621C00
CTaskComplexDestroyCar::CTaskComplexDestroyCar(CVehicle* vehicle, uint32 a3, uint32 a4, uint32 a5) : CTaskComplex() {
    dword14 = a3;
    dword18 = a4;
    dword1C = a5;
    m_Vehicle = vehicle;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x621CB0
CTaskComplexDestroyCar::~CTaskComplexDestroyCar() {
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x621C80
bool CTaskComplexDestroyCar::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_URGENT:
    case ABORT_PRIORITY_IMMEDIATE:
        return m_pSubTask->MakeAbortable(ped, priority, event);
    default:
        return false;
    }
}

// 0x6288C0
CTask* CTaskComplexDestroyCar::ControlSubTask_Reversed(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6288C0, CTaskComplexDestroyCar*, CPed*>(this, ped);
}

// 0x62DA90
CTask* CTaskComplexDestroyCar::CreateFirstSubTask_Reversed(CPed* ped) {
    dword0C = false;

    if (!m_Vehicle)
        return CreateSubTask(TASK_FINISHED);

    if (ped->m_pVehicle && ped->bInVehicle)
        return CreateSubTask(TASK_COMPLEX_LEAVE_CAR, ped);

    if (ped->GetActiveWeapon().IsTypeMelee())
        return CreateSubTask(TASK_COMPLEX_DESTROY_CAR_MELEE);

    return CreateSubTask(TASK_COMPLEX_DESTROY_CAR_ARMED);
}

// 0x62D9E0
CTask* CTaskComplexDestroyCar::CreateNextSubTask_Reversed(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62D9E0, CTaskComplexDestroyCar*, CPed*>(this, ped); // untested, maybe wrong

    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_BE_HIT:
        return CreateSubTask(TASK_FINISHED);
    case TASK_COMPLEX_FALL_AND_GET_UP:
        return CreateSubTask(TASK_FINISHED);
    case TASK_COMPLEX_LEAVE_CAR:
    case TASK_COMPLEX_DRAG_PED_FROM_CAR:
        return CreateSubTask(ped->GetActiveWeapon().IsTypeMelee() ? TASK_COMPLEX_DESTROY_CAR_MELEE : TASK_COMPLEX_DESTROY_CAR_ARMED);
    default:
        return nullptr;
    }
}

// 0x6287A0
CTask* CTaskComplexDestroyCar::CreateSubTask(eTaskType taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6287A0, CTaskComplexDestroyCar*, eTaskType, CPed*>(this, taskType, ped);

    switch (taskType) {
    case TASK_COMPLEX_DESTROY_CAR_ARMED:
        // return new CTaskComplexDestroyCarArmed(m_Vehicle, dword14, dword18, dword1C);
    case TASK_COMPLEX_LEAVE_CAR:
        return new CTaskComplexLeaveCar(ped->m_pVehicle, 0, 0, true, false);
    case TASK_COMPLEX_DESTROY_CAR_MELEE:
        // return new CTaskComplexDestroyCarMelee(m_Vehicle);
    default:
        return nullptr;
    }
}
