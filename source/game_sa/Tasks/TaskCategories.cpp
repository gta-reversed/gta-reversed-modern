#include "StdInc.h"
#include "TaskCategories.h"

// 0x698680
int8 CTaskCategories::ComputeTaskCategory(const CTask* task) {
    int8 category = task != nullptr;

    // todo: FIX_BUGS?
    auto type = const_cast<CTask*>(task)->GetTaskType();
    if (type >= TASK_SIMPLE_FIGHT_CTRL && type <= TASK_SIMPLE_THROW_CTRL)
        category = 4;

    if (type >= TASK_SIMPLE_FIGHT_CTRL && type <= TASK_SIMPLE_THROW_CTRL)
        category = 2;

    if (type < TASK_SIMPLE_FIGHT_CTRL)
        return category;

    if (type <= TASK_SIMPLE_THROW_CTRL)
        return 4;

    return category;
}

void CTaskCategories::IsFleePedTask(const CTask* task, bool& a2, bool& a3) {
    // unused
}

// 0x698610
void CTaskCategories::IsFollowPedTask(const CTask* task, bool& a2, bool& a3) {
    a2 = false;
    a3 = false;
}

// 0x6985E0
void CTaskCategories::IsKillPedTask(const CTask* task, bool& a2, bool& a3) {
    a2 = false;
    a3 = false;
    auto type = const_cast<CTask*>(task)->GetTaskType();
    if (type >= TASK_SIMPLE_FIGHT_CTRL && type <= TASK_SIMPLE_THROW_CTRL)
        a2 = true;
}
