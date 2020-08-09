#include "StdInc.h"

void CEventHandler::HandleEvents()
{
    plugin::CallMethod<0x4C3F10, CEventHandler*>(this);
}

void CEventHandler::FlushImmediately()
{
    plugin::CallMethod<0x4C3820, CEventHandler*>(this);
}

eEventType CEventHandler::GetCurrentEventType()
{
    return plugin::CallMethodAndReturn<eEventType, 0x4B8CC0, CEventHandler*>(this);
}

bool CEventHandler::IsTemporaryEvent(CEvent* _event)
{
    return plugin::CallAndReturn<bool, 0x4BC370, CEvent*>(_event);
}
