#include "StdInc.h"

#include "FxSystemBP_c.h"

void FxSystemBP_c::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("FxSystemBP_c", "operator new", 0x4AA100, &FxSystemBP_c::operator new);
    // Install("FxSystemBP_c", "FxSystemBP_c", 0x4AA0D0, &FxSystemBP_c::Constructor);
    // Install("FxSystemBP_c", "~FxSystemBP_c", 0x4AA0F0, &FxSystemBP_c::Destructor);
    // Install("FxSystemBP_c", "Load", 0x5C05F0, &FxSystemBP_c::Load);
    // Install("FxSystemBP_c", "Unload", 0x4AA120, &FxSystemBP_c::Unload);
    // Install("FxSystemBP_c", "Update", 0x4AA130, &FxSystemBP_c::Update);
    // Install("FxSystemBP_c", "Render", 0x4AA160, &FxSystemBP_c::Render);
    // Install("FxSystemBP_c", "FreePrtFromSystem", 0x4AA1B0, &FxSystemBP_c::FreePrtFromSystem);
    // Install("FxSystemBP_c", "GetBoundingSphere", 0x4AA1F0, &FxSystemBP_c::GetBoundingSphere);
    // Install("FxSystemBP_c", "SetBoundingSphere", 0x4AA200, &FxSystemBP_c::SetBoundingSphere);
}

// 0x4AA100
void* FxSystemBP_c::operator new(uint32 size) {
    return plugin::CallAndReturn<void*, 0x4AA100, uint32>(size);
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
