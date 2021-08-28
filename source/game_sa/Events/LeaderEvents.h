#pragma once
#include "CEventEditableResponse.h"
#include "CPedGroup.h"

class CEventLeaderEnteredCarAsDriver : public CEventEditableResponse {
public:
    CVehicle* m_vehicle;

    static void InjectHooks();

    CEventLeaderEnteredCarAsDriver(CVehicle* vehicle);
    ~CEventLeaderEnteredCarAsDriver();
private:
    CEventLeaderEnteredCarAsDriver* Constructor(CVehicle* vehicle);
public:
    eEventType GetEventType() const override { return EVENT_LEADER_ENTERED_CAR_AS_DRIVER; }
    int32_t GetEventPriority() const override  { return 46; }
    std::int32_t GetLifeTime() override  { return 0; }
    bool AffectsPed(CPed* ped) override  { return false; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    bool TakesPriorityOver(const CEvent& refEvent) override  { return true; }
    bool CanBeInterruptedBySameEvent() override  { return true; }
    CEventLeaderEnteredCarAsDriver* CloneEditable() override  { return new CEventLeaderEnteredCarAsDriver(m_vehicle); }

private:
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
public:

};

VALIDATE_SIZE(CEventLeaderEnteredCarAsDriver, 0x18);

class CEventLeaderExitedCarAsDriver : public CEventEditableResponse {
public:
    static void InjectHooks();

    CEventLeaderExitedCarAsDriver() {}
    ~CEventLeaderExitedCarAsDriver() {}
private:
    CEventLeaderExitedCarAsDriver* Constructor();
public:
    eEventType GetEventType() const override { return EVENT_LEADER_EXITED_CAR_AS_DRIVER; }
    int32_t GetEventPriority() const override { return 47; }
    std::int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return false; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }
    CEventLeaderExitedCarAsDriver* CloneEditable() override { return new CEventLeaderExitedCarAsDriver(); }
private:
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
};

VALIDATE_SIZE(CEventLeaderExitedCarAsDriver, 0x14);

class CEventLeaderQuitEnteringCarAsDriver : public CEvent {
public:
    static void InjectHooks();

    CEventLeaderQuitEnteringCarAsDriver() {}
    ~CEventLeaderQuitEnteringCarAsDriver() {}
private:
    CEventLeaderQuitEnteringCarAsDriver* Constructor();
public:
    eEventType GetEventType() const override { return EVENT_LEADER_QUIT_ENTERING_CAR_AS_DRIVER; }
    int32_t GetEventPriority() const override { return 48; }
    std::int32_t GetLifeTime() override { return 0; }
    CEventLeaderQuitEnteringCarAsDriver* Clone() override { return new CEventLeaderQuitEnteringCarAsDriver(); }
    bool AffectsPed(CPed* ped) override { return false; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }

private:
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
};

VALIDATE_SIZE(CEventLeaderQuitEnteringCarAsDriver, 0xC);

class CEventAreaCodes : public CEvent {
public:
    CPed* m_ped;

    static void InjectHooks();

    CEventAreaCodes(CPed* ped);
    ~CEventAreaCodes();
private:
    CEventAreaCodes* Constructor(CPed* ped);
public:
    eEventType GetEventType() const override { return EVENT_AREA_CODES; }
    int32_t GetEventPriority() const override { return 55; }
    std::int32_t GetLifeTime() override { return 0; }
    CEventAreaCodes* Clone() override { return new CEventAreaCodes(m_ped); }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(const CEvent& refEvent) override;
private:
    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
};

VALIDATE_SIZE(CEventAreaCodes, 0x10);

class CEventLeaderEntryExit : public CEventAreaCodes {
public:
    static void InjectHooks();

    CEventLeaderEntryExit(CPed* ped) : CEventAreaCodes(ped) {}
    ~CEventLeaderEntryExit() {}
private:
    CEventLeaderEntryExit* Constructor(CPed* ped);
public:
    eEventType GetEventType() const override { return EVENT_LEADER_ENTRY_EXIT; }
    std::int32_t GetLifeTime() override { return 0; }
    CEventLeaderEntryExit* Clone() override { return new CEventLeaderEntryExit(m_ped); }
    bool AffectsPedGroup(CPedGroup* pedGroup) override { return m_ped && pedGroup->GetMembership().GetLeader() == m_ped; }
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }
    bool CanBeInterruptedBySameEvent() override { return true; }
};

VALIDATE_SIZE(CEventLeaderEntryExit, 0x10);
