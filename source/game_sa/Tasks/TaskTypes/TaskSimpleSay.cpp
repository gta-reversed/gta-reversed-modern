#include "StdInc.h"
#include "TaskSimpleSay.h"

void CTaskSimpleSay::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleSay, 0x85a1dc, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x48E360);
    RH_ScopedInstall(Destructor, 0x48E4E0);

    RH_ScopedVMTInstall(Clone, 0x48E390);
    RH_ScopedVMTInstall(GetTaskType, 0x48E420);
    RH_ScopedVMTInstall(MakeAbortable, 0x48E430);
    RH_ScopedVMTInstall(ProcessPed, 0x48E440);
}

// 0x48E360
CTaskSimpleSay::CTaskSimpleSay(uint32 sayId, int32 sayDuration) :
    m_sayDuration{sayDuration},
    m_sayId{sayId}
{
}

// 0x48E440
bool CTaskSimpleSay::ProcessPed(CPed* ped) {
    m_timer.StartIfNotAlready(m_sayDuration);
    ped->Say(m_sayId);
    return m_timer.IsOutOfTime();
}
