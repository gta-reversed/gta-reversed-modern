#include "StdInc.h"

#include "TaskSimpleWaitUntilAreaCodesMatch.h"
#include "EntryExitManager.h"

void CTaskSimpleWaitUntilAreaCodesMatch::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleWaitUntilAreaCodesMatch, 0x86e544, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x635540);
    RH_ScopedInstall(Destructor, 0x6355E0);
    RH_ScopedVMTInstall(MakeAbortable, 0x6355D0);
    RH_ScopedVMTInstall(ProcessPed, 0x635640);
}

// 0x635540
CTaskSimpleWaitUntilAreaCodesMatch::CTaskSimpleWaitUntilAreaCodesMatch(CPed* targetPed) :
    CTaskSimpleStandStill(1000, true, false, 8.f),
    m_TargetPed{ targetPed }
{
    CEntity::SafeRegisterRef(m_TargetPed);
}

// 0x6355E0
CTaskSimpleWaitUntilAreaCodesMatch::~CTaskSimpleWaitUntilAreaCodesMatch() {
    CEntity::SafeCleanUpRef(m_TargetPed);
}

// 0x635640
bool CTaskSimpleWaitUntilAreaCodesMatch::ProcessPed(CPed* ped) {
    if (!m_TargetPed) {
        return true;
    }

    if (CEntryExitManager::ms_exitEnterState != EXIT_ENTER_STATE_0) {
        if (m_TargetPed->m_nAreaCode == ped->m_nAreaCode) {
            return true;
        }
    }

    return !ped->bInVehicle && CTaskSimpleStandStill::ProcessPed(ped);
}
