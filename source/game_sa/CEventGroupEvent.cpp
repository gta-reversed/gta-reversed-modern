#include "StdInc.h"

CEventGroupEvent* CEventGroupEvent::Constructor(CPed* pPed, CEvent* damageEvent)
{
    return plugin::CallMethodAndReturn<CEventGroupEvent*, 0x4ADFD0, CEventGroupEvent*, CPed*, CEvent* >(this, pPed, damageEvent);
}

void CEventGroupEvent::Destructor()
{
    return plugin::CallMethod<0x4AE070, CEventGroupEvent*>(this);
}