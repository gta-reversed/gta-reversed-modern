#pragma once
#include "PluginBase.h"
#include "CEvent.h"
#include "CPedGroup.h"

class CPed;
class CEventGroupEvent : public CEvent
{
public:
    CPed* m_ped;
    CEvent* m_event;

    static void InjectHooks();

    CEventGroupEvent(CPed* ped, CEvent* event);
    ~CEventGroupEvent();
private:
    CEventGroupEvent* Constructor(CPed* ped, CEvent* event);
public:
    eEventType GetEventType() override { return EVENT_GROUP_EVENT; }
    int GetEventPriority() override { return 41; };
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override { return false; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override { return pedGroup->m_groupMembership.IsMember(m_ped); }
    float GetLocalSoundLevel() override { return 100.0f; }

    CEvent* Clone_Reversed();
    bool BaseEventTakesPriorityOverBaseEvent(CEventGroupEvent* other);
private:
    bool IsPriorityEvent();
};

VALIDATE_SIZE(CEventGroupEvent, 0x14);
