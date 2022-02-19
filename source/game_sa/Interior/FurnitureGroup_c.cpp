#include "StdInc.h"
#include "FurnitureGroup_c.h"

void FurnitureGroup_c::InjectHooks() {
    RH_ScopedClass(FurnitureGroup_c);
    RH_ScopedCategory("Interior");

    // Constructors (1x)
    // RH_ScopedInstall(Constructor, 0x590DE0);

    // Destructors (1x)
    // RH_ScopedInstall(Destructor, 0x590DF0);

    // Methods (6x)
    // RH_ScopedInstall(Init, 0x5910A0);
    // RH_ScopedInstall(Exit, 0x5910B0);
    // RH_ScopedInstall(AddSubGroup, 0x5910E0);
    // RH_ScopedInstall(GetFurniture, 0x591130);
    // RH_ScopedInstall(GetRandomId, 0x591170);
    // RH_ScopedInstall(AddFurniture, 0x5C0230);
}

// 0x590DE0
FurnitureGroup_c::FurnitureGroup_c() {}

// 0x590DE0
FurnitureGroup_c* FurnitureGroup_c::Constructor() {
    this->FurnitureGroup_c::FurnitureGroup_c();
    return this;
}

// 0x590DF0
FurnitureGroup_c::~FurnitureGroup_c() {}

// 0x590DF0
FurnitureGroup_c* FurnitureGroup_c::Destructor() {
    this->FurnitureGroup_c::~FurnitureGroup_c();
    return this;
}

// Methods
// 0x5910A0
int32 FurnitureGroup_c::Init() {
    return plugin::CallMethodAndReturn<int32, 0x5910A0, FurnitureGroup_c*>(this);
}

// 0x5910B0
int32 FurnitureGroup_c::Exit() {
    return plugin::CallMethodAndReturn<int32, 0x5910B0, FurnitureGroup_c*>(this);
}

// 0x5910E0
bool FurnitureGroup_c::AddSubGroup(int32 subgroupId, int32 minWidth, int32 minDepth, int32 maxWidth, int32 maxDepth, uint8 canPlaceInFrontOfWindow, uint8 isTall, uint8 canSteal) {
    return plugin::CallMethodAndReturn<bool, 0x5910E0, FurnitureGroup_c*, int32, int32, int32, int32, int32, uint8, uint8, uint8>(
        this, subgroupId, minWidth, minDepth, maxWidth, maxDepth, canPlaceInFrontOfWindow, isTall, canSteal);
}

// 0x591130
Furniture_c* FurnitureGroup_c::GetFurniture(int32 subGroupId, int16 a1, uint8 a2) {
    return plugin::CallMethodAndReturn<Furniture_c*, 0x591130, FurnitureGroup_c*, int32, int16, uint8>(this, subGroupId, a1, a2);
}

// 0x591170
int32 FurnitureGroup_c::GetRandomId(int32 a1, uint8 a2) {
    return plugin::CallMethodAndReturn<int32, 0x591170, FurnitureGroup_c*, int32, uint8>(this, a1, a2);
}

// 0x5C0230
int8_t FurnitureGroup_c::AddFurniture(int32 subgroupId, uint16 modelId, int16 id, uint8 wealthMin, uint8 wealthMax, uint8 maxAng) {
    return plugin::CallMethodAndReturn<int8_t, 0x5C0230, FurnitureGroup_c*, int32, uint16, int16, uint8, uint8, uint8>(this, subgroupId, modelId, id, wealthMin, wealthMax, maxAng);
}
