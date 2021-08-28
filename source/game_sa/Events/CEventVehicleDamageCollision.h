#include "CEventVehicleDamage.h"

class CEventVehicleDamageCollision : public CEventVehicleDamage
{
public:
    static void InjectHooks();

    CEventVehicleDamageCollision(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType);
    ~CEventVehicleDamageCollision() {}
private:
    CEventVehicleDamageCollision* Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType);
public:
    eEventType GetEventType() override { return EVENT_VEHICLE_DAMAGE_COLLISION; }
    CEventEditableResponse* CloneEditable() override;

    CEventEditableResponse* CloneEditable_Reversed();
};
