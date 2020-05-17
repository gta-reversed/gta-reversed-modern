#include "StdInc.h"

CEvent* CEventGroup::Add(CEvent* event, bool bValid)
{
    return plugin::CallMethodAndReturn<CEvent*, 0x4AB420, CEventGroup*, CEvent*, bool>(this, event, bValid);
}

bool CEventGroup::HasScriptCommandOfTaskType(eTaskType taskType)
{
    return plugin::CallMethodAndReturn<bool, 0x4AB840, CEventGroup*, int>(this, taskType);
}

bool CEventGroup::HasEvent(CEvent* event)
{
    return plugin::CallMethodAndReturn<bool, 0x4AB6A0, CEventGroup*, CEvent*>(this, event);
}

void CEventGroup::Flush(bool bAvoidFlushingTaskComplexBeInGroup)
{
    plugin::CallMethod<0x4AB370, CEventGroup*, bool>(this, bAvoidFlushingTaskComplexBeInGroup);
}
