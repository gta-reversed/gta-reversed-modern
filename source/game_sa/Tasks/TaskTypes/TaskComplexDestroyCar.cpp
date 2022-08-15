#include "StdInc.h"
#include "TaskComplexDestroyCar.h"

void CTaskComplexDestroyCar::InjectHooks() {
    RH_ScopedClass(CTaskComplexDestroyCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x621C00);
    RH_ScopedInstall(Destructor, 0x621CB0);

    // RH_ScopedInstall(CreateSubTask, 0x6287A0);

    // RH_ScopedVirtualInstall(Clone, 0x623530);
    // RH_ScopedVirtualInstall(GetTaskType, 0x621C70);
    // RH_ScopedVirtualInstall(MakeAbortable, 0x621C80);
    // RH_ScopedVirtualInstall(CreateNextSubTask, 0x62D9E0);
    // RH_ScopedVirtualInstall(CreateFirstSubTask, 0x62DA90);
    // RH_ScopedVirtualInstall(ControlSubTask, 0x6288C0);
}

// 0x621C00
CTaskComplexDestroyCar::CTaskComplexDestroyCar(CVehicle* vehicleToDestroy, CVector vehPosn) :
    m_vehicleToDestroy{vehicleToDestroy},
    m_vehPosn{vehPosn}
{
    NOTASA_ASSERT(m_vehicleToDestroy);

    CEntity::SafeRegisterRef(m_vehicleToDestroy);
}

// 0x621CB0
CTaskComplexDestroyCar::~CTaskComplexDestroyCar() {
    CEntity::SafeCleanUpRef(m_vehicleToDestroy);
}

// 0x6287A0
CTask* CTaskComplexDestroyCar::CreateSubTask(eTaskType taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6287A0, CTaskComplexDestroyCar*, eTaskType, CPed*>(this, taskType, ped);
}

// 0x623530
CTask* CTaskComplexDestroyCar::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x623530, CTaskComplexDestroyCar*>(this);
}

// 0x621C80
bool CTaskComplexDestroyCar::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x621C80, CTaskComplexDestroyCar*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x62D9E0
CTask* CTaskComplexDestroyCar::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62D9E0, CTaskComplexDestroyCar*, CPed*>(this, ped);
}

// 0x62DA90
CTask* CTaskComplexDestroyCar::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DA90, CTaskComplexDestroyCar*, CPed*>(this, ped);
}

// 0x6288C0
CTask* CTaskComplexDestroyCar::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6288C0, CTaskComplexDestroyCar*, CPed*>(this, ped);
}
