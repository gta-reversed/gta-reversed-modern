#include "StdInc.h"

CEvent* CEventGroup::Add(CEvent& event, bool bValid)
{
    return plugin::CallMethodAndReturn<CEvent*, 0x4AB420, CEventGroup*, CEvent&, bool>(this, event, bValid);
}