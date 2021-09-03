#pragma once

class CPed;
class CEventGroup;

class CCollisionEventScanner {
public:
    // IMPORTANT: This function was probably __cdecl, i.e, it does not need `this`, but the compiler
    // messed up and made the first parameter `this`, which is a boolean, is being passed in ecx a.k.a `this`.
    // We can rewrite this, but our goal is to keep our source code similar to gta_sa.exe.
    // Also, read the comment in CPedIntelligence::ProcessFirst.
    void ScanForCollisionEvents(CPed* pVictim, CEventGroup* pEventGroup);
};