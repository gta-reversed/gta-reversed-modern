#include "StdInc.h"

#include "TaskComplexBeInGroup.h"

void CTaskComplexBeInGroup::InjectHooks() {
    RH_ScopedClass(CTaskComplexBeInGroup);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x632E50);
    RH_ScopedInstall(Destructor, 0x632EA0);

    RH_ScopedInstall(MonitorMainGroupTask, 0x633010);
    RH_ScopedInstall(MonitorSecondaryGroupTask, 0x6330B0);
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
    if (const auto groupMainTask = CPedGroups::GetGroup(m_groupId).GetIntelligence().GetTaskMain(ped)) {
        if (groupMainTask != m_mainTask || groupMainTask->GetTaskType() != m_mainTaskId) {
            if (groupMainTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
                m_mainTask = groupMainTask;
                m_mainTaskId = groupMainTask->GetTaskType();
            }
        }
    } else if (m_mainTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
        m_mainTask = nullptr;
        m_mainTaskId = TASK_NONE;
    }
}

// 0x6330B0
void CTaskComplexBeInGroup::MonitorSecondaryGroupTask(CPed* ped) {
    // Check if ped has finished the group task (if any)
    auto& groupIntel = CPedGroups::GetGroup(m_groupId).GetIntelligence();
    const auto grpSecTask = groupIntel.GetTaskSecondary(ped);
    const auto pedGrpSecTaskSlot = groupIntel.GetTaskSecondarySlot(ped);
    const auto pedGrpSecTask = ped->GetTaskManager().GetTaskSecondary(pedGrpSecTaskSlot);
    if (m_secondaryTask == grpSecTask) {
        if (m_secondaryTask) { // Check if theres any task at all (Not both nullptr)
            // Check if ped has finished the task
            if (!pedGrpSecTask) {
                groupIntel.ReportFinishedTask(ped, m_secondaryTask);
                m_secondaryTask = nullptr;
                m_secondaryTaskSlot = -1;
            }
        }
    } else { // Group has a new task, apply it to the ped

        // Abort peds task in the previous stored slot
        if (const auto task = ped->GetTaskManager().GetTaskSecondary(m_secondaryTaskSlot)) {
            task->MakeAbortable(ped, ABORT_PRIORITY_LEISURE, nullptr);
        }

        // Make sure ped has the task the new task (and abort current)
        if (!pedGrpSecTask || pedGrpSecTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
            m_secondaryTask = grpSecTask;
            m_secondaryTaskSlot = pedGrpSecTaskSlot;
            if (grpSecTask) { 
                ped->GetTaskManager().SetTaskSecondary(grpSecTask->Clone(), pedGrpSecTaskSlot);
            }
        }
    }
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
