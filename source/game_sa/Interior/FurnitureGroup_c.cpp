#include "StdInc.h"
#include "FurnitureGroup_c.h"
#include "FurnitureManager_c.h"

void FurnitureGroup_c::InjectHooks() {
    RH_ScopedClass(FurnitureGroup_c);
    RH_ScopedCategory("Interior");

    RH_ScopedInstall(Init, 0x5910A0);
    RH_ScopedInstall(Exit, 0x5910B0);
    RH_ScopedInstall(AddSubGroup, 0x5910E0);
    RH_ScopedInstall(GetFurniture, 0x591130);
    RH_ScopedInstall(GetRandomId, 0x591170);
    RH_ScopedInstall(AddFurniture, 0x5C0230);
}

// 0x5910A0
int32 FurnitureGroup_c::Init() {
    return 1;
}

// 0x5910B0
void FurnitureGroup_c::Exit() {
    rng::for_each(m_subGroupsList, &FurnitureSubGroup_c::Exit);
    m_subGroupsList.RemoveAll();
}

// 0x5910E0
bool FurnitureGroup_c::AddSubGroup(int32 subGroupId, int32 minWidth, int32 minDepth, int32 maxWidth, int32 maxDepth, uint8 canPlaceInFrontOfWindow, bool isTall, bool canSteal) {
    if (FurnitureManager_c::g_currSubGroupId >= std::size(FurnitureManager_c::g_subGroupStore))
        return false;

    auto& sg = FurnitureManager_c::g_subGroupStore[FurnitureManager_c::g_currSubGroupId++];
    sg.m_nSubgroupId = subGroupId;
    sg.m_bCanPlaceInFrontOfWindow = canPlaceInFrontOfWindow;
    sg.m_bIsTall = isTall;
    sg.m_bCanSteal = canSteal;
    m_subGroupsList.AddItem(&sg);
    return true;
}

// 0x591130
Furniture_c* FurnitureGroup_c::GetFurniture(int32 subGroupId, int16 furnitureId, uint8 rating) {
    auto subGroup = GetSubGroup(subGroupId);
    if (!subGroup)
        return nullptr;

    return subGroup->GetFurniture(furnitureId, rating);
}

// 0x591170
int32 FurnitureGroup_c::GetRandomId(int32 subGroupId, uint8 rating) {
    auto subGroup = GetSubGroup(subGroupId);
    if (!subGroup)
        return -1;

    return subGroup->GetRandomId(rating);
}

// 0x5C0230
bool FurnitureGroup_c::AddFurniture(int32 subGroupId, uint16 modelId, int16 id, uint8 wealthMin, uint8 wealthMax, uint8 maxAng) {
    auto subGroup = GetSubGroup(subGroupId);
    if (!subGroup)
        return false;

    return subGroup->AddFurniture(modelId, id, wealthMin, wealthMax, maxAng);
}

FurnitureSubGroup_c* FurnitureGroup_c::GetSubGroup(int32 subGroupId) {
    for (auto& sg : m_subGroupsList) {
        if (sg.m_nSubgroupId == subGroupId) {
            return &sg;
        }
    }
    return nullptr;
}
