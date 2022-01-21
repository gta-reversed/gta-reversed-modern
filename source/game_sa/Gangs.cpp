#include "StdInc.h"

#include "Gangs.h"

void CGangs::InjectHooks() {
    // ReversibleHooks::Install("CGangs", "Initialise", 0x5DE680, &CGangs::Initialise);
    // ReversibleHooks::Install("CGangs", "Load", 0x5D3A90, &CGangs::Load);
    // ReversibleHooks::Install("CGangs", "Save", 0x5D3A60, &CGangs::Save);
}

// 0x5DE680
void CGangs::Initialise() {
    plugin::Call<0x5DE680>();
}

// 0x5D3A90
bool CGangs::Load() {
    return plugin::CallAndReturn<bool, 0x5D3A90>();
}

// 0x5D3A60
bool CGangs::Save() {
    return plugin::CallAndReturn<bool, 0x5D3A60>();
}
