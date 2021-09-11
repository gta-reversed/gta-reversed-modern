#include "StdInc.h"

void CShopping::InjectHooks() {
//    ReversibleHooks::Install("CShopping", "AddPriceModifier", 0x0, &CShopping::AddPriceModifier);
//    ReversibleHooks::Install("CShopping", "AddPriceModifier", 0x0, &CShopping::AddPriceModifier);
//    ReversibleHooks::Install("CShopping", "Buy", 0x49BF70, &CShopping::Buy);
//    ReversibleHooks::Install("CShopping", "FindItem", 0x0, &CShopping::FindItem);
//    ReversibleHooks::Install("CShopping", "FindSection", 0x49AE70, &CShopping::FindSection);
//    ReversibleHooks::Install("CShopping", "FindSectionInSection", 0x49AF90, &CShopping::FindSectionInSection);
//    ReversibleHooks::Install("CShopping", "GetExtraInfo", 0x49ADE0, &CShopping::GetExtraInfo);
//    ReversibleHooks::Install("CShopping", "GetItemIndex", 0x49AB10, &CShopping::GetItemIndex);
//    ReversibleHooks::Install("CShopping", "GetKey", 0x49AB30, &CShopping::GetKey);
//    ReversibleHooks::Install("CShopping", "GetNameTag", 0x0, &CShopping::GetNameTag);
//    ReversibleHooks::Install("CShopping", "GetNextSection", 0x49AF10, &CShopping::GetNextSection);
//    ReversibleHooks::Install("CShopping", "GetPrice", 0x49AD50, &CShopping::GetPrice);
//    ReversibleHooks::Install("CShopping", "GetPriceSectionFromName", 0x49AAD0, &CShopping::GetPriceSectionFromName);
//    ReversibleHooks::Install("CShopping", "HasPlayerBought", 0x49B5E0, &CShopping::HasPlayerBought);
//    ReversibleHooks::Install("CShopping", "IncrementStat", 0x0, &CShopping::IncrementStat);
//    ReversibleHooks::Install("CShopping", "IncrementStat2", 0x0, &CShopping::IncrementStat2);
//    ReversibleHooks::Install("CShopping", "Init", 0x49C290, &CShopping::Init);
//    ReversibleHooks::Install("CShopping", "Load", 0x5D3E40, &CShopping::Load);
//    ReversibleHooks::Install("CShopping", "LoadPrices", 0x49B8D0, &CShopping::LoadPrices);
//    ReversibleHooks::Install("CShopping", "LoadShop", 0x49BBE0, &CShopping::LoadShop);
//    ReversibleHooks::Install("CShopping", "LoadStats", 0x49B6A0, &CShopping::LoadStats);
//    ReversibleHooks::Install("CShopping", "RemoveLoadedPrices", 0x0, &CShopping::RemoveLoadedPrices);
//    ReversibleHooks::Install("CShopping", "RemoveLoadedShop", 0x49AE30, &CShopping::RemoveLoadedShop);
//    ReversibleHooks::Install("CShopping", "RemovePriceModifier", 0x0, &CShopping::RemovePriceModifier);
//    ReversibleHooks::Install("CShopping", "RemovePriceModifier", 0x0, &CShopping::RemovePriceModifier);
//    ReversibleHooks::Install("CShopping", "RestoreClothesState", 0x49B240, &CShopping::RestoreClothesState);
//    ReversibleHooks::Install("CShopping", "RestoreVehicleMods", 0x49B3C0, &CShopping::RestoreVehicleMods);
//    ReversibleHooks::Install("CShopping", "Save", 0x5D3DE0, &CShopping::Save);
//    ReversibleHooks::Install("CShopping", "SetPlayerHasBought", 0x49B610, &CShopping::SetPlayerHasBought);
//    ReversibleHooks::Install("CShopping", "ShutdownForRestart", 0x49B640, &CShopping::ShutdownForRestart);
//    ReversibleHooks::Install("CShopping", "StoreClothesState", 0x49B200, &CShopping::StoreClothesState);
//    ReversibleHooks::Install("CShopping", "StoreVehicleMods", 0x0, &CShopping::StoreVehicleMods);
//    ReversibleHooks::Install("CShopping", "UpdateStats", 0x0, &CShopping::UpdateStats);
}

// Used only in CShopping::LoadStats()
// 0x49ABD0
int32 GetChangingStatIndex(const char* stat) {
    if (!strcmp("-", stat))
        return -1;
    if (!strcmp("fat", stat))
        return 0;
    if (!strcmp("respect", stat))
        return 1;
    if (!strcmp("sexy", stat))
        return 2;
    if (!strcmp("health", stat))
        return 3;
    if (!strcmp("stamina", stat))
        return 4;
    if (strcmp("calories", stat) != 0)
        return -1;

    return 5;
}

// 0x
void CShopping::AddPriceModifier(char const* a1, char const* a2, int32 a3) {
    plugin::Call<0x0, char const*, char const*, int32>(a1, a2, a3);
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
void CShopping::FindSection(FILE* file, char const* sectionName) {
    plugin::Call<0x49AE70, FILE*, char const*>(file, sectionName);
}

// unused
// 0x49AF90
void CShopping::FindSectionInSection(FILE* file, char const* sectionName, char const* a3) {

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
void CShopping::GetKey(char const* modelName, int32 index) {
    plugin::Call<0x49AB30, char const*, int32>(modelName, index);
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
void CShopping::GetPriceSectionFromName(char const* name) {
    plugin::Call<0x49AAD0, char const*>(name);
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

// 0x49C290
void CShopping::Init() {
    plugin::Call<0x49C290>();
}

// 0x5D3E40
void CShopping::Load() {
    plugin::Call<0x5D3E40>();
}

// 0x49B8D0
void CShopping::LoadPrices(char const* sectionName) {
    plugin::Call<0x49B8D0, char const*>(sectionName);
}

// 0x49BBE0
void CShopping::LoadShop(char const* sectionName) {
    plugin::Call<0x49BBE0, char const*>(sectionName);
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
void CShopping::RemovePriceModifier(char const* a1, char const* a2) {
    plugin::Call<0x0, char const*, char const*>(a1, a2);
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

// 0x5D3DE0
void CShopping::Save() {
    plugin::Call<0x5D3DE0>();
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
