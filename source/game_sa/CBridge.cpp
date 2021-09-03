#include "StdInc.h"

void CBridge::InjectHooks() {
//    ReversibleHooks::Install("CBridge", "Init", 0x41BC70, &CBridge::Init);
//    ReversibleHooks::Install("CBridge", "Update", 0x41BC80, &CBridge::Update);
//    ReversibleHooks::Install("CBridge", "FindBridgeEntities", 0x0, &CBridge::FindBridgeEntities);
//    ReversibleHooks::Install("CBridge", "ShouldLightsBeFlashing", 0x41BC90, &CBridge::ShouldLightsBeFlashing);
}

// 0x41BC70
void CBridge::Init() {
    plugin::Call<0x41BC70>();
}

// 0x41BC80
void CBridge::Update() {
    plugin::Call<0x41BC80>();
}

// 0x0
void CBridge::FindBridgeEntities() {
    plugin::Call<0x0>();
}

// 0x41BC90
bool CBridge::ShouldLightsBeFlashing() {
    return false;
}

// used in CPlayerInfo::Process
bool CBridge::ThisIsABridgeObjectMovingUp(uint32) {
    return false;
}
