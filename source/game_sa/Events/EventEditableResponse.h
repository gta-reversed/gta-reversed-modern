#pragma once

#include "Event.h"

class CEventEditableResponse : public CEvent {
public:
    bool   m_bAddToEventGroup;
    bool   field_D;
    int16  m_taskId; // see eTaskType
    int16  field_10;
    uint16 field_12;

public:
    CEventEditableResponse();
    ~CEventEditableResponse() override = default; // 0x4AC480

    CEvent* Clone() override;
    bool HasEditableResponse() const override;
    virtual CEventEditableResponse* CloneEditable() = 0;

    bool WillRespond() const;
    void InformVehicleOccupants(CPed* ped);
    void InformRespectedFriends(CPed* ped);
    void InformGroup(CPed* ped);
    void TriggerLookAt(CPed* ped);
    void ComputeResponseTaskType(CPed* ped, bool bDecisionMakerTypeInGroup);
    void ComputeResponseTaskType(CPedGroup* pedGroup);
    bool ComputeResponseTaskOfType(CPed* ped, int32 taskId);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CEventEditableResponse* Constructor();
    CEvent* Clone_Reversed();
    bool HasEditableResponse_Reversed() const { return true; }
};

VALIDATE_SIZE(CEventEditableResponse, 0x14);

class CEventSpecial : public CEventEditableResponse {
public:
    CEventSpecial() = default; // 0x4B1AE0
    ~CEventSpecial() override = default; // 0x4B6750 ?

    eEventType GetEventType() const override { return EVENT_SPECIAL; }
    int32 GetEventPriority() const override { return 52; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return true; }
    CEventSpecial* CloneEditable() override { return new CEventSpecial(); }

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CEventSpecial* Constructor();
};

VALIDATE_SIZE(CEventSpecial, 0x14);

class CEventFireNearby : public CEventEditableResponse {
public:
    CVector m_position;

public:
    explicit CEventFireNearby(const CVector& position);
    ~CEventFireNearby() override = default; // 0x4B1F80

    eEventType GetEventType() const override { return EVENT_FIRE_NEARBY; }
    int32 GetEventPriority() const override { return 17; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(const CEvent& refevent) override { return true; }
    CEventFireNearby* CloneEditable() override { return new CEventFireNearby(m_position); }

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CEventFireNearby* Constructor(const CVector& position);
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventFireNearby, 0x20);

class CEventDanger : public CEventEditableResponse {
public:
    CEntity* m_dangerFrom;
    float m_dangerRadius;

public:
    CEventDanger(CEntity* dangerFrom, float dangerRadius);
    ~CEventDanger() override;

    eEventType GetEventType() const override { return EVENT_DANGER; }
    int32 GetEventPriority() const override { return 20; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEntity* GetSourceEntity() const override;
    CEventDanger* CloneEditable() override { return new CEventDanger(m_dangerFrom, m_dangerRadius); }

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CEventDanger* Constructor(CEntity* dangerFrom, float dangerRadius);
    bool AffectsPed_Reversed(CPed* ped);
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
    CEntity* GetSourceEntity_Reversed() const;
};

VALIDATE_SIZE(CEventDanger, 0x1C);

class CEventSeenPanickedPed : public CEventEditableResponse {
public:
    CPed* m_ped;

public:
    explicit CEventSeenPanickedPed(CPed* ped);
    ~CEventSeenPanickedPed() override;

    eEventType GetEventType() const override { return EVENT_SEEN_PANICKED_PED; }
    int32 GetEventPriority() const override { return 13; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_ped;}
    CEventSeenPanickedPed* CloneEditable() override { return new CEventSeenPanickedPed(m_ped); }

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CEventSeenPanickedPed* Constructor(CPed* ped);
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventSeenPanickedPed, 0x18);
