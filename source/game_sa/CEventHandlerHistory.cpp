#include "StdInc.h"

void CEventHandlerHistory::ClearAllEvents()
{
    plugin::CallMethod<0x4BC550, CEventHandlerHistory*>(this);
}