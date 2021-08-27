/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

CTaskComplex::CTaskComplex() {
    m_pSubTask = nullptr;
}

CTaskComplex::~CTaskComplex() {
    if (m_pSubTask)
        delete m_pSubTask;
    m_pSubTask = nullptr;
}

CTaskComplex* CTaskComplex::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskComplex*, 0x61A3B0, CTaskComplex*>(this);
}

CTask* CTaskComplex::GetSubTask() {
    return ((CTask * (__thiscall*)(CTask*))0x421190)(this);
}

// 0x4211A0
bool CTaskComplex::IsSimple() {
    return CTaskComplex::IsSimple_Reversed();
}

// 0x4211B0
bool CTaskComplex::MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) {
    return CTaskComplex::MakeAbortable_Reversed(ped, priority, event);
}

void CTaskComplex::SetSubTask(CTask* subTask){
    ((void(__thiscall*)(CTaskComplex*, CTask*))0x61A430)(this, subTask);
}

bool CTaskComplex::MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event) {
    return m_pSubTask->MakeAbortable(ped, priority, event);
}