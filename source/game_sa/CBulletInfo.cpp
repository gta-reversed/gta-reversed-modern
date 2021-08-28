#include "StdInc.h"
#include "CBulletInfo.h"

void CBulletInfo::InjectHooks() {

    // Destructors
    // ReversibleHooks::Install("CBulletInfo", "", , &CBulletInfo::);

    // Static functions
    // ReversibleHooks::Install("CBulletInfo", "Initialise", 0x735FD0, &CBulletInfo::Initialise);
    // ReversibleHooks::Install("CBulletInfo", "Shutdown", 0x736000, &CBulletInfo::Shutdown);
    // ReversibleHooks::Install("CBulletInfo", "AddBullet", 0x736010, &CBulletInfo::AddBullet);
    // ReversibleHooks::Install("CBulletInfo", "Update", 0x7360D0, &CBulletInfo::Update);
}

// Static functions
// 0x735FD0
void CBulletInfo::Initialise() {
    plugin::Call<0x735FD0>();
}

// 0x736000
void CBulletInfo::Shutdown() {
    plugin::Call<0x736000>();
}

// 0x736010
bool CBulletInfo::AddBullet(CEntity* creator, eWeaponType weaponType, CVector pos, CVector velocity) {
    return plugin::CallAndReturn<int8_t, 0x736010, CEntity*, eWeaponType, CVector, CVector>(creator, weaponType, pos, velocity);
}

// 0x7360D0
void CBulletInfo::Update() {
    plugin::Call<0x7360D0>();
}
