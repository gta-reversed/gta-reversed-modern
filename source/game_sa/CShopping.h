#pragma once

class CShopping {
public:
    static void InjectHooks();

    static void AddPriceModifier(char const* a1, char const* a2, int a3);
    static void AddPriceModifier(unsigned int a1, int a2);
    static void Buy(unsigned int a1, int a2);
    static void FindItem(unsigned int a1);
    static void FindSection(FILE* file, char const* sectionName);
    static void FindSectionInSection(FILE* file, char const* sectionName, char const* a3);
    static void GetExtraInfo(unsigned int a1, int a2);
    static int GetItemIndex(unsigned int a1);
    static void GetKey(char const* modelName, int index);
    static void GetNameTag(unsigned int a1);
    static void GetNextSection(FILE* file);
    static void GetPrice(unsigned int itemId);
    static void GetPriceSectionFromName(char const* name);
    static void HasPlayerBought(unsigned int a1);
    static void IncrementStat(int a1, int a2);
    static void IncrementStat2(int a1, int a2);
    static void Init();
    static void Load();
    static void LoadPrices(char const* sectionName);
    static void LoadShop(char const* sectionName);
    static void LoadStats();
    static void RemoveLoadedPrices();
    static void RemoveLoadedShop();
    static void RemovePriceModifier(char const* a1, char const* a2);
    static void RemovePriceModifier(unsigned int a1);
    static void RestoreClothesState();
    static void RestoreVehicleMods();
    static void Save();
    static void SetCurrentProperty();
    static void SetPlayerHasBought(unsigned int a1);
    static void ShutdownForRestart();
    static void StoreClothesState();
    static void StoreVehicleMods();
    static void UpdateStats(int a1, bool a2);
};
