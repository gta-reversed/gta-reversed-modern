#include "StdInc.h"

bool CInformGroupEventQueue::Add(CEntity* pEntity, CPedGroup* pPedGroup, CEvent* pEvent) {
    return plugin::CallAndReturn<bool, 0x4B7CD0, CEntity*, CPedGroup*, CEvent*>(pEntity, pPedGroup, pEvent);
}