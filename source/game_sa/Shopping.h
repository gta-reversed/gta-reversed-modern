#pragma once

#include <cstdio> // FILE*
#include "TheZones.h"

extern std::array<float, NUM_LEVELS>& gPriceMultipliers;

// incomplete, todo: move
class CMultiBuilding {};

class CShopping {
    struct PriceModifier {
        const char* key;
        uint32 price;
    };
    VALIDATE_SIZE(PriceModifier, 8u);

    struct ItemPrice {
        const char* key;
        uint32 price;

        union {
            struct {
                uint32 ammo;
            } weapon;
            struct {
                uint32 modelKey;
                uint32 type;
            } clothes;
            struct {
                uint32 type1;
                uint32 texKey;
            } tattoos;
            struct {
                int32 extra1;
                int32 extra2;
            } general;
        };

        char nameTag[8];
    };

    static constexpr auto NUM_PRICE_MODIFIERS = 20u;
    static constexpr auto NUM_ITEMS = 560u; // ?
    static constexpr auto NUM_SELLABLE_ITEMS = 300u; // ?
    static constexpr auto NUM_SHOPS = 24u;
    static constexpr auto NUM_SECTION_NAMES = 11u;

    inline static int32& ms_priceSectionLoaded = *(int32*)0xA9A7C8;
    inline static int32& ms_numPrices = *(int32*)0xA9A7CC;
    inline static int32& ms_numPriceModifiers = *(int32*)0xA9A7D0;
    inline static std::array<int8, NUM_SHOPS>& ms_shopLoaded = *(std::array<int8, NUM_SHOPS>*)0xA9A7D8;
    inline static uint32& ms_numBuyableItems = *(uint32*)0xA9A310;
    inline static std::array<PriceModifier, NUM_PRICE_MODIFIERS>& ms_priceModifiers = *(std::array<PriceModifier, NUM_PRICE_MODIFIERS>*)0xA98650;
    inline static std::array<bool, NUM_ITEMS>& ms_bHasBought = *(std::array<bool, NUM_ITEMS>*)0xA972A0;
    inline static std::array<uint32, NUM_ITEMS>& ms_keys = *(std::array<uint32, NUM_ITEMS>*)0xA97D90;

    inline static std::array<ItemPrice, NUM_SELLABLE_ITEMS>& ms_prices = *(std::array<ItemPrice, NUM_SELLABLE_ITEMS>*)0xA022A8;
    inline static std::array<const char*, NUM_SECTION_NAMES>& ms_sectionNames = *(std::array<const char*, NUM_SECTION_NAMES>*)0x8A61D8;

public:
    static void InjectHooks();

    static void Init();
    static void AddPriceModifier(const char* a1, const char* a2, int32 a3);
    static void AddPriceModifier(uint32 a1, int32 a2);
    static void Buy(uint32 a1, int32 a2);
    static int32 FindItem(uint32 itemKey);
    static bool FindSection(FILESTREAM file, const char* sectionName);
    static bool FindSectionInSection(FILESTREAM file, const char* parentSection, const char* childSection);
    static int32 GetExtraInfo(uint32 itemKey, int32 index);
    static int32 GetItemIndex(uint32 itemKey);
    static void GetKey(const char* modelName, int32 index);
    static void GetNameTag(uint32 a1);
    static void GetNextSection(FILESTREAM file);
    static int32 GetPrice(uint32 itemId);
    static int32 GetPriceSectionFromName(const char* name);
    static void SetPlayerHasBought(uint32 itemKey);
    static bool HasPlayerBought(uint32 itemKey);
    static void IncrementStat(int32 a1, int32 a2);
    static void IncrementStat2(int32 a1, int32 a2);
    static void LoadPrices(const char* sectionName);
    static void LoadShop(const char* sectionName);
    static void LoadStats();
    static void RemoveLoadedPrices();
    static void RemoveLoadedShop();
    static void RemovePriceModifier(const char* a1, const char* a2);
    static void RemovePriceModifier(uint32 a1);
    static void RestoreClothesState();
    static void RestoreVehicleMods();
    static void SetCurrentProperty(CMultiBuilding* property);
    static void ShutdownForRestart();
    static void StoreClothesState();
    static void StoreVehicleMods();
    static void UpdateStats(int32 a1, bool a2);
    static void Load();
    static void Save();

    // NOTSA
    static int32 GetPriceMultipliedByLevel(int32 price, eLevelName level = NUM_LEVELS) {
        level = (level == NUM_LEVELS) ? CTheZones::m_CurrLevel : level;
        return (float)price * gPriceMultipliers[level];
    }
};

static constexpr auto NUM_COMPONENTS = 20u; // ?

extern char& gClothesHaveBeenStored;
extern std::array<eDamageState, NUM_COMPONENTS>& gComponentDamageState;
extern std::array<int16, NUM_VEHICLE_UPGRADES>& gStoredVehicleMods;
extern CPedClothesDesc& gStoredClothesState;
extern CMultiBuilding* gpCurrentProperty;
