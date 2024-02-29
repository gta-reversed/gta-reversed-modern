/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "SetPieces.h"

void CSetPieces::InjectHooks() {
    RH_ScopedClass(CSetPieces);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(AddOne, 0x499500, {.reversed=false});
    RH_ScopedInstall(Init, 0x4994F0, {.reversed=false});
    RH_ScopedInstall(Load, 0x5D3CA0, {.reversed=false});
    RH_ScopedInstall(Save, 0x5D3C70, {.reversed=false});
    RH_ScopedInstall(Update, 0x49AA00, {.reversed=false});
}

// 0x499500
void CSetPieces::AddOne(uint8 type, CVector2D cornerA, CVector2D cornerB, CVector2D spawnCoord1, CVector2D targetCoord1, CVector2D spawnCoord2, CVector2D targetCoord2) {
    plugin::Call<0x499500, uint8, CVector2D, CVector2D, CVector2D, CVector2D, CVector2D, CVector2D>(type, cornerA, cornerB, spawnCoord1, targetCoord1, spawnCoord2, targetCoord2);
}

// 0x4994F0
void CSetPieces::Init() {
    ZoneScoped;

    plugin::Call<0x4994F0>();
}

// 0x5D3CA0
bool CSetPieces::Load() {
    return plugin::CallAndReturn<bool, 0x5D3CA0>();
}

// 0x5D3C70
bool CSetPieces::Save() {
    return plugin::CallAndReturn<bool, 0x5D3C70>();
}

// 0x49AA00
void CSetPieces::Update() {
    ZoneScoped;

    plugin::Call<0x49AA00>();
}
