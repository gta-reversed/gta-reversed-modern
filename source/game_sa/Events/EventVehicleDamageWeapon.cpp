#include "StdInc.h"

void CEventVehicleDamageWeapon::InjectHooks()
{
    RH_ScopedInstall(Constructor, 0x61C2E0);
    RH_ScopedInstall(CloneEditable_Reversed, 0x61C330);
}

CEventVehicleDamageWeapon::CEventVehicleDamageWeapon(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType) :
    CEventVehicleDamage(vehicle, attacker, weaponType)
{
    // nothing here
}

CEventVehicleDamageWeapon::~CEventVehicleDamageWeapon()
{
    // nothing here
}

CEventVehicleDamageWeapon* CEventVehicleDamageWeapon::Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventVehicleDamageWeapon*, 0x61C2E0, CEvent*, CVehicle*, CEntity*, eWeaponType>
        (this, vehicle, attacker, weaponType);
#else
    this->CEventVehicleDamageWeapon::CEventVehicleDamageWeapon(vehicle, attacker, weaponType);
    return this;
#endif
}

CEventEditableResponse* CEventVehicleDamageWeapon::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x61C330, CEvent*>(this);
#else
    return CEventVehicleDamageWeapon::CloneEditable_Reversed();
#endif
}

CEventEditableResponse* CEventVehicleDamageWeapon::CloneEditable_Reversed()
{
    return new CEventVehicleDamageWeapon(m_vehicle, m_attacker, m_weaponType);
}
