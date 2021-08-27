#pragma once 
#include "CEventVehicleDamage.h"

class CEventVehicleDamageWeapon : public CEventVehicleDamage
{
public:

    static void InjectHooks();

    CEventVehicleDamageWeapon(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType);
    ~CEventVehicleDamageWeapon();
private:
    CEventVehicleDamageWeapon* Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType);
public:
    eEventType GetEventType() const override { return EVENT_VEHICLE_DAMAGE_WEAPON; }
    CEventEditableResponse* CloneEditable() override;
    CEventEditableResponse* CloneEditable_Reversed();
};

VALIDATE_SIZE(CEventVehicleDamageWeapon, 0x20);
