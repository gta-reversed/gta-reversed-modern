#include "CEvent.h"

class CPed;

class CEventDeadPed : public CEventEditableResponse
{
    CPed* m_ped;
    bool field_18;
private:
    char padding[3];
public:
    std::uint32_t m_deathTimeInMs;

    static void InjectHooks();

    CEventDeadPed(CPed* ped, bool bUnknown, std::uint32_t deathTimeInMs);
    ~CEventDeadPed();
private:
    CEventDeadPed* Constructor(CPed* ped, bool bUnknown, std::uint32_t deathTimeInMs);
public:
    eEventType GetEventType() const override { return EVENT_DEAD_PED; }
    int32_t GetEventPriority() const override { return 15; }
    int GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_ped; }
    float GetLocalSoundLevel() override { return 60.0f; }
    CEventEditableResponse* CloneEditable() override;

    bool AffectsPed_Reversed(CPed* ped);
    CEventEditableResponse* CloneEditable_Reversed();
};

VALIDATE_SIZE(CEventDeadPed, 0x20);
