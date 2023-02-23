#include "StdInc.h"

#include "TaskSimpleDead.h"

void CTaskSimpleDead::InjectHooks() {
    RH_ScopedClass(CTaskSimpleDead);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(ProcessPed, 0x630600, { .reversed = false });
}

// NOTSA: *deathTime* originally int32
// 0x630590
CTaskSimpleDead::CTaskSimpleDead(uint32 deathTime, bool a3) : CTaskSimple() {
    m_nDeathTimeMS = deathTime;
    m_nFlags = m_nFlags & 0xF9 | (2 * (a3 & 1)) | 1; // todo: flags
}

// 0x630600
bool CTaskSimpleDead::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x630600, CTaskSimpleDead*, CPed*>(this, ped);
}
