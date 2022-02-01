#include "StdInc.h"

#include "CollisionEventScanner.h"

// IMPORTANT: This function was probably __cdecl, i.e, it does not need `this`, but the compiler
// messed up and made the first parameter `this`, which is a boolean, is being passed as in ecx a.k.a `this`.
// We can rewrite this, but our goal is to keep our source code similar to gta_sa.exe.
// Also, read the comment in CPedIntelligence::ProcessFirst.
void CCollisionEventScanner::ScanForCollisionEvents(CPed* pVictim, CEventGroup* pEventGroup)
{
    plugin::CallMethod<0x604500, CCollisionEventScanner*, CPed*, CEventGroup*>(this, pVictim, pEventGroup);
}
