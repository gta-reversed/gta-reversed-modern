#include "CEventEditableResponse.h"

class CEntity;
class CVehicle;
enum eWeaponType : std::uint32_t;

class CEventVehicleDamage : public CEventEditableResponse
{
public:
    CVehicle* m_vehicle;
    CEntity* m_attacker;
    eWeaponType m_weaponType;

    static void InjectHooks();

    CEventVehicleDamage(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType);
    ~CEventVehicleDamage();
private:
    CEventVehicleDamage* Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType);
public:
    int GetEventPriority() override { return 49; }
    int GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool IsCriminalEvent() override;
    void ReportCriminalEvent(CPed* ped) override;
    CEntity* GetSourceEntity() override;
    float GetLocalSoundLevel() override { return 55.0f; }

    bool AffectsPed_Reversed(CPed* ped);
    bool IsCriminalEvent_Reversed();
    void ReportCriminalEvent_Reversed(CPed* ped);;
    CEntity* GetSourceEntity_Reversed();
};

VALIDATE_SIZE(CEventVehicleDamage, 0x20);
