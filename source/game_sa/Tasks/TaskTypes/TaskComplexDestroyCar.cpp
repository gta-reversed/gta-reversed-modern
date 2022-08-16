#include "StdInc.h"
#include "TaskComplexDestroyCar.h"
#include "TaskComplexDestroyCarArmed.h"
#include "TaskComplexDestroyCarMelee.h"
#include "TaskComplexLeaveCar.h"

void CTaskComplexDestroyCar::InjectHooks() {
    RH_ScopedClass(CTaskComplexDestroyCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x621C00);
    RH_ScopedInstall(Destructor, 0x621CB0);

    RH_ScopedInstall(CreateSubTask, 0x6287A0);

    RH_ScopedVirtualInstall2(Clone, 0x623530);
    RH_ScopedVirtualInstall2(GetTaskType, 0x621C70);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x621C80);
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x62D9E0);
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x62DA90);
    RH_ScopedVirtualInstall2(ControlSubTask, 0x6288C0, { .enabled = false, .locked = true });
}

// 0x621C00
CTaskComplexDestroyCar::CTaskComplexDestroyCar(CVehicle* vehicleToDestroy, CVector vehPosn) :
    m_vehicleToDestroy{vehicleToDestroy},
    m_vehPosn{vehPosn}
{
    NOTASA_ASSERT(m_vehicleToDestroy);

    CEntity::SafeRegisterRef(m_vehicleToDestroy);
}

CTaskComplexDestroyCar::CTaskComplexDestroyCar(const CTaskComplexDestroyCar& o) :
    CTaskComplexDestroyCar{o.m_vehicleToDestroy, o.m_vehPosn}
{
}

// 0x621CB0
CTaskComplexDestroyCar::~CTaskComplexDestroyCar() {
    CEntity::SafeCleanUpRef(m_vehicleToDestroy);
}

// 0x6287A0
CTask* CTaskComplexDestroyCar::CreateSubTask(eTaskType taskType, CPed* ped) {
    switch (taskType) {
    case TASK_COMPLEX_DESTROY_CAR_ARMED:
        return new CTaskComplexDestroyCarArmed{ m_vehicleToDestroy, m_vehPosn };
    case TASK_COMPLEX_LEAVE_CAR:
        return new CTaskComplexLeaveCar{ ped->m_pVehicle, 0, 0, true, false };
    case TASK_COMPLEX_DESTROY_CAR_MELEE:
        return new CTaskComplexDestroyCarMelee{ m_vehicleToDestroy };
    default:
        return nullptr;
    }
}

// 0x621C80
bool CTaskComplexDestroyCar::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    switch (priority) {
    case ABORT_PRIORITY_URGENT:
    case ABORT_PRIORITY_IMMEDIATE:
        return m_pSubTask->MakeAbortable(ped, priority, event);
    default:
        return false;
    }
}

// 0x62D9E0
CTask* CTaskComplexDestroyCar::CreateNextSubTask(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_BE_HIT:
    case TASK_COMPLEX_DESTROY_CAR_ARMED:
    case TASK_COMPLEX_DESTROY_CAR_MELEE:
    case TASK_COMPLEX_FALL_AND_GET_UP:
        return CreateSubTask(TASK_FINISHED, ped);
    case TASK_COMPLEX_LEAVE_CAR:
    case TASK_COMPLEX_DRAG_PED_FROM_CAR:
        return CreateSubTask(ped->GetActiveWeapon().IsTypeMelee() ? TASK_COMPLEX_DESTROY_CAR_MELEE : TASK_COMPLEX_DESTROY_CAR_ARMED, ped);
    default:
        return nullptr;
    }
}

// 0x62DA90
CTask* CTaskComplexDestroyCar::CreateFirstSubTask(CPed* ped) {
    m_arg0 = false;

    if (!m_vehicleToDestroy) {
        return CreateSubTask(TASK_FINISHED, nullptr);
    }
    if (ped->m_pVehicle && ped->bInVehicle) {
        return CreateSubTask(TASK_COMPLEX_LEAVE_CAR, ped);
    }
    if (ped->GetActiveWeapon().IsTypeMelee()) {
        return CreateSubTask(TASK_COMPLEX_DESTROY_CAR_MELEE, nullptr);
    }
    return CreateSubTask(TASK_COMPLEX_DESTROY_CAR_ARMED, nullptr);
}

// 0x6288C0
CTask* CTaskComplexDestroyCar::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6288C0, CTaskComplexDestroyCar*, CPed*>(this, ped);
}
