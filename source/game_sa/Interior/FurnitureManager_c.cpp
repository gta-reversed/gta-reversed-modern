#include "StdInc.h"
#include "FurnitureManager_c.h"

uint32& FurnitureManager_c::g_currSubGroupId  = StaticRef<uint32, 0xBAB37C>();
uint32& FurnitureManager_c::g_currFurnitureId = StaticRef<uint32, 0xBAB378>();
FurnitureSubGroup_c (&FurnitureManager_c::g_subGroupStore)[128] = *(FurnitureSubGroup_c(*)[128])0xBAD3F8;

std::map<std::string_view, int32> groups = {
    { "IT_SHOP",    0},
    { "IT_OFFICE",  1},
    { "IT_LOUNGE",  2},
    { "IT_BEDROOM", 3},
    { "IT_KITCHEN", 4},
    { "IT_MISC",    8},
};

std::map<std::string_view, int32> subGroups = {
// SHOP
    { "SHOP_UNIT1_L",         0 },
    { "SHOP_UNIT1_R",         1 },
    { "SHOP_UNIT1_M",         2 },
    { "SHOP_UNIT2_L",         3 },
    { "SHOP_UNIT2_R",         4 },
    { "SHOP_UNIT2_M",         5 },
    { "SHOP_UNIT3_L",         6 },
    { "SHOP_UNIT3_R",         7 },
    { "SHOP_UNIT3_M",         8 },
    { "SHOP_UNIT4_L",         9 },
    { "SHOP_UNIT4_R",         10},
    { "SHOP_UNIT4_M",         11},
    { "SHOP_CHECKOUTS",       12},
    { "SHOP_BASKETS",         13},
    { "SHOP_LIGHTS",          14},
 // OFFICE
    { "OFFICE_DESKS",         0 },
    { "OFFICE_CHAIRS",        1 },
    { "OFFICE_WATERCOOLERS",  2 },
    { "OFFICE_FILINGCABS",    3 },
 // LOUNGE
    { "LOUNGE_SOFAS",         0 },
    { "LOUNGE_CHAIRS",        1 },
    { "LOUNGE_TVSTANDS",      2 },
    { "LOUNGE_TVS",           3 },
    { "LOUNGE_TABLES",        4 },
    { "LOUNGE_LAMPS",         5 },
    { "LOUNGE_HIFI_TABLES",   6 },
    { "LOUNGE_VIDEOS",        7 },
    { "LOUNGE_HIFIS",         8 },
    { "LOUNGE_CONSOLES",      9 },
 // BEDROOM
    { "BEDROOM_BEDS",         0 },
    { "BEDROOM_TABLES",       1 },
    { "BEDROOM_DRAWERS",      2 },
    { "BEDROOM_WARDROBES",    3 },
 // KITCHEN
    { "KITCHEN_UNIT_L",       0 },
    { "KITCHEN_UNIT_M",       1 },
    { "KITCHEN_UNIT_R",       2 },
    { "KITCHEN_UNIT_SINKS",   3 },
    { "KITCHEN_UNIT_FRIDGES", 4 },
    { "KITCHEN_UNIT_OVENS",   5 },
    { "KITCHEN_UNIT_WASHERS", 6 },
    { "KITCHEN_UNIT_CORNERS", 7 },
    { "KITCHEN_MICROWAVES",   8 },
    { "KITCHEN_TOASTERS",     9 },
    { "KITCHEN_TVS",          10},
 // MISC
    { "MISC_PLANTS",          0 },
    { "MISC_LIGHTS",          1 },
    { "MISC_RUGS",            2 },
    { "MISC_PLATES",          3 },
    { "MISC_FOOD",            4 },
    { "MISC_MAGAZINES",       5 },
    { "MISC_CLOTHES",         6 },
};

void FurnitureManager_c::InjectHooks() {
    RH_ScopedClass(FurnitureManager_c);
    RH_ScopedCategory("Interior");

    //RH_ScopedInstall(Constructor, 0x591260, { .reversed = false });
    //RH_ScopedInstall(Destructor, 0x5912E0, { .reversed = false });
    RH_ScopedGlobalInstall(GetGroupId, 0x5BFB40);
    RH_ScopedGlobalInstall(GetSubGroupId, 0x5BFBF0);
    RH_ScopedInstall(Exit, 0x5911A0);
    RH_ScopedInstall(GetFurniture, 0x5911E0);
    RH_ScopedInstall(GetRandomId, 0x591220);
    RH_ScopedInstall(LoadFurniture, 0x5C0280);
    RH_ScopedInstall(Init, 0x5C04A0);
}

