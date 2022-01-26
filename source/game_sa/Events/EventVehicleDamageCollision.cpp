#include "StdInc.h"

void CEventVehicleDamageCollision::InjectHooks()
{
    ReversibleHooks::Install("CEventVehicleDamageCollision", "Constructor", 0x6A0620, &CEventVehicleDamageCollision::Constructor);
    ReversibleHooks::Install("CEventVehicleDamageCollision", "CloneEditable_Reversed", 0x6A0670, &CEventVehicleDamageCollision::CloneEditable_Reversed);
}

// 0x6A0620
CEventVehicleDamageCollision::CEventVehicleDamageCollision(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType) :
    CEventVehicleDamage(vehicle, attacker, weaponType)
{
    // empty
}

CEventVehicleDamageCollision* CEventVehicleDamageCollision::Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType)
{
    this->CEventVehicleDamageCollision::CEventVehicleDamageCollision(vehicle, attacker, weaponType);
    return this;
}

// 0x6A0670
CEventEditableResponse* CEventVehicleDamageCollision::CloneEditable()
{
    return CEventVehicleDamageCollision::CloneEditable_Reversed();
}

CEventEditableResponse* CEventVehicleDamageCollision::CloneEditable_Reversed()
{
    return new CEventVehicleDamageCollision(m_vehicle, m_attacker, m_weaponType);
}
