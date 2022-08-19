#include "StdInc.h"
#include <extensions/enumerate.hpp>
#include "Shopping.h"

void CShopping::InjectHooks() {
    RH_ScopedClass(CShopping);
    RH_ScopedCategoryGlobal();

    //RH_ScopedInstall(Init, 0x49C290);
    //RH_ScopedInstall(AddPriceModifier, 0x0);
    //RH_ScopedInstall(AddPriceModifier, 0x0);
    //RH_ScopedInstall(Buy, 0x49BF70);
    //RH_ScopedInstall(FindItem, 0x0);
    //RH_ScopedInstall(FindSection, 0x49AE70);
    //RH_ScopedInstall(FindSectionInSection, 0x49AF90);
    //RH_ScopedInstall(GetExtraInfo, 0x49ADE0);
    //RH_ScopedInstall(GetItemIndex, 0x49AB10);
    //RH_ScopedInstall(GetKey, 0x49AB30);
    //RH_ScopedInstall(GetNameTag, 0x0);
    //RH_ScopedInstall(GetNextSection, 0x49AF10);
    //RH_ScopedInstall(GetPrice, 0x49AD50);
    //RH_ScopedInstall(GetPriceSectionFromName, 0x49AAD0);
    //RH_ScopedInstall(HasPlayerBought, 0x49B5E0);
    //RH_ScopedInstall(IncrementStat, 0x0);
    //RH_ScopedInstall(IncrementStat2, 0x0);
    //RH_ScopedInstall(LoadPrices, 0x49B8D0);
    //RH_ScopedInstall(LoadShop, 0x49BBE0);
    //RH_ScopedInstall(LoadStats, 0x49B6A0);
    //RH_ScopedInstall(RemoveLoadedPrices, 0x0);
    //RH_ScopedInstall(RemoveLoadedShop, 0x49AE30);
    //RH_ScopedInstall(RemovePriceModifier, 0x0);
    //RH_ScopedInstall(RemovePriceModifier, 0x0);
    //RH_ScopedInstall(RestoreClothesState, 0x49B240);
    //RH_ScopedInstall(RestoreVehicleMods, 0x49B3C0);
    //RH_ScopedInstall(SetPlayerHasBought, 0x49B610);
    //RH_ScopedInstall(ShutdownForRestart, 0x49B640);
    //RH_ScopedInstall(StoreClothesState, 0x49B200);
    //RH_ScopedInstall(StoreVehicleMods, 0x0);
    //RH_ScopedInstall(UpdateStats, 0x0);
    //RH_ScopedInstall(Load, 0x5D3E40);
    //RH_ScopedInstall(Save, 0x5D3DE0);
}

// 0x49C290
void CShopping::Init() {
    ms_numPrices = 0;
    ms_numPriceModifiers = 0;
    ms_numBuyableItems = 0u;
    gClothesHaveBeenStored = 0;

    LoadStats();
}

// Used only in CShopping::LoadStats()
// 0x49ABD0
int32 GetChangingStatIndex(const char* stat) {
    constexpr const char* statNames[] = {
        "fat", "respect", "sexy", "health", "calories"
    };

    for (auto&& [i, name] : notsa::enumerate(statNames)) {
        if (!strcmp(name, stat)) {
            return i;
        }
    }

    return -1;
}

// 0x
void CShopping::AddPriceModifier(const char* a1, const char* a2, int32 a3) {
    plugin::Call<0x0, const char*, const char*, int32>(a1, a2, a3);
}

// 0x
void CShopping::AddPriceModifier(uint32 a1, int32 a2) {
    plugin::Call<0x0, uint32, int32>(a1, a2);
}

// 0x49BF70
void CShopping::Buy(uint32 a1, int32 a2) {
    plugin::Call<0x49BF70, uint32, int32>(a1, a2);
}

// 0x
void CShopping::FindItem(uint32 a1) {
    plugin::Call<0x0, uint32>(a1);
}

// 0x49AE70
void CShopping::FindSection(FILE* file, const char* sectionName) {
    plugin::Call<0x49AE70, FILE*, const char*>(file, sectionName);
}

// unused
// 0x49AF90
void CShopping::FindSectionInSection(FILE* file, const char* sectionName, const char* a3) {

}

// 0x49ADE0
void CShopping::GetExtraInfo(uint32 a1, int32 a2) {
    plugin::Call<0x49ADE0, uint32, int32>(a1, a2);
}

