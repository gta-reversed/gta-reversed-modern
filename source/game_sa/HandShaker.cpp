#include "StdInc.h"

#include "HandShaker.h"

CHandShaker*& gHandShaker = *(CHandShaker**)0xB6ECA0;

void CHandShaker::InjectHooks() {
    RH_ScopedClass(CHandShaker);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(SetDefaults, 0x517330);
    RH_ScopedInstall(Reset, 0x50D860);
    RH_ScopedInstall(Process, 0x50D930, { .reversed = false });
}

// 0x517330
void CHandShaker::SetDefaults() {
    vec1.Set(0.02f, 0.02f, 0.01f);
    vec2.Set(0.0002f, 0.0002f, 0.0001f);
    vec4.Set(1.3f, 1.3f, 1.4f);

    f84 = 0.3f;
    f88 = 1.0f;
    n8C = 20;
    f90 = 0.001f;

    Reset();
}

// 0x50D860
void CHandShaker::Reset() {
    vec = CVector();
    vec3 = CVector{
        CGeneral::GetRandomNumberInRange(0.0f, vec2.x),
        CGeneral::GetRandomNumberInRange(0.0f, vec2.y),
        CGeneral::GetRandomNumberInRange(0.0f, vec2.z),
    };
}

// 0x50D930
void CHandShaker::Process(float a1) {
    plugin::CallMethod<0x50D930, CHandShaker*, float>(this, a1);
}
