#include "StdInc.h"
#include "FurnitureManager_c.h"

uint32& g_currSubGroupId = StaticRef<uint32, 0xBAB37C>();
uint32& g_currFurnitureId = StaticRef<uint32, 0xBAB378>();
FurnitureSubGroup_c (&g_subGroupStore)[128] = *(FurnitureSubGroup_c(*)[128])0xBAD3F8;

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

    for (int i = 0; i < 512; i++) {
        m_furnitureList.AddItem(&m_furnitureItem[i]);
    }

    for (int i = 0; i < 9; i++) {
        m_groups[i].Init();
    }

    LoadFurniture();
    return true;
}

// 0x5911A0
void FurnitureManager_c::Exit() {
    m_furnitureList.RemoveAll();

    for (int g = 0; g < 9; g++) {
        for (List_c* i = reinterpret_cast<List_c*>(this->m_groups[g].m_subGroupsList.GetHead()); i; i = reinterpret_cast<List_c*>(i->GetTail())) {
            reinterpret_cast<List_c*>(i->GetHead())->RemoveAll();
        }
        this->m_groups[g].m_subGroupsList.RemoveAll();
    }
}

// 0x5C0280
void FurnitureManager_c::LoadFurniture() {
    auto file = CFileMgr::OpenFile("data\\furnitur.dat", "rb");
    for (auto i = (char*)CFileLoader::LoadLine(file); i; i = (char*)CFileLoader::LoadLine(file)) {
        if (*i != 35 && *i) {
            int  groupId    = -1;
            int  subGroupId = -1;
            char tag[32];
            char groupString[128];

            RET_IGNORED(sscanf(i, "%s", tag));
            if (!strcmp(tag, "GROUP:")) {
                RET_IGNORED(sscanf(i, "%s %s", tag, groupString));
                groupId = FurnitureManager_c::GetGroupId(groupString);
            } else if (!strcmp(tag, "SUBGROUP:")) {
                int  minWidth, minDepth, maxWidth, maxDepth, canPlaceInFrontOfWindow, isTall, canSteal;
                VERIFY(sscanf_s(i, "%s %s %d %d %d %d %d %d %d", tag, std::size(tag), groupString, std::size(groupString), &minWidth, &minDepth, &maxWidth, &maxDepth, &canPlaceInFrontOfWindow, &isTall, &canSteal) == 9);
                subGroupId = FurnitureManager_c::GetSubGroupId(groupString);
                m_groups[groupId].AddSubGroup(subGroupId, minWidth, minDepth, maxWidth, maxDepth, canPlaceInFrontOfWindow, isTall == 1, canSteal == 1);
            } else if (!strcmp(tag, "ITEM:")) {
                char modelName[64];
                int id, wealthMin, wealthMax, maxAng;
                uint16 modelIndex = -1;
                VERIFY(sscanf_s(i, "%s %s %d %d %d %d", tag, std::size(tag), modelName, std::size(modelName), &id, &wealthMin, &wealthMax, &maxAng) == 6);
                if (CModelInfo::GetModelInfoUInt16(modelName, &modelIndex)) {
                    m_groups[groupId].AddFurniture(subGroupId, modelIndex, id, wealthMin, wealthMax, maxAng);
                } else {
                    // I guess this is used for debug mode? because the variable string is written to is never used.
                    // So maybe the usage got removed during compilation in release mode.
                    // sprintf(v23, "Cannot find model %s", modelName);
                }
            }
        }
    }
    CFileMgr::CloseFile(file);
}

// 0x5BFB40
int32 FurnitureManager_c::GetGroupId(const char* name) {
    if (!strcmp(name, "IT_SHOP")) {
        return 0;
    }
    if (!strcmp(name, "IT_OFFICE")) {
        return 1;
    }
    if (!strcmp(name, "IT_LOUNGE")) {
        return 2;
    }
    if (!strcmp(name, "IT_BEDROOM")) {
        return 3;
    }
    if (!strcmp(name, "IT_KITCHEN")) {
        return 4;
    }
    return strcmp(name, "IT_MISC") != 0 ? -1 : 8;
}

