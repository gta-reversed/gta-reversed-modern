#include "StdInc.h"

#include "3dMarkers.h"

void C3dMarkers::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("C3dMarkers", "Init", 0x724E40, &C3dMarkers::Init);
    // Install("C3dMarkers", "Update", 0x7227B0, &C3dMarkers::Update);
    // Install("C3dMarkers", "Shutdown", 0x722710, &C3dMarkers::Shutdown);
    // Install("C3dMarkers", "Render", 0x725040, &C3dMarkers::Render);
    // Install("C3dMarkers", "LoadUser3dMarkers", 0x5D42E0, &C3dMarkers::LoadUser3dMarkers);
    // Install("C3dMarkers", "SaveUser3dMarkers", 0x5D4300, &C3dMarkers::SaveUser3dMarkers);
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
