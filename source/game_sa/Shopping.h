#pragma once

#include <cstdio> // FILE*

class CShopping {
    struct tPriceModifier {
        const char* key;
        uint32 price;
    };
    VALIDATE_SIZE(tPriceModifier, 8u);

    static constexpr auto NUM_PRICE_MODIFIERS = 20u;
    static constexpr auto NUM_ITEMS = 560u; // ?

    inline static int32& ms_numPrices = *(int32*)0xA9A7CC;
    inline static int32& ms_numPriceModifiers = *(int32*)0xA9A7D0;
    inline static uint32& ms_numBuyableItems = *(uint32*)0xA9A310;
    inline static std::array<tPriceModifier, NUM_PRICE_MODIFIERS>& ms_priceModifiers = *(std::array<tPriceModifier, 20>*)0xA98650;
    inline static std::array<bool, NUM_ITEMS>& ms_bHasBought = *(std::array<bool, 560>*)0xA972A0;

public:
    static void InjectHooks();

    static void Init();
    static void AddPriceModifier(const char* a1, const char* a2, int32 a3);
    static void AddPriceModifier(uint32 a1, int32 a2);
    static void Buy(uint32 a1, int32 a2);
    static void FindItem(uint32 a1);
    static void FindSection(FILE* file, const char* sectionName);
    static void FindSectionInSection(FILE* file, const char* sectionName, const char* a3);
    static void GetExtraInfo(uint32 a1, int32 a2);
    static int32 GetItemIndex(uint32 a1);
    static void GetKey(const char* modelName, int32 index);
    static void GetNameTag(uint32 a1);
    static void GetNextSection(FILE* file);
    static void GetPrice(uint32 itemId);
    static void GetPriceSectionFromName(const char* name);
    static void HasPlayerBought(uint32 a1);
    static void IncrementStat(int32 a1, int32 a2);
    static void IncrementStat2(int32 a1, int32 a2);
    static void Load();
    static void LoadPrices(const char* sectionName);
    static void LoadShop(const char* sectionName);
    static void LoadStats();
    static void RemoveLoadedPrices();
    static void RemoveLoadedShop();
    static void RemovePriceModifier(const char* a1, const char* a2);
    static void RemovePriceModifier(uint32 a1);
    static void RestoreClothesState();
    static void RestoreVehicleMods();
    static void Save();
    static void SetCurrentProperty();
    static void SetPlayerHasBought(uint32 a1);
    static void ShutdownForRestart();
    static void StoreClothesState();
    static void StoreVehicleMods();
    static void UpdateStats(int32 a1, bool a2);
};

extern char& gClothesHaveBeenStored;
extern std::array<eDamageState, 20u>& gComponentDamageState;
extern std::array<int16, NUM_VEHICLE_UPGRADES>& gStoredVehicleMods;
