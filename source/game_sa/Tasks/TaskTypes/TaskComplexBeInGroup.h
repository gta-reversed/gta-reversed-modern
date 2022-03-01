#pragma once

#include "TaskComplex.h"

class CTaskComplexBeInGroup : public CTaskComplex {
    int32  m_groupId{};
    bool   m_isLeader{};
    CPed*  m_ped{};
    CTask* m_mainTask{};
    int32  m_mainTaskId{TASK_NONE};
    CTask* m_secondaryTask{};
    int32  m_secondaryTaskSlot{-1}; // used as index in `CTaskManager::m_aSecondaryTasks`

public:
    static constexpr auto Type = TASK_COMPLEX_BE_IN_GROUP;

    static void InjectHooks();

    CTaskComplexBeInGroup(int32 groupId, bool isLeader);
    ~CTaskComplexBeInGroup() {}

    void MonitorMainGroupTask(CPed* ped);
    void MonitorSecondaryGroupTask(CPed* ped);

    CTask*    Clone() override { return new CTaskComplexBeInGroup{m_groupId, m_isLeader}; }
    eTaskType GetTaskType() override { return Type; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask*    CreateNextSubTask(CPed* ped) override;
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override;

private:
    // 0x632E50
    CTaskComplexBeInGroup* Constructor(int32 groupId, bool isLeader) {
        this->CTaskComplexBeInGroup::CTaskComplexBeInGroup(groupId, isLeader);
        return this;
    }

    // 0x632EA0
    CTaskComplexBeInGroup* Destructor() {
        this->CTaskComplexBeInGroup::~CTaskComplexBeInGroup();
        return this;
    }

    CTask*    Clone_Reversed() { return CTaskComplexBeInGroup::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskComplexBeInGroup::GetTaskType(); }
    bool      MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskComplexBeInGroup::MakeAbortable(ped, priority, event); }
    CTask*    CreateNextSubTask_Reversed(CPed* ped) { return CTaskComplexBeInGroup::CreateNextSubTask(ped); }
    CTask*    CreateFirstSubTask_Reversed(CPed* ped) { return CTaskComplexBeInGroup::CreateFirstSubTask(ped); }
    CTask*    ControlSubTask_Reversed(CPed* ped) { return CTaskComplexBeInGroup::ControlSubTask(ped); }
};

VALIDATE_SIZE(CTaskComplexBeInGroup, 0x28);
