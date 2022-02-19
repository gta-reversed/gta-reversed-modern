#pragma once

#include "Base.h"
#include "FurnitureGroup_c.h"
#include "FurnitureItem.h"
#include "List_c.h"

class Furniture_c;

class FurnitureManager_c {

public:
    FurnitureGroup_c m_groups[9] = {};       // 0
    FurnitureItem m_furnitureItem[512] = {}; // 0x6C
    List_c m_furnitureList = {};             // 0x206C

public:
    static void InjectHooks();

    ~FurnitureManager_c();
    FurnitureManager_c();

    static int32 GetGroupId(const char* name);
    static int32 GetSubGroupId(const char* name);

    void Exit();
    Furniture_c* GetFurniture(int32 furnitureGroupId, int32 furnitureSubgroupId, int16 id, uint8 wealth);
    int32 GetRandomId(int32 groupId, int32 a3, uint8 a4);
    void LoadFurniture();
    void Init();

private:
    FurnitureManager_c* Constructor();
    FurnitureManager_c* Destructor();
};
VALIDATE_SIZE(FurnitureManager_c, 0x2078);
