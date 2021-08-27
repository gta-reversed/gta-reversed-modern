#include "CEventEditableResponse.h"
#include "CPed.h"
#include "common.h"
#include "CPedGroup.h"

class CVehicle;

class CEventDraggedOutCar : public CEventEditableResponse
{
public:
    CPed* m_carjacker;
    CVehicle* m_vehicle;
    bool m_IsDriverSeat;
private:
    char padding[3];
public:

    static void InjectHooks();

    CEventDraggedOutCar(CVehicle* vehicle, CPed* carjacker, bool IsDriverSeat);
    ~CEventDraggedOutCar();
private:
    CEventDraggedOutCar* Constructor(CVehicle* vehicle, CPed* carjacker, bool IsDriverSeat);
public:
    eEventType GetEventType() const override { return EVENT_DRAGGED_OUT_CAR; }
    int32_t GetEventPriority() const override { return 40; }
    int GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return ped->IsAlive() && m_carjacker; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override { return FindPlayerPed(-1) == pedGroup->m_groupMembership.GetLeader(); }
    CEntity* GetSourceEntity() const override { return m_carjacker; }
    float GetLocalSoundLevel() override { return 100.0f; }
    CEventEditableResponse* CloneEditable() override;

    CEventEditableResponse* CloneEditable_Reversed();
};

VALIDATE_SIZE(CEventDraggedOutCar, 0x20);
