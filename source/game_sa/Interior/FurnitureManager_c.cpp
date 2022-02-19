#include "StdInc.h"
#include "FurnitureManager_c.h"

void FurnitureManager_c::InjectHooks() {
    RH_ScopedClass(FurnitureManager_c);
    RH_ScopedCategory("Interior");

    // Constructors (1x)
    // RH_ScopedInstall(Constructor, 0x591260);

    // Destructors (1x)
    // RH_ScopedInstall(Destructor, 0x5912E0);

    // Static functions (2x)
    // RH_ScopedGlobalInstall(GetGroupId, 0x5BFB40);
    // RH_ScopedGlobalInstall(GetSubGroupId, 0x5BFBF0);

    // Methods (5x)
    // RH_ScopedInstall(Exit, 0x5911A0);
    // RH_ScopedInstall(GetFurniture, 0x5911E0);
    // RH_ScopedInstall(GetRandomId, 0x591220);
    // RH_ScopedInstall(LoadFurniture, 0x5C0280);
    // RH_ScopedInstall(Init, 0x5C04A0);
}

// 0x591260
FurnitureManager_c::FurnitureManager_c() {}

// 0x591260
FurnitureManager_c* FurnitureManager_c::Constructor() {
    this->FurnitureManager_c::FurnitureManager_c();
    return this;
}

// 0x5912E0
FurnitureManager_c::~FurnitureManager_c() {}

// 0x5912E0
FurnitureManager_c* FurnitureManager_c::Destructor() {
    this->FurnitureManager_c::~FurnitureManager_c();
    return this;
}

// Static functions
// 0x5BFB40
int32 FurnitureManager_c::GetGroupId(const char* name) {
    return plugin::CallAndReturn<int32, 0x5BFB40, const char*>(name);
}

// 0x5BFBF0
int32 FurnitureManager_c::GetSubGroupId(const char* name) {
    return plugin::CallAndReturn<int32, 0x5BFBF0, const char*>(name);
}

// Methods
// 0x5911A0
void FurnitureManager_c::Exit() {
    plugin::CallMethod<0x5911A0, FurnitureManager_c*>(this);
}

// 0x5911E0
Furniture_c* FurnitureManager_c::GetFurniture(int32 furnitureGroupId, int32 furnitureSubgroupId, int16 id, uint8 wealth) {
    return plugin::CallMethodAndReturn<Furniture_c*, 0x5911E0, FurnitureManager_c*, int32, int32, int16, uint8>(this, furnitureGroupId, furnitureSubgroupId, id, wealth);
}

// 0x591220
int32 FurnitureManager_c::GetRandomId(int32 groupId, int32 a3, uint8 a4) {
    return plugin::CallMethodAndReturn<int32, 0x591220, FurnitureManager_c*, int32, int32, uint8>(this, groupId, a3, a4);
}

// 0x5C0280
void FurnitureManager_c::LoadFurniture() {
    plugin::CallMethod<0x5C0280, FurnitureManager_c*>(this);
}

// 0x5C04A0
void FurnitureManager_c::Init() {
    plugin::CallMethod<0x5C04A0, FurnitureManager_c*>(this);
}
