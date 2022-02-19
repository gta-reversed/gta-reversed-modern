#pragma once

#include "Base.h"

#include "List_c.h"

class Furniture_c;

class FurnitureGroup_c {
public:
    List_c m_subGroupsList = {}; // 0

public:
    static void InjectHooks();

    ~FurnitureGroup_c();
    FurnitureGroup_c();

    int32 Init();
    int32 Exit();
    bool AddSubGroup(int32 subgroupId, int32 minWidth, int32 minDepth, int32 maxWidth, int32 maxDepth, uint8 canPlaceInFrontOfWindow, uint8 isTall, uint8 canSteal);
    Furniture_c* GetFurniture(int32 subGroupId, int16, uint8);
    int32 GetRandomId(int32, uint8);
    int8_t AddFurniture(int32 subgroupId, uint16 modelId, int16 id, uint8 wealthMin, uint8 wealthMax, uint8 maxAng);

private:
    FurnitureGroup_c* Constructor();
    FurnitureGroup_c* Destructor();
};
VALIDATE_SIZE(FurnitureGroup_c, 0xC);
