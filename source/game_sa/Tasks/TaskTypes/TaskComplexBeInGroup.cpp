#include "StdInc.h"

#include "TaskComplexBeInGroup.h"

void CTaskComplexBeInGroup::InjectHooks() {
    RH_ScopedClass(CTaskComplexBeInGroup);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x632E50);
    RH_ScopedInstall(Destructor, 0x632EA0);

    //RH_ScopedInstall(MonitorMainGroupTask, 0x633010);
    //RH_ScopedInstall(MonitorSecondaryGroupTask, 0x6330B0);
    //RH_ScopedInstall(Clone_Reversed, 0x636BE0);
    RH_ScopedInstall(GetTaskType_Reversed, 0x632E90);
    //RH_ScopedInstall(MakeAbortable_Reversed, 0x632EB0);
    //RH_ScopedInstall(CreateNextSubTask_Reversed, 0x632F40);
    //RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x632FB0);
    //RH_ScopedInstall(ControlSubTask_Reversed, 0x638AA0);
}

CTaskComplexBeInGroup::CTaskComplexBeInGroup(int32 groupId, bool isLeader) :
    m_groupId{groupId},
    m_isLeader{isLeader}
{
}

// 0x633010
void CTaskComplexBeInGroup::MonitorMainGroupTask(CPed* ped) {
    return plugin::CallMethodAndReturn<void, 0x633010, CTaskComplexBeInGroup*, CPed*>(this, ped);
}

// 0x6330B0
void CTaskComplexBeInGroup::MonitorSecondaryGroupTask(CPed* ped) {
    plugin::CallMethod<0x6330B0, CTaskComplexBeInGroup*, CPed*>(this, ped);
}

CTask* CTaskComplexBeInGroup::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x636BE0, CTask*>(this);
}

bool CTaskComplexBeInGroup::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{ 
    return plugin::CallMethodAndReturn<bool, 0x632EB0, CTask*, CPed*, int32, const CEvent*>(this, ped, priority, event);
}

CTask* CTaskComplexBeInGroup::CreateNextSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x632F40, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexBeInGroup::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x632FB0, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexBeInGroup::ControlSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x638AA0, CTask*, CPed*>(this, ped);
}
