#pragma once

class CTaskCategories {
public:
    static int8 ComputeTaskCategory(const CTask* task);
    static void IsFleePedTask(const CTask* task, bool& a2, bool& a3);
    static void IsFollowPedTask(const CTask* task, bool& a2, bool& a3);
    static void IsKillPedTask(const CTask* task, bool& a2, bool& a3);
};
