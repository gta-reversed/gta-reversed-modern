#include "StdInc.h"

CTaskComplexSequence* CTaskComplexSequence::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskComplexSequence*, 0x632BD0, CTaskComplexSequence*>(this);
}

void CTaskComplexSequence::AddTask(CTask* pTask)
{
    plugin::CallMethod<0x632D10, CTaskComplexSequence*, CTask*>(this, pTask);
}