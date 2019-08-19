/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void *CTask::operator new(unsigned int size)
{
    return ((CTask *(__cdecl *)(unsigned int))0x61A5A0)(size);
}

void CTask::operator delete(void *object)
{
    ((void(__cdecl *)(void *))0x61A5B0)(object);
}

CTask* CTask::DeletingDestructor(uint8_t deletingFlags)
{
    return((CTask * (__thiscall*)(CTask*, uint8_t))plugin::GetVMT(this, 0))(this, deletingFlags);
}

CTask *CTask::Clone()
{
    return ((CTask *(__thiscall *)(CTask *))plugin::GetVMT(this, 1))(this);
}

CTask *CTask::GetSubTask()
{
    return ((CTask *(__thiscall *)(CTask *))plugin::GetVMT(this, 2))(this);
}

bool CTask::IsSimple()
{
    return ((bool(__thiscall *)(CTask *))plugin::GetVMT(this, 3))(this);
}

eTaskType CTask::GetId()
{
    return ((eTaskType(__thiscall *)(CTask *))plugin::GetVMT(this, 4))(this);
}

void CTask::StopTimer(class CEvent *_event)
{
    ((void(__thiscall *)(CTask *, class CEvent *))plugin::GetVMT(this, 5))(this, _event);
}

bool CTask::MakeAbortable(class CPed *ped, eAbortPriority priority, class CEvent *_event)
{
    return ((bool(__thiscall *)(CTask *, CPed *, int, class CEvent *))plugin::GetVMT(this, 6))(this, ped, priority, _event);
}