#include "StdInc.h"

#include "3dMarkers.h"

void C3dMarkers::InjectHooks() {
    using namespace ReversibleHooks;
    // RH_ScopedInstall(Init, 0x724E40);
    // RH_ScopedInstall(Update, 0x7227B0);
    // RH_ScopedInstall(Shutdown, 0x722710);
    // RH_ScopedInstall(Render, 0x725040);
    // RH_ScopedInstall(LoadUser3dMarkers, 0x5D42E0);
    // RH_ScopedInstall(SaveUser3dMarkers, 0x5D4300);
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
