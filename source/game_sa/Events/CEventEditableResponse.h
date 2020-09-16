#pragma once
#include "CEvent.h"

class CEventEditableResponse : public CEvent {
public:
    bool m_bAddToEventGroup;
    bool field_D;
    short m_taskId;
    short field_10;
    unsigned short field_12;

    static void InjectHooks();

    CEventEditableResponse();
    ~CEventEditableResponse();
private:
    CEventEditableResponse* Constructor();
public:
    CEvent* Clone() override;
    bool HasEditableResponse() override;
    virtual CEventEditableResponse* CloneEditable() = 0;

    CEvent* Clone_Reversed();
    bool HasEditableResponse_Reversed() { return true; }

    bool WillRespond();
    void InformVehicleOccupants(CPed* ped);
    void InformRespectedFriends(CPed* ped);
    void InformGroup(CPed* ped);
    void TriggerLookAt(CPed* ped);
    void ComputeResponseTaskType(CPed* ped, bool bDecisionMakerTypeInGroup);
    void ComputeResponseTaskType(CPedGroup* pedGroup);
    bool ComputeResponseTaskOfType(CPed* ped, int taskId);
};

VALIDATE_SIZE(CEventEditableResponse, 0x14);

class CEventSpecial : public CEventEditableResponse {
public:

    static void InjectHooks();

    CEventSpecial() {}
    ~CEventSpecial() {}
private:
    CEventSpecial* Constructor();
public:
    eEventType GetEventType() override { return EVENT_SPECIAL; }
    std::int32_t GetEventPriority() override { return 52; }
    std::int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return true; }
    CEventSpecial* CloneEditable() override { return new CEventSpecial(); }
};

VALIDATE_SIZE(CEventSpecial, 0x14);

class CEventFireNearby : public CEventEditableResponse {
public:
    CVector m_position;

    static void InjectHooks();

    CEventFireNearby(CVector const& position);
    ~CEventFireNearby() {}
private:
    CEventFireNearby* Constructor(CVector const& position);
public:
    eEventType GetEventType() override { return EVENT_FIRE_NEARBY; }
    std::int32_t GetEventPriority() override { return 17; }
    std::int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(CEvent* refevent) override { return true; }
    CEventFireNearby* CloneEditable() override { return new CEventFireNearby(m_position); }

private:
    bool AffectsPed_Reversed(CPed* ped);
public:

};

VALIDATE_SIZE(CEventFireNearby, 0x20);
