#include "StdInc.h"

void CEventHandler::HandleEvents()
{
    plugin::CallMethod<0x4C3F10, CEventHandler*>(this);
}

void CEventHandler::FlushImmediately()
{
    plugin::CallMethod<0x4C3820, CEventHandler*>(this);
}

bool CEventHandler::IsTemporaryEvent(CEvent* _event)
{
    return plugin::CallAndReturn<bool, 0x4BC370, CEvent*>(_event);
}