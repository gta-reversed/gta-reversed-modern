#include "StdInc.h"

#include "CollisionEventScanner.h"

void CCollisionEventScanner::ScanForCollisionEvents(CPed* victim, CEventGroup* eventGroup)
{
    plugin::CallMethod<0x604500, CCollisionEventScanner*, CPed*, CEventGroup*>(this, victim, eventGroup);
}
