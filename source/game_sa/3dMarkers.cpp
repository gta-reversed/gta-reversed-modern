#include "StdInc.h"

#include "3dMarkers.h"

void C3dMarkers::InjectHooks() {
    RH_ScopedClass(C3dMarkers);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x724E40, { .reversed = false });
    RH_ScopedInstall(Update, 0x7227B0, { .reversed = false });
    RH_ScopedInstall(Shutdown, 0x722710, { .reversed = false });
    RH_ScopedInstall(Render, 0x725040, { .reversed = false });
    RH_ScopedInstall(LoadUser3dMarkers, 0x5D42E0, { .reversed = false });
    RH_ScopedInstall(SaveUser3dMarkers, 0x5D4300, { .reversed = false });
}

// 0x724E40
void C3dMarkers::Init() {
    plugin::Call<0x724E40>();
}

// 0x7227B0
void C3dMarkers::Update() {
    plugin::Call<0x7227B0>();
}

// 0x722710
void C3dMarkers::Shutdown() {
    plugin::Call<0x722710>();
}

// Modifies `posn`!!
void C3dMarkers::PlaceMarkerCone(uint32 id, CVector& posn, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate, uint8 bEnableCollision)
{
    plugin::Call<0x726D40, uint32, CVector&, float, uint8, uint8, uint8, uint8, uint16, float, int16, uint8>(id, posn, size, red, green, blue, alpha, pulsePeriod, pulseFraction, rotateRate, bEnableCollision);
}

// 0x725040
void C3dMarkers::Render() {
    plugin::Call<0x725040>();
}

// 0x5D42E0
bool C3dMarkers::LoadUser3dMarkers() {
    return plugin::CallAndReturn<bool, 0x5D42E0>();
}

// 0x5D4300
bool C3dMarkers::SaveUser3dMarkers() {
    return plugin::CallAndReturn<bool, 0x5D4300>();
}
