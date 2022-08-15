#include "StdInc.h"
#include "TaskComplexDestroyCarArmed.h"

void CTaskComplexDestroyCarArmed::InjectHooks() {
    RH_ScopedClass(CTaskComplexDestroyCarArmed);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x621F50);
    RH_ScopedInstall(Destructor, 0x622010);

    // RH_ScopedInstall(CalculateSearchPositionAndRanges, 0x628C80);
    // RH_ScopedInstall(CreateSubTask, 0x628DA0);

    // RH_ScopedVirtualInstall(Clone, 0x623600);
    // RH_ScopedVirtualInstall(GetTaskType, 0x622000);
    // RH_ScopedVirtualInstall(MakeAbortable, 0x622070);
    // RH_ScopedVirtualInstall(CreateNextSubTask, 0x62DF20);
    // RH_ScopedVirtualInstall(CreateFirstSubTask, 0x62E0A0);
    // RH_ScopedVirtualInstall(ControlSubTask, 0x628FA0);
}

// 0x621F50
CTaskComplexDestroyCarArmed::CTaskComplexDestroyCarArmed(CVehicle* vehicleToDestroy, CVector posn) : // TODO: Name `posn` something more informative
    CTaskComplexDestroyCar{ vehicleToDestroy, {} },
    m_posn{posn}
{
    /* Rest done by compiler */
}

// 0x622010
CTaskComplexDestroyCarArmed::~CTaskComplexDestroyCarArmed() {
    /* Empty */
}

// 0x628C80
void CTaskComplexDestroyCarArmed::CalculateSearchPositionAndRanges(CPed* ped) {
    plugin::CallMethod<0x628C80, CTaskComplexDestroyCarArmed*, CPed*>(this, ped);
}

// 0x628DA0
void CTaskComplexDestroyCarArmed::CreateSubTask(int32 a2, CPed* ped) {
    plugin::CallMethod<0x628DA0, CTaskComplexDestroyCarArmed*, int32, CPed*>(this, a2, ped);
}

// 0x623600
CTask* CTaskComplexDestroyCarArmed::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x623600, CTaskComplexDestroyCarArmed*>(this);
}

// 0x622070
bool CTaskComplexDestroyCarArmed::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x622070, CTaskComplexDestroyCarArmed*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x62DF20
CTask* CTaskComplexDestroyCarArmed::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DF20, CTaskComplexDestroyCarArmed*, CPed*>(this, ped);
}

// 0x62E0A0
CTask* CTaskComplexDestroyCarArmed::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62E0A0, CTaskComplexDestroyCarArmed*, CPed*>(this, ped);
}

// 0x628FA0
CTask* CTaskComplexDestroyCarArmed::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x628FA0, CTaskComplexDestroyCarArmed*, CPed*>(this, ped);
}
