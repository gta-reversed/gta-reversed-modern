/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

uint32 MAX_NUM_WEAPON_CROSSHAIRS = 2;
CWeaponEffects* gCrossHair = (CWeaponEffects*)0xC8A838;
RwTexture*& gpCrossHairTex = *(RwTexture * *)0xC8A818;
RwTexture** gpCrossHairTexFlight = (RwTexture * *)0xC8A810;

// 0x742A90
CWeaponEffects::CWeaponEffects() {
    plugin::CallMethod<0x742A90, CWeaponEffects*>(this);
}

// 0x742AA0
CWeaponEffects::~CWeaponEffects() {
    plugin::CallMethod<0x742AA0, CWeaponEffects*>(this);
}

// 0x742AB0
void CWeaponEffects::Init() {
    plugin::Call<0x742AB0>();
}

// 0x742B80
void CWeaponEffects::Shutdown() {
    plugin::Call<0x742B80>();
}

// 0x742BD0
bool CWeaponEffects::IsLockedOn(int32 crosshairId) {
    return plugin::CallAndReturn<bool, 0x742BD0, int32>(crosshairId);
}

// 0x742BF0
void CWeaponEffects::MarkTarget(int32 crosshairId, CVector posn, uint8 red, uint8 green, uint8 blue, uint8 alpha, float size, uint8 arg7) {
    plugin::Call<0x742BF0, int32, CVector, uint8, uint8, uint8, uint8, float, uint8>(crosshairId, posn, red, green, blue, alpha, size, arg7);
}

// 0x742C60
void CWeaponEffects::ClearCrossHair(int32 crosshairId) {
    plugin::Call<0x742C60, int32>(crosshairId);
}

// 0x742C80
void CWeaponEffects::ClearCrossHairs() {
    plugin::Call<0x742C80>();
}

// 0x742CA0
void CWeaponEffects::ClearCrossHairImmediately(int32 crosshairId) {
    plugin::Call<0x742CA0, int32>(crosshairId);
}

// 0x742CC0
void CWeaponEffects::ClearCrossHairsImmediately() {
    plugin::Call<0x742CC0>();
}

// 0x742CF0
void CWeaponEffects::Render() {
    plugin::Call<0x742CF0>();
}