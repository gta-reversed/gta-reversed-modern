#include "CTaskComplex.h"

class CTaskComplexBeInGroup : public CTaskComplex
{
    int32 m_groupId;
    bool m_isLeader;
private:
    int8 padding[3];
public:
    CPed* m_ped;
    CTask* m_mainTask;
    int32 m_mainTaskId;
    CTask* m_secondaryTask;
    int32 m_secondaryTaskSlot; // used as index in CTaskManager::m_aSecondaryTasks

    CTaskComplexBeInGroup(int32 groupId, bool isLeader);
    ~CTaskComplexBeInGroup() { }

    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_COMPLEX_BE_IN_GROUP; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

};

VALIDATE_SIZE(CTaskComplexBeInGroup, 0x28);