// 0x5BFBF0
int32 FurnitureManager_c::GetSubGroupId(const char* name) {
    if (!strcmp(name, "SHOP_UNIT1_L")) {
        return 0;
    }
    if (!strcmp(name, "SHOP_UNIT1_R")) {
        return 1;
    }
    if (!strcmp(name, "SHOP_UNIT1_M")) {
        return 2;
    }
    if (!strcmp(name, "SHOP_UNIT2_L")) {
        return 3;
    }
    if (!strcmp(name, "SHOP_UNIT2_R")) {
        return 4;
    }
    if (!strcmp(name, "SHOP_UNIT2_M")) {
        return 5;
    }
    if (!strcmp(name, "SHOP_UNIT3_L")) {
        return 6;
    }
    if (!strcmp(name, "SHOP_UNIT3_R")) {
        return 7;
    }
    if (!strcmp(name, "SHOP_UNIT3_M")) {
        return 8;
    }
    if (!strcmp(name, "SHOP_UNIT4_L")) {
        return 9;
    }
    if (!strcmp(name, "SHOP_UNIT4_R")) {
        return 10;
    }
    if (!strcmp(name, "SHOP_UNIT4_M")) {
        return 11;
    }
    if (!strcmp(name, "SHOP_CHECKOUTS")) {
        return 12;
    }
    if (!strcmp(name, "SHOP_BASKETS")) {
        return 13;
    }
    if (!strcmp(name, "SHOP_LIGHTS")) {
        return 14;
    }
    if (!strcmp(name, "OFFICE_DESKS")) {
        return 0;
    }
    if (!strcmp(name, "OFFICE_CHAIRS")) {
        return 1;
    }
    if (!strcmp(name, "OFFICE_WATERCOOLERS")) {
        return 2;
    }
    if (!strcmp(name, "OFFICE_FILINGCABS")) {
        return 3;
    }
    if (!strcmp(name, "LOUNGE_SOFAS")) {
        return 0;
    }
    if (!strcmp(name, "LOUNGE_CHAIRS")) {
        return 1;
    }
    if (!strcmp(name, "LOUNGE_TVSTANDS")) {
        return 2;
    }
    if (!strcmp(name, "LOUNGE_TVS")) {
        return 3;
    }
    if (!strcmp(name, "LOUNGE_TABLES")) {
        return 4;
    }
    if (!strcmp(name, "LOUNGE_LAMPS")) {
        return 5;
    }
    if (!strcmp(name, "LOUNGE_HIFI_TABLES")) {
        return 6;
    }
    if (!strcmp(name, "LOUNGE_VIDEOS")) {
        return 7;
    }
    if (!strcmp(name, "LOUNGE_HIFIS")) {
        return 8;
    }
    if (!strcmp(name, "LOUNGE_CONSOLES")) {
        return 9;
    }
    if (!strcmp(name, "BEDROOM_BEDS")) {
        return 0;
    }
    if (!strcmp(name, "BEDROOM_TABLES")) {
        return 1;
    }
    if (!strcmp(name, "BEDROOM_DRAWERS")) {
        return 2;
    }
    if (!strcmp(name, "BEDROOM_WARDROBES")) {
        return 3;
    }
    if (!strcmp(name, "KITCHEN_UNIT_L")) {
        return 0;
    }
    if (!strcmp(name, "KITCHEN_UNIT_M")) {
        return 1;
    }
    if (!strcmp(name, "KITCHEN_UNIT_R")) {
        return 2;
    }
    if (!strcmp(name, "KITCHEN_UNIT_SINKS")) {
        return 3;
    }
    if (!strcmp(name, "KITCHEN_UNIT_FRIDGES")) {
        return 4;
    }
    if (!strcmp(name, "KITCHEN_UNIT_OVENS")) {
        return 5;
    }
    if (!strcmp(name, "KITCHEN_UNIT_WASHERS")) {
        return 6;
    }
    if (!strcmp(name, "KITCHEN_UNIT_CORNERS")) {
        return 7;
    }
    if (!strcmp(name, "KITCHEN_MICROWAVES")) {
        return 8;
    }
    if (!strcmp(name, "KITCHEN_TOASTERS")) {
        return 9;
    }
    if (!strcmp(name, "KITCHEN_TVS")) {
        return 10;
    }
    if (!strcmp(name, "MISC_PLANTS")) {
        return 0;
    }
    if (!strcmp(name, "MISC_LIGHTS")) {
        return 1;
    }
    if (!strcmp(name, "MISC_RUGS")) {
        return 2;
    }
    if (!strcmp(name, "MISC_PLATES")) {
        return 3;
    }
    if (!strcmp(name, "MISC_FOOD")) {
        return 4;
    }
    if (!strcmp(name, "MISC_MAGAZINES")) {
        return 5;
    }
    return strcmp(name, "MISC_CLOTHES") != 0 ? -1 : 6;
}

// 0x5911E0
Furniture_c* FurnitureManager_c::GetFurniture(int32 furnitureGroupId, int32 furnitureSubgroupId, int16 id, uint8 wealth) {
    auto last = reinterpret_cast<FurnitureSubGroup_c*>(m_groups[furnitureGroupId].m_subGroupsList.GetHead());
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
    auto head = reinterpret_cast<FurnitureSubGroup_c*>(m_groups[subGroupId].m_subGroupsList.GetHead());
    if (!head)
        return -1;

    while (head->m_nSubgroupId != subGroupId) {
        head = head->m_pNext;
        if (!head)
            return -1;
    }

    return head->GetRandomId(wealth);
}
