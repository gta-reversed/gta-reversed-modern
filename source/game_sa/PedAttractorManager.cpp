#include "StdInc.h"

CPedAttractorManager* GetPedAttractorManager()
{
    return plugin::CallAndReturn<CPedAttractorManager*, 0x5EE190>();
}

bool CPedAttractorManager::HasEmptySlot(C2dEffect const* pEffect, CEntity const* pEntity)
{
    return plugin::CallMethodAndReturn<bool, 0x5EBB00, CPedAttractorManager*, C2dEffect const*, CEntity const*>(this, pEffect, pEntity);
}
