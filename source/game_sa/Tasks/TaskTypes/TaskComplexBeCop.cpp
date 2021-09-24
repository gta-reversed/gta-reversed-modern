#include "StdInc.h"

#include "TaskComplexBeCop.h"

eTaskType CTaskComplexBeCop::GetTaskType()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((eTaskType(__thiscall*)(CTask*))plugin::GetVMT(this, 4))(this);
#else
    return GetId_Reversed();
#endif
}

eTaskType CTaskComplexBeCop::GetId_Reversed()
{
    return TASK_COMPLEX_BE_COP;
}