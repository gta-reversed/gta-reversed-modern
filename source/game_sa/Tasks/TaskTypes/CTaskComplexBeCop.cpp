#include "StdInc.h"

eTaskType CTaskComplexBeCop::GetId()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((eTaskType(__thiscall*)(CTask*))plugin::GetVMT(this, 4))(this);
#else
    return TASK_COMPLEX_BE_COP;
#endif
}