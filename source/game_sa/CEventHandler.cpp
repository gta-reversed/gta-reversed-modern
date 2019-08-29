#include "StdInc.h"

void CEventHandler::HandleEvents()
{
    plugin::CallMethod<0x4C3F10, CEventHandler*>(this);
}

void CEventHandler::FlushImmediately()
{
    plugin::CallMethod<0x4C3820, CEventHandler*>(this);
}