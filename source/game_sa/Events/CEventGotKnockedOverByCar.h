#include "CEventEditableResponse.h"
#include "CVehicle.h"

class CEventGotKnockedOverByCar : public CEventEditableResponse {
public:
    CVehicle* m_vehicle;

public:
    static void InjectHooks();

    CEventGotKnockedOverByCar(CVehicle* vehicle);
    ~CEventGotKnockedOverByCar();
private:
    CEventGotKnockedOverByCar* Constructor(CVehicle* vehicle);
public:
    eEventType GetEventType() const override { return EVENT_GOT_KNOCKED_OVER_BY_CAR; }
    int32_t GetEventPriority() const override { return 37; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_vehicle ? m_vehicle->m_pDriver : nullptr; }
    float GetLocalSoundLevel() override { return 55.0f; }
    CEventEditableResponse* CloneEditable() override;

    bool AffectsPed_Reversed(CPed* ped);
    CEventEditableResponse* CloneEditable_Reversed();
};

VALIDATE_SIZE(CEventGotKnockedOverByCar, 0x18);