// 0x5C04A0
bool FurnitureManager_c::Init() {
    g_currSubGroupId = 0;
    g_currFurnitureId = 0;

    for (int i = 0; i < std::size(m_furnitureItem); i++) {
        m_furnitureList.AddItem(&m_furnitureItem[i]);
    }

    rng::for_each(m_groups, &FurnitureGroup_c::Init);

    LoadFurniture();
    return true;
}

// 0x5911A0
void FurnitureManager_c::Exit() {
    m_furnitureList.RemoveAll();

    rng::for_each(m_groups, &FurnitureGroup_c::Exit);
}

// 0x5C0280
void FurnitureManager_c::LoadFurniture() {
    auto file = CFileMgr::OpenFile("data\\furnitur.dat", "rb");
    for (auto i = (char*)CFileLoader::LoadLine(file); i; i = (char*)CFileLoader::LoadLine(file)) {
        if (*i == 0 || *i != '#') { // Skip empty and comment lines
            continue;
        }

        int  groupId = -1;
        int  subGroupId = -1;
        char tag[32];
        char groupString[128];

        VERIFY(sscanf(i, "%s", tag) == 1);
        if (!strcmp(tag, "GROUP:")) {
            VERIFY(sscanf(i, "%s %s", tag, groupString) == 2);
            groupId = FurnitureManager_c::GetGroupId(groupString);
        } else if (!strcmp(tag, "SUBGROUP:")) {
            int  minWidth, minDepth, maxWidth, maxDepth, canPlaceInFrontOfWindow, isTall, canSteal;
            VERIFY(sscanf_s(i, "%s %s %d %d %d %d %d %d %d", SCANF_S_STR(tag), SCANF_S_STR(groupString), &minWidth, &minDepth, &maxWidth, &maxDepth, &canPlaceInFrontOfWindow, &isTall, &canSteal) == 9);
            subGroupId = FurnitureManager_c::GetSubGroupId(groupString);
            m_groups[groupId].AddSubGroup(subGroupId, minWidth, minDepth, maxWidth, maxDepth, canPlaceInFrontOfWindow, isTall == 1, canSteal == 1);
        } else if (!strcmp(tag, "ITEM:")) {
            char modelName[64];
            int id, wealthMin, wealthMax, maxAng;
            uint16 modelIndex = -1;
            VERIFY(sscanf_s(i, "%s %s %d %d %d %d", tag, std::size(tag), modelName, std::size(modelName), &id, &wealthMin, &wealthMax, &maxAng) == 6);
            VERIFY(CModelInfo::GetModelInfoUInt16(modelName, &modelIndex) != nullptr);
            m_groups[groupId].AddFurniture(subGroupId, modelIndex, id, wealthMin, wealthMax, maxAng);
        }
    }
    CFileMgr::CloseFile(file);
}

// 0x5BFB40
int32 FurnitureManager_c::GetGroupId(const char* name) {
    const auto it = groups.find(name);
    if (it != groups.end()) {
        return it->second;
    } else {
        return -1;
    }
}

// 0x5BFBF0
int32 FurnitureManager_c::GetSubGroupId(const char* name) {
    const auto it = subGroups.find(name);
    if (it != subGroups.end()) {
        return it->second;
    } else {
        return -1;
    }
}

// 0x5911E0
Furniture_c* FurnitureManager_c::GetFurniture(int32 furnitureGroupId, int32 furnitureSubgroupId, int16 id, uint8 wealth) {
    auto last = m_groups[furnitureGroupId].m_subGroupsList.GetHead();
    if (!last)
        return nullptr;

    while (last->m_nSubgroupId != furnitureSubgroupId) {
        last = last->m_pPrev;
        if (!last)
            return nullptr;
    }

    return last->GetFurniture(id, wealth);
}

// 0x591220
int32 FurnitureManager_c::GetRandomId(int32 groupId, int32 subGroupId, uint8 wealth) {
    auto head = m_groups[subGroupId].m_subGroupsList.GetHead();
    if (!head)
        return -1;

    while (head->m_nSubgroupId != subGroupId) {
        head = head->m_pNext;
        if (!head)
            return -1;
    }

    return head->GetRandomId(wealth);
}
