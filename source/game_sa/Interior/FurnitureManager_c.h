#pragma once

#include "Base.h"
#include "FurnitureGroup_c.h"
#include "FurnitureItem.h"
#include "List_c.h"

class Furniture_c;

class FurnitureManager_c {
public:
    FurnitureGroup_c m_groups[9];
    FurnitureItem    m_furnitureItem[512];
    TList_c<void>    m_furnitureList;

public:
    static void InjectHooks();

    FurnitureManager_c() = default;  // 0x591260
    ~FurnitureManager_c() = default; // 0x5912E0

    bool Init();
    void Exit();
    void LoadFurniture();
    Furniture_c* GetFurniture(int32 furnitureGroupId, int32 furnitureSubgroupId, int16 id, uint8 wealth);
    int32 GetRandomId(int32 groupId, int32 a3, uint8 a4);
    static int32 GetGroupId(const char* name);
    static int32 GetSubGroupId(const char* name);
};
VALIDATE_SIZE(FurnitureManager_c, 0x2078);

static inline auto& g_furnitureMan = StaticRef<FurnitureManager_c, 0xBAB380>();
