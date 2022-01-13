#include "StdInc.h"

void CGangs::InjectHooks() {
//    ReversibleHooks::Install("CGangs", "Initialise". 0x5DE680, &CGangs::Initialise);
}

// 0x5DE680
void CGangs::Initialise() {
    plugin::Call<0x5DE680>();
}

bool CGangs::Load() {
    return plugin::CallAndReturn<bool, 0x5D3A90>();
}

bool CGangs::Save() {
    return plugin::CallAndReturn<bool, 0x5D3A60>();
}
