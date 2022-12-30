#pragma once

#include "TaskAllocator.h"

class CTaskAllocatorKillThreatsBasic : public CTaskAllocator {
public:
    explicit CTaskAllocatorKillThreatsBasic(CPed* ped);
    ~CTaskAllocatorKillThreatsBasic() override;

    eTaskAllocatorType GetType() override { return TASK_ALLOCATOR_KILL_THREATS_BASIC; }; // 0x69C2C0
    void AllocateTasks(CPedGroupIntelligence* intel) override;
    void ProcessGroup(CPedGroupIntelligence* intel) override;
    void ComputeClosestPeds(CPedGroup& group1, CPedGroup& group2, CPed** peds);
};