// 0x49AB10
int32 CShopping::GetItemIndex(uint32 a1) {
    return plugin::CallAndReturn<int32, 0x49AB10, uint32>(a1);
}

// 0x49AB30
void CShopping::GetKey(const char* modelName, int32 index) {
    plugin::Call<0x49AB30, const char*, int32>(modelName, index);
}

// 0x
void CShopping::GetNameTag(uint32 a1) {
    plugin::Call<0x0, uint32>(a1);
}

// 0x49AF10
void CShopping::GetNextSection(FILE* file) {
    plugin::Call<0x49AF10, FILE*>(file);
}

// 0x49AD50
void CShopping::GetPrice(uint32 itemId) {
    plugin::Call<0x49AD50, uint32>(itemId);
}

// 0x49AAD0
void CShopping::GetPriceSectionFromName(const char* name) {
    plugin::Call<0x49AAD0, const char*>(name);
}

// 0x49B5E0
void CShopping::HasPlayerBought(uint32 a1) {
    plugin::Call<0x49B5E0, uint32>(a1);
}

// 0x
void CShopping::IncrementStat(int32 a1, int32 a2) {
    plugin::Call<0x0, int32, int32>(a1, a2);
}

// 0x
void CShopping::IncrementStat2(int32 a1, int32 a2) {
    plugin::Call<0x0, int32, int32>(a1, a2);
}

// 0x49B8D0
void CShopping::LoadPrices(const char* sectionName) {
    plugin::Call<0x49B8D0, const char*>(sectionName);
}

// 0x49BBE0
void CShopping::LoadShop(const char* sectionName) {
    plugin::Call<0x49BBE0, const char*>(sectionName);
}

// 0x49B6A0
void CShopping::LoadStats() {
    plugin::Call<0x49B6A0>();
}

// 0x
void CShopping::RemoveLoadedPrices() {
    plugin::Call<0x0>();
}

// 0x49AE30
void CShopping::RemoveLoadedShop() {
    plugin::Call<0x49AE30>();
}

// 0x
void CShopping::RemovePriceModifier(const char* a1, const char* a2) {
    plugin::Call<0x0, const char*, const char*>(a1, a2);
}

// 0x
void CShopping::RemovePriceModifier(uint32 a1) {
    plugin::Call<0x0, uint32>(a1);
}

// 0x49B240
void CShopping::RestoreClothesState() {
    plugin::Call<0x49B240>();
}

// 0x49B3C0
void CShopping::RestoreVehicleMods() {
    plugin::Call<0x49B3C0>();
}

// unused
// 0x
void CShopping::SetCurrentProperty() {

}

// 0x49B610
void CShopping::SetPlayerHasBought(uint32 a1) {
    plugin::Call<0x49B610, uint32>(a1);
}

// 0x49B640
void CShopping::ShutdownForRestart() {
    plugin::Call<0x49B640>();
}

// 0x49B200
void CShopping::StoreClothesState() {
    plugin::Call<0x49B200>();
}

// 0x
void CShopping::StoreVehicleMods() {
    plugin::Call<0x0>();
}

// 0x
void CShopping::UpdateStats(int32 a1, bool a2) {
    plugin::Call<0x0, int32, bool>(a1, a2);
}

// 0x5D3E40
void CShopping::Load() {
    plugin::Call<0x5D3E40>();

    CGenericGameStorage::LoadDataFromWorkBuffer(&ms_numPriceModifiers, sizeof(int32));
    for (auto i = 0; i < ms_numPriceModifiers; i++) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&ms_priceModifiers[i], sizeof(tPriceModifier));
    }

    CGenericGameStorage::LoadDataFromWorkBuffer(&ms_numBuyableItems, sizeof(uint32));
    CGenericGameStorage::LoadDataFromWorkBuffer(&ms_bHasBought, sizeof(ms_numBuyableItems) * sizeof(bool));
}

// 0x5D3DE0
void CShopping::Save() {
    plugin::Call<0x5D3DE0>();

    CGenericGameStorage::SaveDataToWorkBuffer(&ms_numPriceModifiers, sizeof(int32));
    for (auto i = 0; i < ms_numPriceModifiers; i++) {
        CGenericGameStorage::SaveDataToWorkBuffer(&ms_priceModifiers[i], sizeof(tPriceModifier));
    }

    CGenericGameStorage::SaveDataToWorkBuffer(&ms_numBuyableItems, sizeof(uint32));
    CGenericGameStorage::SaveDataToWorkBuffer(&ms_bHasBought, sizeof(ms_numBuyableItems) * sizeof(bool));
}
