#include "StdInc.h"

#include "EventVehicleDamageWeapon.h"

void CEventVehicleDamageWeapon::InjectHooks()
{
    RH_ScopedClass(CEventVehicleDamageWeapon);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x61C2E0);
    RH_ScopedVirtualInstall(CloneEditable, 0x61C330);
}

// 0x61C2E0
CEventVehicleDamageWeapon::CEventVehicleDamageWeapon(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType) :
    CEventVehicleDamage(vehicle, attacker, weaponType)
{
    // nothing here
}

CEventVehicleDamageWeapon* CEventVehicleDamageWeapon::Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType)
{
    this->CEventVehicleDamageWeapon::CEventVehicleDamageWeapon(vehicle, attacker, weaponType);
    return this;
}

// 0x61C330
CEventEditableResponse* CEventVehicleDamageWeapon::CloneEditable()
{
    return CEventVehicleDamageWeapon::CloneEditable_Reversed();
}

CEventEditableResponse* CEventVehicleDamageWeapon::CloneEditable_Reversed()
{
    return new CEventVehicleDamageWeapon(m_vehicle, m_attacker, m_weaponType);
}
