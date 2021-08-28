/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned int MAX_NUM_WEAPON_CROSSHAIRS = 2;
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
bool CWeaponEffects::IsLockedOn(int crosshairId) {
    return plugin::CallAndReturn<bool, 0x742BD0, int>(crosshairId);
}

// 0x742BF0
void CWeaponEffects::MarkTarget(int crosshairId, CVector posn, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, float size, unsigned char arg7) {
    plugin::Call<0x742BF0, int, CVector, unsigned char, unsigned char, unsigned char, unsigned char, float, unsigned char>(crosshairId, posn, red, green, blue, alpha, size, arg7);
}

// 0x742C60
void CWeaponEffects::ClearCrossHair(int crosshairId) {
    plugin::Call<0x742C60, int>(crosshairId);
}

// 0x742C80
void CWeaponEffects::ClearCrossHairs() {
    plugin::Call<0x742C80>();
}

// 0x742CA0
void CWeaponEffects::ClearCrossHairImmediately(int crosshairId) {
    plugin::Call<0x742CA0, int>(crosshairId);
}

// 0x742CC0
void CWeaponEffects::ClearCrossHairsImmediately() {
    plugin::Call<0x742CC0>();
}

// 0x742CF0
void CWeaponEffects::Render() {
    plugin::Call<0x742CF0>();
}