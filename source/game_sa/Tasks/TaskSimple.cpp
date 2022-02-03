/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "TaskSimple.h"

void CTaskSimple::InjectHooks() {
    RH_ScopedClass(CTaskSimple);
    RH_ScopedCategory("Tasks");

    RH_ScopedInstall(GetSubTask_Reversed, 0x43E300);
    RH_ScopedInstall(IsSimple_Reversed, 0x43E310);
    RH_ScopedInstall(SetPedPosition_Reversed, 0x43E320);
}

// 0x61A390
CTaskSimple::CTaskSimple() {
    m_pParentTask = nullptr;
}

// 0x43E300
CTask* CTaskSimple::GetSubTask() {
    return CTaskSimple::GetSubTask_Reversed();
}

// 0x43E310
bool CTaskSimple::IsSimple() {
    return CTaskSimple::IsSimple_Reversed();
}

// 0x43E320
bool CTaskSimple::SetPedPosition(CPed* ped) {
    return CTaskSimple::SetPedPosition_Reversed(ped);
}
