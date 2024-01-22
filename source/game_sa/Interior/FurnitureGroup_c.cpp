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
    auto currentList = reinterpret_cast<List_c*>(m_subGroupsList.GetHead());
    if (currentList) {
        do {
            reinterpret_cast<List_c*>(currentList->GetHead())->RemoveAll();
            currentList = reinterpret_cast<List_c*>(currentList->GetTail());
        } while (currentList);
    }
    m_subGroupsList.RemoveAll();
}

// 0x5910E0
bool FurnitureGroup_c::AddSubGroup(int32 subGroupId, int32 minWidth, int32 minDepth, int32 maxWidth, int32 maxDepth, uint8 canPlaceInFrontOfWindow, bool isTall, bool canSteal) {
    if ( g_currSubGroupId >= 0x80u )
        return false;

    auto nextId = g_currSubGroupId++;
    g_subGroupStore[nextId].m_nSubgroupId = subGroupId;
    g_subGroupStore[nextId].m_bCanPlaceInFrontOfWindow = canPlaceInFrontOfWindow;
    g_subGroupStore[nextId].m_bIsTall = isTall;
    g_subGroupStore[nextId].m_bCanSteal = canSteal;
    m_subGroupsList.AddItem(&g_subGroupStore[nextId]);
    return true;
}

// 0x591130
Furniture_c* FurnitureGroup_c::GetFurniture(int32 subGroupId, int16 refId, uint8 rating) {
    auto subGroup = reinterpret_cast<FurnitureSubGroup_c*>(m_subGroupsList.GetHead());
    if (!subGroup)
        return nullptr;

    while (subGroup->m_nSubgroupId != subGroupId) {
        subGroup = subGroup->m_pNext;
        if (!subGroup) 
            return nullptr;
    }

    return subGroup->GetFurniture(refId, rating);
}

// 0x591170
int32 FurnitureGroup_c::GetRandomId(int32 subGroupId, uint8 rating) {
    auto subGroup = reinterpret_cast<FurnitureSubGroup_c*>(m_subGroupsList.GetHead());
    if (!subGroup)
        return -1;

    while (subGroup->m_nSubgroupId != subGroupId) {
        subGroup = subGroup->m_pNext;
        if (!subGroup) 
            return -1;
    }

    return subGroup->GetRandomId(rating);
}

// 0x5C0230
bool FurnitureGroup_c::AddFurniture(int32 subGroupId, uint16 modelId, int16 id, uint8 wealthMin, uint8 wealthMax, uint8 maxAng) {
    auto subGroup = reinterpret_cast<FurnitureSubGroup_c*>(m_subGroupsList.GetHead());
    if (subGroup) {
        do {
            if (subGroup->m_nSubgroupId == subGroupId) {
                subGroup->AddFurniture(modelId, id, wealthMin, wealthMax, maxAng);
            }
            subGroup = subGroup->m_pNext;
        } while (subGroup);
    }

    return true;
}
