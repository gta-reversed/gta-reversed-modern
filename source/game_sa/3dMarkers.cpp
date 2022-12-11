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

// 0x725BA0
void C3dMarkers::PlaceMarkerSet(uint32 id, uint16 type, const CVector& posn, float size, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction, int16 rotateRate) {
    return plugin::CallAndReturn<void, 0x725BA0>(id, type, &posn, size, r, g, b, a, pulsePeriod, pulseFraction, rotateRate);
}
