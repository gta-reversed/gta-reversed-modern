#pragma once

#include "CEvent.h"
#include "CPedGroup.h"

class CPed;

class CEventGroupEvent : public CEvent {
public:
    CPed*   m_ped;
    CEvent* m_event;

public:
    CEventGroupEvent(CPed* ped, CEvent* event);
    ~CEventGroupEvent();

    eEventType GetEventType() const override {
        return EVENT_GROUP_EVENT;
    }
    int32_t GetEventPriority() const override {
        return 41;
    };
    int GetLifeTime() override {
        return 0;
    }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override {
        return false;
    }
    bool AffectsPedGroup(CPedGroup* pedGroup) override {
        return pedGroup->m_groupMembership.IsMember(m_ped);
    }
    float GetLocalSoundLevel() override {
        return 100.0f;
    }

    CEvent* Clone_Reversed();
    bool BaseEventTakesPriorityOverBaseEvent(const CEventGroupEvent& other);

private:
    bool IsPriorityEvent() const;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventGroupEvent* Constructor(CPed* ped, CEvent* event);
};

VALIDATE_SIZE(CEventGroupEvent, 0x14);
