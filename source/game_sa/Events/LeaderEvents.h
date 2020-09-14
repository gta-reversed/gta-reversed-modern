#pragma once
#include "CEventEditableResponse.h"

class CEventLeaderEnteredCarAsDriver : public CEventEditableResponse {
public:
    CVehicle* m_vehicle;

    static void InjectHooks();

    CEventLeaderEnteredCarAsDriver(CVehicle* vehicle);
    ~CEventLeaderEnteredCarAsDriver();
private:
    CEventLeaderEnteredCarAsDriver* Constructor(CVehicle* vehicle);
public:
    eEventType GetEventType() override { return EVENT_LEADER_ENTERED_CAR_AS_DRIVER; }
    std::int32_t GetEventPriority() override  { return 46; }
    std::int32_t GetLifeTime() override  { return 0; }
    bool AffectsPed(CPed* ped) override  { return false; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    bool TakesPriorityOver(CEvent* refEvent) override  { return true; }
    bool CanBeInterruptedBySameEvent() override  { return true; }
    CEventLeaderEnteredCarAsDriver* CloneEditable() override  { return new CEventLeaderEnteredCarAsDriver(m_vehicle); }

private:
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
public:

};

VALIDATE_SIZE(CEventLeaderEnteredCarAsDriver, 0x18);
