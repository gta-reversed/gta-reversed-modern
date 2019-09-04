#include "StdInc.h"

CTaskComplexWander* CTaskComplexWander::GetWanderTaskByPedType(CPed* pPed)
{
    return plugin::CallAndReturn<CTaskComplexWander*, 0x673D00, CPed*>(pPed);
}

CTask* CTaskComplexWander::CreateNextSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x674140, CTaskComplexWander*, CPed*>(this, ped);
}

CTask* CTaskComplexWander::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x6740E0, CTaskComplexWander*, CPed*>(this, ped);
}

CTask* CTaskComplexWander::ControlSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x674C30, CTaskComplexWander*, CPed*>(this, ped);
}

int CTaskComplexWander::GetWanderType()
{
    return ((int(__thiscall*)(CTaskComplex*))plugin::GetVMT(this, 11))(this);
}

void CTaskComplexWander::ScanForStuff(CPed* ped)
{
    return ((void(__thiscall*)(CTaskComplex*, CPed*))plugin::GetVMT(this, 12))(this, ped);
}

void CTaskComplexWander::UpdateDir(CPed* pPed)
{
    return ((void(__thiscall*)(CTaskComplex*, CPed*))plugin::GetVMT(this, 13))(this, pPed);
}

void CTaskComplexWander::UpdatePathNodes(CPed* pPed, int8_t dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8_t* outDir)
{
    return ((void(__thiscall*)(CTaskComplex*, CPed*, int8_t, CNodeAddress*, CNodeAddress*, int8_t*))plugin::GetVMT(this, 14))
        (this, pPed, dir, originNode, targetNode, outDir);
}