#include "StdInc.h"

void CCranes::InjectHooks() {
//    ReversibleHooks::Install("CCranes", "InitCranes", 0x6F3FC0, &CCranes::InitCranes);
//    ReversibleHooks::Install("CCranes", "UpdateCranes", 0x6F3FE0, &CCranes::UpdateCranes);
    ReversibleHooks::Install("CCranes", "IsThisCarBeingCarriedByAnyCrane", 0x6F3FF0, &CCranes::IsThisCarBeingCarriedByAnyCrane);
    ReversibleHooks::Install("CCranes", "IsThisCarBeingTargettedByAnyCrane", 0x6F4000, &CCranes::IsThisCarBeingTargettedByAnyCrane);
    ReversibleHooks::Install("CCranes", "IsThisCarPickedUp", 0x6F3FD0, &CCranes::IsThisCarPickedUp);
}

// 0x6F3FC0
void CCranes::InitCranes() {
    plugin::Call<0x6F3FC0>();
}

// 0x6F3FE0
void CCranes::UpdateCranes() {
    plugin::Call<0x6F3FE0>();
}

// 0x6F3FF0
bool CCranes::IsThisCarBeingCarriedByAnyCrane() { return false; }

// 0x6F4000
bool CCranes::IsThisCarBeingTargettedByAnyCrane() { return false; }

// 0x6F3FD0
bool CCranes::IsThisCarPickedUp() { return false; }
