/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "TaskComplex.h"

// 0x61A3B0
CTaskComplex::CTaskComplex() : CTask() {
    m_pSubTask = nullptr;
}

// 0x61A3D0
CTaskComplex::~CTaskComplex() {
    delete m_pSubTask;
    m_pSubTask = nullptr;
}

// 0x421190
CTask* CTaskComplex::GetSubTask() {
    return m_pSubTask;
}

// 0x4211A0
bool CTaskComplex::IsSimple() {
    return false;
}

// 0x4211B0
bool CTaskComplex::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

// 0x61A430
void CTaskComplex::SetSubTask(CTask* subTask) {
    if (m_pSubTask == subTask) {
        return;
    }
    delete m_pSubTask;
    m_pSubTask = subTask;
    if (subTask) {
        subTask->m_pParentTask = this;
    }
}
