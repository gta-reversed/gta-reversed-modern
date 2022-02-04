#pragma once

#include "EventVehicleDamage.h"

class CEventVehicleDamageCollision : public CEventVehicleDamage {
public:
    CEventVehicleDamageCollision(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType);
    ~CEventVehicleDamageCollision() override = default;

    eEventType GetEventType() const override { return EVENT_VEHICLE_DAMAGE_COLLISION; }
    CEventEditableResponse* CloneEditable() override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventVehicleDamageCollision* Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType);

    CEventEditableResponse* CloneEditable_Reversed();
};
