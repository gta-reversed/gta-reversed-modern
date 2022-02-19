#pragma once

#include "Base.h"

#include "ListItem_c.h"

class Furniture_c;

class FurnitureSubGroup_c : public ListItem_c {
public:
    int32 m_nSubgroupId = {};             // 8
    List_c m_furniturList = {};           // 0xC
    bool m_bCanPlaceInFrontOfWindow = {}; // 0x18
    bool m_bIsTall = {};                  // 0x19
    bool m_bCanSteal = {};                // 0x1A
    int8_t _pad1B = {};                   // 0x1B

public:
    static void InjectHooks();

    ~FurnitureSubGroup_c();
    FurnitureSubGroup_c();

    Furniture_c* GetFurniture(int16 id, uint8 wealth);
    int32 GetRandomId(uint8 a2);
    bool AddFurniture(uint16 modelId, int16 id, uint8 wealthMin, uint8 wealthMax, uint8 maxAng);

private:
    FurnitureSubGroup_c* Constructor();
    FurnitureSubGroup_c* Destructor();
};
VALIDATE_SIZE(FurnitureSubGroup_c, 0x1C);
