#include "StdInc.h"

void CBridge::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CBridge", "Init", 0x41BC70, &CBridge::Init);
    Install("CBridge", "Update", 0x41BC80, &CBridge::Update);
    Install("CBridge", "FindBridgeEntities", 0x41BCA0, &CBridge::FindBridgeEntities);
    Install("CBridge", "ShouldLightsBeFlashing", 0x41BC90, &CBridge::ShouldLightsBeFlashing);
}

// 0x41BC70
void CBridge::Init() {
    // NOP
}

// 0x41BC80
void CBridge::Update() {
    // NOP
}

// used in CEntity::ProcessLightsForEntity
// always false
// 0x41BC90
bool CBridge::ShouldLightsBeFlashing() {
    return false;
}

// 0x41BCA0
void CBridge::FindBridgeEntities() {
    // NOP
}

// used in CPlayerInfo::Process
// 0x41BCB0
bool CBridge::ThisIsABridgeObjectMovingUp(uint32) {
    return false;
}
