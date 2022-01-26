#include "StdInc.h"

void CEventVehicleDamageCollision::InjectHooks()
{
    RH_ScopedClass(CEventVehicleDamageCollision);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x6A0620);
    RH_ScopedInstall(CloneEditable_Reversed, 0x6A0670);
}

CEventVehicleDamageCollision::CEventVehicleDamageCollision(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType) :
    CEventVehicleDamage(vehicle, attacker, weaponType)
{
    // empty
}

CEventVehicleDamageCollision* CEventVehicleDamageCollision::Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventVehicleDamageCollision*, 0x6A0620, CEvent*, CVehicle*, CEntity*, eWeaponType>(this, vehicle, attacker, weaponType);
#else
    this->CEventVehicleDamageCollision::CEventVehicleDamageCollision(vehicle, attacker, weaponType);
    return this;
#endif
}

CEventEditableResponse* CEventVehicleDamageCollision::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x6A0670, CEvent*>(this);
#else
    return CEventVehicleDamageCollision::CloneEditable_Reversed();
#endif
}

CEventEditableResponse* CEventVehicleDamageCollision::CloneEditable_Reversed()
{
    return new CEventVehicleDamageCollision(m_vehicle, m_attacker, m_weaponType);
}
