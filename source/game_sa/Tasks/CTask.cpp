/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void* CTask::operator new(unsigned int size)
{
    return CPools::ms_pTaskPool->New();
}

void CTask::operator delete(void* object)
{
    CPools::ms_pTaskPool->Delete(static_cast<CTask*>(object));
}

CTask::CTask() {
    m_pParentTask = nullptr;
}


CTask::~CTask() {
    // nothing here
}

void CTask::StopTimer(class CEvent *_event)
{
    ((void(__thiscall *)(CTask *, class CEvent *))0x421180)(this, _event);
}

bool CTask::IsGoToTask(CTask* pTask)
{
    return plugin::CallAndReturn<bool, 0x61A360, CTask*>(pTask);
    //return pTask->GetId() == TASK_SIMPLE_GO_TO_POINT|| pTask->GetId() == TASK_SIMPLE_GO_TO_POINT_FINE;
}
