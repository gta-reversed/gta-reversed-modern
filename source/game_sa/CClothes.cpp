#include "StdInc.h"

/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

// Converted from cdecl void CClothes::ConstructPedModel(uint modelid,CPedClothesDesc &newclothes,CPedClothesDesc const*oldclothes,bool bCutscenePlayer) 0x5A81E0 
void CClothes::ConstructPedModel(unsigned int modelid, CPedClothesDesc& newclothes, CPedClothesDesc const* oldclothes, bool bCutscenePlayer) {
    plugin::Call<0x5A81E0, unsigned int, CPedClothesDesc&, CPedClothesDesc const*, bool>(modelid, newclothes, oldclothes, bCutscenePlayer);
}

// Converted from cdecl void CClothes::RequestMotionGroupAnims(void) 0x5A8120 
void CClothes::RequestMotionGroupAnims() {
    plugin::Call<0x5A8120>();
}

// Converted from cdecl void CClothes::RebuildPlayerIfNeeded(CPlayerPed *player) 0x5A8390 
void CClothes::RebuildPlayerIfNeeded(CPlayerPed* player) {
    plugin::Call<0x5A8390, CPlayerPed*>(player);
}

// Converted from cdecl void CClothes::RebuildPlayer(CPlayerPed *player,bool bIgnoreFatAndMuscle) 0x5A82C0 
void CClothes::RebuildPlayer(CPlayerPed* player, bool bIgnoreFatAndMuscle) {
    plugin::Call<0x5A82C0, CPlayerPed*, bool>(player, bIgnoreFatAndMuscle);
}

// Converted from cdecl void CClothes::RebuildCutscenePlayer(CPlayerPed *player,int modelid) 0x5A8270 
void CClothes::RebuildCutscenePlayer(CPlayerPed* player, int modelid) {
    plugin::Call<0x5A8270, CPlayerPed*, int>(player, modelid);
}

// Converted from cdecl void CClothes::LoadClothesFile(void) 0x5A7B30 
void CClothes::LoadClothesFile() {
    plugin::Call<0x5A7B30>();
}

// Converted from cdecl void CClothes::Init(void) 0x5A80D0 
void CClothes::Init() {
    plugin::Call<0x5A80D0>();
}

// Converted from cdecl eClothesModelPart CClothes::GetTextureDependency(int eClothesTexturePart) 0x5A7EA0 
eClothesModelPart CClothes::GetTextureDependency(int eClothesTexturePart) {
    eClothesModelPart result;
    plugin::CallAndReturn<eClothesModelPart, 0x5A7EA0, eClothesModelPart*, int>(&result, eClothesTexturePart);
    return result;
}

// Converted from cdecl int CClothes::GetPlayerMotionGroupToLoad(void) 0x5A7FB0 
int CClothes::GetPlayerMotionGroupToLoad() {
    return plugin::CallAndReturn<int, 0x5A7FB0>();
}

// Converted from cdecl eClothesTexturePart CClothes::GetDependentTexture(int eClothesModelPart) 0x5A7F30 
eClothesTexturePart CClothes::GetDependentTexture(int eClothesModelPart) {
    eClothesTexturePart result;
    plugin::CallAndReturn<eClothesTexturePart, 0x5A7F30, eClothesTexturePart*, int>(&result, eClothesModelPart);
    return result;
}

// Converted from cdecl int CClothes::GetDefaultPlayerMotionGroup(void) 0x5A81B0
int CClothes::GetDefaultPlayerMotionGroup() {
    return plugin::CallAndReturn<int, 0x5A81B0>();
}
