#include "StdInc.h"
#include "CExplosion.h"

void CExplosion::InjectHooks() {

    // Destructors
    // ReversibleHooks::Install("CExplosion", "", , &CExplosion::);

    // Static functions
    // ReversibleHooks::Install("CExplosion", "ClearAllExplosions", 0x736840, &CExplosion::ClearAllExplosions);
    // ReversibleHooks::Install("CExplosion", "Shutdown", 0x7368F0, &CExplosion::Shutdown);
    // ReversibleHooks::Install("CExplosion", "GetExplosionActiveCounter", 0x736900, &CExplosion::GetExplosionActiveCounter);
    // ReversibleHooks::Install("CExplosion", "ResetExplosionActiveCounter", 0x736910, &CExplosion::ResetExplosionActiveCounter);
    // ReversibleHooks::Install("CExplosion", "DoesExplosionMakeSound", 0x736920, &CExplosion::DoesExplosionMakeSound);
    // ReversibleHooks::Install("CExplosion", "GetExplosionType", 0x736930, &CExplosion::GetExplosionType);
    // ReversibleHooks::Install("CExplosion", "GetExplosionPosition", 0x736940, &CExplosion::GetExplosionPosition);
    // ReversibleHooks::Install("CExplosion", "TestForExplosionInArea", 0x736950, &CExplosion::TestForExplosionInArea);
    // ReversibleHooks::Install("CExplosion", "RemoveAllExplosionsInArea", 0x7369E0, &CExplosion::RemoveAllExplosionsInArea);
    // ReversibleHooks::Install("CExplosion", "Initialise", 0x736A40, &CExplosion::Initialise);
    // ReversibleHooks::Install("CExplosion", "AddExplosion", 0x736A50, &CExplosion::AddExplosion);
    // ReversibleHooks::Install("CExplosion", "Update", 0x737620, &CExplosion::Update);
}

// Static functions
// 0x736840
void CExplosion::ClearAllExplosions() {
    plugin::Call<0x736840>();
}

// 0x7368F0
void CExplosion::Shutdown() {
    plugin::Call<0x7368F0>();
}

// 0x736900
uint8_t CExplosion::GetExplosionActiveCounter(uint8_t id) {
    return plugin::CallAndReturn<uint8_t, 0x736900, uint8_t>(id);
}

// 0x736910
void CExplosion::ResetExplosionActiveCounter(uint8_t id) {
    plugin::Call<0x736910, uint8_t>(id);
}

// 0x736920
bool CExplosion::DoesExplosionMakeSound(uint8_t id) {
    return plugin::CallAndReturn<bool, 0x736920, uint8_t>(id);
}

// 0x736930
unsigned int CExplosion::GetExplosionType(uint8_t id) {
    return plugin::CallAndReturn<unsigned int, 0x736930, uint8_t>(id);
}

// 0x736940
CVector* CExplosion::GetExplosionPosition(uint8_t id) {
    return plugin::CallAndReturn<CVector*, 0x736940, uint8_t>(id);
}

// 0x736950
bool CExplosion::TestForExplosionInArea(eExplosionType type, float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    return plugin::CallAndReturn<bool, 0x736950, eExplosionType, float, float, float, float, float, float>(type, minX, maxX, minY, maxY, minZ, maxZ);
}

// 0x7369E0
void CExplosion::RemoveAllExplosionsInArea(CVector pos, float r) {
    plugin::Call<0x7369E0, CVector, float>(pos, r);
}

// 0x736A40
void CExplosion::Initialise() {
    plugin::Call<0x736A40>();
}

// 0x736A50
bool CExplosion::AddExplosion(CEntity* victim, CEntity* creator, eExplosionType explosionType, const CVector& posn, uint32 time, bool bMakeSound, float camShake, bool bHideExplosion) {
    return plugin::CallAndReturn<bool, 0x736A50, CEntity*, CEntity*, eExplosionType, const CVector&, uint32, bool, float, bool>(victim, creator, explosionType, posn, time, bMakeSound, camShake, bHideExplosion);
}

// 0x737620
void CExplosion::Update() {
    plugin::Call<0x737620>();
}
