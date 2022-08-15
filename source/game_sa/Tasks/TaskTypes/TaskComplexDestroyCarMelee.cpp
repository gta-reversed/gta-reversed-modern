#include "StdInc.h"
#include "TaskComplexDestroyCarMelee.h"

void CTaskComplexDestroyCarMelee::InjectHooks() {
    RH_ScopedClass(CTaskComplexDestroyCarMelee);
    RH_ScopedCategory("Tasks/TaskTypes");

    // RH_ScopedInstall(Constructor, 0x621D10);

    // RH_ScopedInstall(Destructor, 0x621DA0);

    // RH_ScopedInstall(CalculateSearchPositionAndRanges, 0x6289F0);
    // RH_ScopedInstall(CreateSubTask, 0x628A70);

    // RH_ScopedVirtualInstall(Clone, 0x6235A0);
    // RH_ScopedVirtualInstall(GetTaskType, 0x621D90);
    // RH_ScopedVirtualInstall(MakeAbortable, 0x621E00);
    // RH_ScopedVirtualInstall(CreateNextSubTask, 0x62DC20);
    // RH_ScopedVirtualInstall(CreateFirstSubTask, 0x62DB20);
    // RH_ScopedVirtualInstall(ControlSubTask, 0x62DDB0);
}

// 0x621D10
CTaskComplexDestroyCarMelee::CTaskComplexDestroyCarMelee(CVehicle* vehToDestroy) :
    CTaskComplexDestroyCar{vehToDestroy, {}}
{
    /* NOP */
}

// 0x621DA0
CTaskComplexDestroyCarMelee::~CTaskComplexDestroyCarMelee() {}

// 0x6289F0
void CTaskComplexDestroyCarMelee::CalculateSearchPositionAndRanges(CPed* ped) {
    return plugin::CallMethodAndReturn<void, 0x6289F0, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);
}

// 0x628A70
CTask* CTaskComplexDestroyCarMelee::CreateSubTask(eTaskType taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x628A70, CTaskComplexDestroyCarMelee*, eTaskType, CPed*>(this, taskType, ped);
}

// 0x6235A0
CTask* CTaskComplexDestroyCarMelee::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6235A0, CTaskComplexDestroyCarMelee*>(this);
}

// 0x621E00
bool CTaskComplexDestroyCarMelee::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x621E00, CTaskComplexDestroyCarMelee*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x62DC20
CTask* CTaskComplexDestroyCarMelee::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DC20, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);
}

// 0x62DB20
CTask* CTaskComplexDestroyCarMelee::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DB20, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);
}

// 0x62DDB0
CTask* CTaskComplexDestroyCarMelee::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DDB0, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);
}
