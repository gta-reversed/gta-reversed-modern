#include "StdInc.h"

void CMovingThings::InjectHooks() {
//    ReversibleHooks::Install("CMovingThings", "Init", 0x717D00, &CMovingThings::Init);
//    ReversibleHooks::Install("CMovingThings", "Shutdown", 0x717C20, &CMovingThings::Shutdown);
//    ReversibleHooks::Install("CMovingThings", "Update", 0x7185B0, &CMovingThings::Update);
//    ReversibleHooks::Install("CMovingThings", "Render", 0x717150, &CMovingThings::Render);
//    ReversibleHooks::Install("CMovingThings", "Render_BeforeClouds", 0x7178F0, &CMovingThings::Render_BeforeClouds);
}

// 0x717D00
void CMovingThings::Init() {
    plugin::Call<0x717D00>();
}

// 0x717C20
void CMovingThings::Shutdown() {
    plugin::Call<0x717C20>();
}

// 0x7185B0
void CMovingThings::Update() {
    plugin::Call<0x7185B0>();
}

// 0x717150
void CMovingThings::Render() {
    plugin::Call<0x717150>();
}

// 0x7178F0
void CMovingThings::Render_BeforeClouds() {
    plugin::Call<0x7178F0>();
}
