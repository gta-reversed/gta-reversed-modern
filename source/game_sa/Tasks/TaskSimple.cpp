/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CTaskSimple::InjectHooks()
{

}

CTaskSimple::CTaskSimple() {
    m_pParentTask = nullptr;
}

CTaskSimple::~CTaskSimple() {
    // nothing here
}

CTask* CTaskSimple::GetSubTask() {
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((CTask * (__thiscall*)(CTaskSimple*))0x43E300)(this);
#else
    return CTaskSimple::GetSubTask_Reversed();
#endif
}

bool CTaskSimple::IsSimple() {
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((bool(__thiscall*)(CTaskSimple*))0x43E310)(this);
#else
    return CTaskSimple::IsSimple_Reversed();
#endif
}

bool CTaskSimple::SetPedPosition(class CPed *ped) {
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((bool(__thiscall *)(CTaskSimple *, class CPed *))0x43E320)(this, ped);
#else
    return CTaskSimple::SetPedPosition_Reversed(ped);
#endif
}