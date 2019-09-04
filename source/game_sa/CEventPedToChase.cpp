#include "StdInc.h"

CEventPedToChase* CEventPedToChase::Constructor(CPed* pPed)
{
    return plugin::CallMethodAndReturn< CEventPedToChase*, 0x4AF130, CEventPedToChase*, CPed*>(this, pPed);
}

CEventPedToChase* CEventPedToChase::Destructor()
{
    return plugin::CallMethodAndReturn< CEventPedToChase*, 0x4AF1C0, CEventPedToChase*>(this);
}