#include "StdInc.h"

#include "FxSystemBP.h"

void FxSystemBP_c::InjectHooks() {
    RH_ScopedClass(FxSystemBP_c);
    RH_ScopedCategory("Fx");

    using namespace ReversibleHooks;
    // Install("FxSystemBP_c", "operator new", 0x4AA100, &FxSystemBP_c::operator new);
    RH_ScopedInstall(Constructor, 0x4AA0D0, { .reversed = false });
    RH_ScopedInstall(Destructor, 0x4AA0F0, { .reversed = false });
    RH_ScopedInstall(Load, 0x5C05F0, { .reversed = false });
    RH_ScopedInstall(Unload, 0x4AA120, { .reversed = false });
    RH_ScopedInstall(Update, 0x4AA130, { .reversed = false });
    RH_ScopedInstall(Render, 0x4AA160, { .reversed = false });
    RH_ScopedInstall(FreePrtFromSystem, 0x4AA1B0, { .reversed = false });
    RH_ScopedInstall(GetBoundingSphere, 0x4AA1F0, { .reversed = false });
    RH_ScopedInstall(SetBoundingSphere, 0x4AA200, { .reversed = false });
}

// 0x4AA100
void* FxSystemBP_c::operator new(unsigned size) {
    return g_fxMan.m_pool.GetMem(size, 4);;
}

// 0x4AA0D0
FxSystemBP_c::FxSystemBP_c() {
    plugin::CallMethod<0x4AA0D0, FxSystemBP_c*>(this);
}

// 0x4AA0F0
FxSystemBP_c::~FxSystemBP_c() {
    plugin::CallMethod<0x4AA0F0, FxSystemBP_c*>(this);
}

FxSystemBP_c* FxSystemBP_c::Constructor() {
    this->FxSystemBP_c::FxSystemBP_c();
    return this;
}

FxSystemBP_c* FxSystemBP_c::Destructor() {
    this->FxSystemBP_c::~FxSystemBP_c();
    return this;
}

// int32 file -> FILESTREAM?
// 0x5C05F0
void FxSystemBP_c::Load(char* filename, int32 file, int32 version) {
    plugin::CallMethod<0x5C05F0, FxSystemBP_c*, char*, int32, int32>(this, filename, file, version);
}

// 0x4AA120
void FxSystemBP_c::Unload() {
    plugin::CallMethod<0x4AA120, FxSystemBP_c*>(this);
}

// 0x4AA130
void FxSystemBP_c::Update(float arg0) {
    plugin::CallMethod<0x4AA130, FxSystemBP_c*, float>(this, arg0);
}

// 0x4AA160
void FxSystemBP_c::Render(RwCamera* camera, float dayNightBalance, bool bHeatHaze) {
    plugin::CallMethod<0x4AA160, FxSystemBP_c*, RwCamera*, float, bool>(this, camera, dayNightBalance, bHeatHaze);
}

// 0x4AA1B0
bool FxSystemBP_c::FreePrtFromSystem(FxSystem_c* system) {
    return plugin::CallMethodAndReturn<bool, 0x4AA1B0, FxSystemBP_c*, FxSystem_c*>(this, system);
}

// 0x4AA1F0
FxSphere_c* FxSystemBP_c::GetBoundingSphere() {
    return plugin::CallMethodAndReturn<FxSphere_c*, 0x4AA1F0, FxSystemBP_c*>(this);
}

// 0x4AA200
void FxSystemBP_c::SetBoundingSphere(RwV3d* center, float radius) {
    plugin::CallMethod<0x4AA200, FxSystemBP_c*, RwV3d*, float>(this, center, radius);
}
