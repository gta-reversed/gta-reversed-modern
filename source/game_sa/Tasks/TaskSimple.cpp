/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "TaskSimple.h"

// 0x61A390
CTaskSimple::CTaskSimple() {
    m_pParentTask = nullptr;
}

// 0x43E300
CTask* CTaskSimple::GetSubTask() {
    return nullptr;
}

// 0x43E310
bool CTaskSimple::IsSimple() {
    return true;
}

// 0x43E320
bool CTaskSimple::SetPedPosition(CPed* ped) {
    return false;
}
