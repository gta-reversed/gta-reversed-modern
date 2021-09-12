/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

void* CTask::operator new(uint32 size) {
    return CPools::ms_pTaskPool->New();
}

void CTask::operator delete(void* object) {
    CPools::ms_pTaskPool->Delete(static_cast<CTask*>(object));
}

CTask::CTask() {
    m_pParentTask = nullptr;
}

CTask::~CTask() {
    // nothing here
}

// 0x421180
void CTask::StopTimer(const CEvent* event) {
    ((void(__thiscall*)(CTask*, const CEvent*))0x421180)(this, event);
}

// 0x61A360
bool CTask::IsGoToTask(CTask* task) {
    return plugin::CallAndReturn<bool, 0x61A360, CTask*>(task);
    // return task->GetId() == TASK_SIMPLE_GO_TO_POINT|| task->GetId() == TASK_SIMPLE_GO_TO_POINT_FINE;
}
