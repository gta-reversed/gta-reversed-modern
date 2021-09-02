#pragma once

#include "CEventEditableResponse.h"
#include "CVector.h"

class CEventSoundQuiet : public CEventEditableResponse {
public:
    CEntity* m_entity;
    float    m_fLocalSoundLevel;
    uint32   m_startTimeInMs;
    CVector  m_position;

    static void InjectHooks();

    CEventSoundQuiet(CEntity* entity, float fLocalSoundLevel, uint32 startTime, CVector& position);
    ~CEventSoundQuiet();
private:
    CEventSoundQuiet* Constructor(CEntity* entity, float fLocalSoundLevel, uint32 startTime, CVector& position);
public:
    eEventType GetEventType() const override { return EVENT_SOUND_QUIET; }
    int32_t GetEventPriority() const override { return 8; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_entity; }
    float GetLocalSoundLevel() override { return m_fLocalSoundLevel; }
    bool CanBeInterruptedBySameEvent() override { return true; }
    CEventEditableResponse* CloneEditable() override;

    bool AffectsPed_Reversed(CPed* ped);
    CEventEditableResponse* CloneEditable_Reversed();
};
