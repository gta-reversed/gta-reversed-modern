#include "StdInc.h"

CEventPedToFlee* CEventPedToFlee::Constructor(CPed* pPed)
{
    return plugin::CallMethodAndReturn< CEventPedToFlee*, 0x4AF240, CEventPedToFlee*, CPed*>(this, pPed);
}

CEventPedToFlee* CEventPedToFlee::Destructor()
{
    return plugin::CallMethodAndReturn< CEventPedToFlee*, 0x4AF2D0, CEventPedToFlee*>(this);
}