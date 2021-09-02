#include "StdInc.h"
#include "CProjectileInfo.h"

void CProjectileInfo::InjectHooks() {

    // Destructors
    // ReversibleHooks::Install("CProjectileInfo", "", , &CProjectileInfo::);

    // Static functions
    // ReversibleHooks::Install("CProjectileInfo", "Initialise", 0x737B40, &CProjectileInfo::Initialise);
    // ReversibleHooks::Install("CProjectileInfo", "Shutdown", 0x737BC0, &CProjectileInfo::Shutdown);
    // ReversibleHooks::Install("CProjectileInfo", "GetProjectileInfo", 0x737BF0, &CProjectileInfo::GetProjectileInfo);
    // ReversibleHooks::Install("CProjectileInfo", "RemoveNotAdd", 0x737C00, &CProjectileInfo::RemoveNotAdd);
    // ReversibleHooks::Install("CProjectileInfo", "AddProjectile", 0x737C80, &CProjectileInfo::AddProjectile);
    // ReversibleHooks::Install("CProjectileInfo", "RemoveDetonatorProjectiles", 0x738860, &CProjectileInfo::RemoveDetonatorProjectiles);
    // ReversibleHooks::Install("CProjectileInfo", "RemoveProjectile", 0x7388F0, &CProjectileInfo::RemoveProjectile);
    // ReversibleHooks::Install("CProjectileInfo", "Update", 0x738B20, &CProjectileInfo::Update);
    // ReversibleHooks::Install("CProjectileInfo", "IsProjectileInRange", 0x739860, &CProjectileInfo::IsProjectileInRange);
    // ReversibleHooks::Install("CProjectileInfo", "RemoveAllProjectiles", 0x7399B0, &CProjectileInfo::RemoveAllProjectiles);
    // ReversibleHooks::Install("CProjectileInfo", "RemoveIfThisIsAProjectile", 0x739A40, &CProjectileInfo::RemoveIfThisIsAProjectile);

    // Methods
    // ReversibleHooks::Install("CProjectileInfo", "RemoveFXSystem", 0x737B80, &CProjectileInfo::RemoveFXSystem);
}

// Static functions
// 0x737B40
void CProjectileInfo::Initialise() {
    plugin::Call<0x737B40>();
}

// 0x737BC0
void CProjectileInfo::Shutdown() {
    plugin::Call<0x737BC0>();
}

// 0x737BF0
CProjectileInfo* CProjectileInfo::GetProjectileInfo(int32_t infoId) {
    return plugin::CallAndReturn<CProjectileInfo*, 0x737BF0, int32_t>(infoId);
}

// 0x737C00
void CProjectileInfo::RemoveNotAdd(CEntity* creator, eWeaponType weaponType, CVector pos) {
    plugin::Call<0x737C00, CEntity*, eWeaponType, CVector>(creator, weaponType, pos);
}

// 0x737C80
bool CProjectileInfo::AddProjectile(CEntity* creator, eWeaponType WeponType, CVector src, float force, CVector* dest, CEntity* victim) {
    return plugin::CallAndReturn<bool, 0x737C80, CEntity*, eWeaponType, CVector, float, CVector*, CEntity*>(creator, WeponType, src, force, dest, victim);
}

// 0x738860
void CProjectileInfo::RemoveDetonatorProjectiles() {
    plugin::Call<0x738860>();
}

// 0x7388F0
void CProjectileInfo::RemoveProjectile(CProjectileInfo* info, CProjectile* object) {
    plugin::Call<0x7388F0, CProjectileInfo*, CProjectile*>(info, object);
}

// 0x738B20
void CProjectileInfo::Update() {
    return plugin::Call<0x738B20>();
}

// 0x739860
bool CProjectileInfo::IsProjectileInRange(float x1, float x2, float y1, float y2, float z1, float z2, bool bDestroy) {
    return plugin::CallAndReturn<bool, 0x739860, float, float, float, float, float, float, bool>(x1, x2, y1, y2, z1, z2, bDestroy);
}

// 0x7399B0
void CProjectileInfo::RemoveAllProjectiles() {
    plugin::Call<0x7399B0>();
}

// 0x739A40
bool CProjectileInfo::RemoveIfThisIsAProjectile(CObject* object) {
    return plugin::CallAndReturn<bool, 0x739A40, CObject*>(object);
}

// Methods
// 0x737B80
void CProjectileInfo::RemoveFXSystem(uint8 bInstantly) {
    plugin::CallMethod<0x737B80, uint8>(bInstantly);
}

// Virtual methods
