/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CTaskManager::InjectHooks()
{
    CTaskSimple::InjectHooks();
}

// Converted from thiscall void CTaskManager::CTaskManager(CPed *ped) 0x6816A0
CTaskManager::CTaskManager(CPed* ped) {
    ((void(__thiscall *)(CTaskManager*, CPed*))0x6816A0)(this, ped);
}

// Converted from thiscall void CTaskManager::~CTaskManager() 0x6816D0
CTaskManager::~CTaskManager() {
    ((void(__thiscall *)(CTaskManager*))0x6816D0)(this);
}

// Converted from thiscall CTask* CTaskManager::GetActiveTask(void) 0x681720
CTask* CTaskManager::GetActiveTask() {
    return ((CTask* (__thiscall *)(CTaskManager*))0x681720)(this);
}

// Converted from thiscall CTask* CTaskManager::FindActiveTaskByType(int taskType) 0x681740
CTask* CTaskManager::FindActiveTaskByType(int taskType) {
    return ((CTask* (__thiscall *)(CTaskManager*, int))0x681740)(this, taskType);
}

// Converted from thiscall CTask* CTaskManager::FindTaskByType(int taskIndex,int taskType) 0x6817D0
CTask* CTaskManager::FindTaskByType(int taskIndex, int taskType) {
    return ((CTask* (__thiscall *)(CTaskManager*, int, int))0x6817D0)(this, taskIndex, taskType);
}

// Converted from thiscall CTask* CTaskManager::GetTaskSecondary(int taskIndex) 0x681810
CTask* CTaskManager::GetTaskSecondary(int taskIndex) {
    return ((CTask* (__thiscall *)(CTaskManager*, int))0x681810)(this, taskIndex);
}

// Converted from thiscall bool CTaskManager::HasTaskSecondary(CTask const*task) 0x681820
bool CTaskManager::HasTaskSecondary(CTask const* task) {
    return ((bool(__thiscall *)(CTaskManager*, CTask const*))0x681820)(this, task);
}

// Converted from thiscall void CTaskManager::Flush(void) 0x681850
void CTaskManager::Flush() {
    ((void(__thiscall *)(CTaskManager*))0x681850)(this);
}

// Converted from thiscall void CTaskManager::FlushImmediately(void) 0x6818A0
void CTaskManager::FlushImmediately() {
    ((void(__thiscall *)(CTaskManager*))0x6818A0)(this);
}

// Converted from thiscall void CTaskManager::SetNextSubTask(CTask *task) 0x681920
void CTaskManager::SetNextSubTask(CTask* task) {
    ((void(__thiscall *)(CTaskManager*, CTask*))0x681920)(this, task);
}

// Converted from thiscall CTask* CTaskManager::GetSimplestTask(CTask *task) 0x681970
CTask* CTaskManager::GetSimplestTask(CTask* task) {
    return ((CTask* (__cdecl *)(CTask*))0x681970)(task);
}

// Converted from thiscall void CTaskManager::StopTimers(CEvent const*_event) 0x6819A0
void CTaskManager::StopTimers(CEvent const* _event) {
    ((void(__thiscall *)(CTaskManager*, CEvent const*))0x6819A0)(this, _event);
}

// Converted from thiscall CTask* CTaskManager::GetSimplestActiveTask(void) 0x6819D0
CTask* CTaskManager::GetSimplestActiveTask() {
    return ((CTask* (__thiscall *)(CTaskManager*))0x6819D0)(this);
}

// Converted from thiscall CTask* CTaskManager::GetSimplestTask(int taskIndex) 0x681A00
CTask* CTaskManager::GetSimplestTask(int taskIndex) {
    return ((CTask* (__thiscall *)(CTaskManager*, int))0x681A00)(this, taskIndex);
}

// Converted from thiscall void CTaskManager::AddSubTasks(CTask *task) 0x681A30
void CTaskManager::AddSubTasks(CTask* task) {
    ((void(__thiscall *)(CTaskManager*, CTask*))0x681A30)(this, task);
}

// Converted from thiscall void CTaskManager::ParentsControlChildren(CTask *task) 0x681A80
void CTaskManager::ParentsControlChildren(CTask* task) {
    ((void(__thiscall *)(CTaskManager*, CTask*))0x681A80)(this, task);
}

// Converted from thiscall void CTaskManager::SetTask(CTask *task,int taskIndex,bool) 0x681AF0
void CTaskManager::SetTask(CTask* task, int taskIndex, bool arg2) {
    ((void(__thiscall *)(CTaskManager*, CTask*, int, bool))0x681AF0)(this, task, taskIndex, arg2);
}

// Converted from thiscall void CTaskManager::SetTaskSecondary(CTask *task,int taskIndex) 0x681B60
void CTaskManager::SetTaskSecondary(CTask* task, int taskIndex) {
    ((void(__thiscall *)(CTaskManager*, CTask*, int))0x681B60)(this, task, taskIndex);
}

// Converted from thiscall void CTaskManager::ClearTaskEventResponse(void) 0x681BD0
void CTaskManager::ClearTaskEventResponse() {
    ((void(__thiscall *)(CTaskManager*))0x681BD0)(this);
}

// Converted from thiscall void CTaskManager::ManageTasks(void) 0x681C10
void CTaskManager::ManageTasks() {
    ((void(__thiscall *)(CTaskManager*))0x681C10)(this);
}