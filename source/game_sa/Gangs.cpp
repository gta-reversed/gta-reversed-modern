#include "StdInc.h"

void CGangs::InjectHooks() {
//    ReversibleHooks::Install("CGangs", "Initialise". 0x5DE680, &CGangs::Initialise);
}

// 0x5DE680
void CGangs::Initialise() {
    plugin::Call<0x5DE680>();
}

void CGangs::Load() {
    plugin::Call<0x5D3A90>();
}
