#pragma once

class CShopping {
public:
    static void InjectHooks();

    static void AddPriceModifier(char const* a1, char const* a2, int32 a3);
    static void AddPriceModifier(uint32 a1, int32 a2);
    static void Buy(uint32 a1, int32 a2);
    static void FindItem(uint32 a1);
    static void FindSection(FILE* file, char const* sectionName);
    static void FindSectionInSection(FILE* file, char const* sectionName, char const* a3);
    static void GetExtraInfo(uint32 a1, int32 a2);
    static int32 GetItemIndex(uint32 a1);
    static void GetKey(char const* modelName, int32 index);
    static void GetNameTag(uint32 a1);
    static void GetNextSection(FILE* file);
    static void GetPrice(uint32 itemId);
    static void GetPriceSectionFromName(char const* name);
    static void HasPlayerBought(uint32 a1);
    static void IncrementStat(int32 a1, int32 a2);
    static void IncrementStat2(int32 a1, int32 a2);
    static void Init();
    static void Load();
    static void LoadPrices(char const* sectionName);
    static void LoadShop(char const* sectionName);
    static void LoadStats();
    static void RemoveLoadedPrices();
    static void RemoveLoadedShop();
    static void RemovePriceModifier(char const* a1, char const* a2);
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
