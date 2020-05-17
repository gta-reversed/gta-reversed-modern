#pragma once
#include "CTaskComplexSequence.h"

class CTaskSequences
{
public:
    static std::int32_t& ms_iActiveSequence;
    static CTaskComplexSequence* ms_taskSequence;
    static inline void AddTaskToActiveSequence(CTask* task)
    {
        ms_taskSequence[ms_iActiveSequence].AddTask(task);
    }
};
