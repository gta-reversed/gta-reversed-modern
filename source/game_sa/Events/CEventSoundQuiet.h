#pragma once
#include "CEventEditableResponse.h"
#include "CVector.h"

class CEventSoundQuiet : public CEventEditableResponse
{
public:
    CEntity* m_entity;
    float m_fLocalSoundLevel;
    std::uint32_t m_startTimeInMs;
    CVector m_position;

    static void InjectHooks();

    CEventSoundQuiet(CEntity* entity, float fLocalSoundLevel, std::uint32_t startTime, CVector& position);
    ~CEventSoundQuiet();
private:
    CEventSoundQuiet* Constructor(CEntity* entity, float fLocalSoundLevel, std::uint32_t startTime, CVector& position);
public:
    eEventType GetEventType() override { return EVENT_SOUND_QUIET; }
    int GetEventPriority() override { return 8; }
    int GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() override { return m_entity; }
    float GetLocalSoundLevel() override { return m_fLocalSoundLevel; }
    bool CanBeInterruptedBySameEvent() override { return true; }
    CEventEditableResponse* CloneEditable() override;

    bool AffectsPed_Reversed(CPed* ped);
    CEventEditableResponse* CloneEditable_Reversed();
};
