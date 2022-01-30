#include "StdInc.h"

#include "TaskComplexBeCop.h"

eTaskType CTaskComplexBeCop::GetTaskType()
{
    return GetId_Reversed();
}

eTaskType CTaskComplexBeCop::GetId_Reversed()
{
    return TASK_COMPLEX_BE_COP;
}