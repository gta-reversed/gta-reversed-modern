#include "StdInc.h"

CGamma& gamma = *reinterpret_cast<CGamma*>(0xC92134);

void CGamma::InjectHooks() {
//    ReversibleHooks::Install("CGamma", "Init", 0x747180, &CGamma::Init);
//    ReversibleHooks::Install("CGamma", "SetGamma", 0x747200, &CGamma::SetGamma);
}

// 0x747180
void CGamma::Init() {
    plugin::Call<0x747180>();
}

// 0x747200
void CGamma::SetGamma(float arg1, bool arg2) {
    plugin::Call<0x747200>(arg1, arg2);
}
