#include "StdInc.h"

bool CInformFriendsEventQueue::Add(CEntity* pEntity, CEvent* pEvent) {
    return plugin::CallAndReturn<bool, 0x4AC1E0, CEntity*, CEvent*>(pEntity, pEvent);
}