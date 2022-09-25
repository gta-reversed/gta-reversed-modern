#include "StdInc.h"

#include "Gamma.h"

CGamma& gamma = *(CGamma*)0xC92134;

void CGamma::InjectHooks() {
    RH_ScopedClass(CGamma);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x747180, { .reversed = false });
    RH_ScopedInstall(SetGamma, 0x747200, { .reversed = false });
}

// 0x747180
void CGamma::Init() {
    plugin::CallMethod<0x747180, CGamma*>(this);
}

// 0x747200
void CGamma::SetGamma(float arg1, bool arg2) {
    plugin::CallMethod<0x747200, CGamma*>(this, arg1, arg2);
}
