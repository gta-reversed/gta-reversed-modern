#pragma once

#include "eEventType.h"
#include "Ped.h"

class CPed;
class CPedGroup;
class CEntity;
enum eEventType;

class CEvent {
public:
    int32 m_nTimeActive;
    bool  m_bValid;
    bool  field_9;
    bool  field_A;
    bool  field_B;

public:
    static void* operator new(uint32 size) {
        return ((CEvent * (__cdecl*)(uint32))0x4B5620)(size);
    }

    static void operator delete(void* object) {
        ((void(__cdecl*)(void*))0x4B5630)(object);
    }

    CEvent();

    virtual ~CEvent();
    virtual eEventType GetEventType() const = 0;
    virtual int32 GetEventPriority() const = 0;
    virtual int32 GetLifeTime() = 0;
    virtual CEvent* Clone() = 0;
    virtual bool AffectsPed(CPed* ped) { return true; };
    virtual bool AffectsPedGroup(CPedGroup* pedGroup) { return true; };
    virtual bool IsCriminalEvent() { return false; }
    virtual void ReportCriminalEvent(CPed* ped) { }; // empty
    virtual bool HasEditableResponse() const { return false; }
    virtual CEntity* GetSourceEntity() const { return nullptr; }
    virtual bool TakesPriorityOver(const CEvent& refEvent) { return GetEventPriority() >= refEvent.GetEventPriority(); }
    virtual float GetLocalSoundLevel() { return 0.0f; }
    virtual bool DoInformVehicleOccupants(CPed* ped) { return false; }
    virtual bool IsValid(CPed* ped) { return m_bValid || m_nTimeActive <= GetLifeTime(); }
    virtual bool CanBeInterruptedBySameEvent() { return false; };

public:
    float GetSoundLevel(CEntity* entity, CVector& position);
    static float CalcSoundLevelIncrement(float level1, float level2);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEvent* Constructor();
};

VALIDATE_SIZE(CEvent, 0xC);

class CEventRevived : public CEvent {
public:
    CEventRevived() {}
    ~CEventRevived() {}

    eEventType GetEventType() const override { return EVENT_REVIVE; }
    int32 GetEventPriority() const override { return 74; }
    int32 GetLifeTime() override { return 0; }
    CEventRevived* Clone() override { return new CEventRevived(); }
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventRevived* Constructor();

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventRevived, 0xC);

class CEventEscalator : public CEvent {
public:
    CEventEscalator() {}
    ~CEventEscalator() override = default;

    eEventType GetEventType() const override { return EVENT_ON_ESCALATOR; }
    int32 GetEventPriority() const override { return 56; }
    int32 GetLifeTime() override { return 0; }
    CEventEscalator* Clone() override { return new CEventEscalator(); }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(const CEvent& refEvent) override { return GetEventType() != refEvent.GetEventType(); }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventEscalator* Constructor();

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventEscalator, 0xC);

class CEventSexyVehicle : public CEvent {
public:
    CVehicle* m_vehicle;

public:
    CEventSexyVehicle(CVehicle* vehicle);
    ~CEventSexyVehicle() override;

    eEventType GetEventType() const override { return EVENT_SEXY_VEHICLE; }
    int32 GetEventPriority() const override { return 3; }
    int32 GetLifeTime() override { return 0; }
    CEventSexyVehicle* Clone() override { return new CEventSexyVehicle(m_vehicle); }
    bool AffectsPed(CPed* ped) override { return ped->IsAlive() && m_vehicle; }


private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventSexyVehicle* Constructor(CVehicle* vehicle);
};

VALIDATE_SIZE(CEventSexyVehicle, 0x10);

class CEventChatPartner : public CEvent {
public:
    bool  m_leadSpeaker;
    char  _pad[3];
    CPed* m_partner;

public:
    CEventChatPartner(bool leadSpeaker, CPed* partner);
    ~CEventChatPartner() override;

    eEventType GetEventType() const override { return EVENT_CHAT_PARTNER; }
    int32 GetEventPriority() const override { return 5; }
    int32 GetLifeTime() override { return 0; }
    CEventChatPartner* Clone() override { return new CEventChatPartner(m_leadSpeaker, m_partner); }
    bool AffectsPed(CPed* ped)  override { return ped->IsAlive() && m_partner; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventChatPartner* Constructor(bool leadSpeaker, CPed* partner);
};

VALIDATE_SIZE(CEventChatPartner, 0x14);

class CEventCopCarBeingStolen : public CEvent {
public:
    CPed* m_hijacker;
    CVehicle* m_vehicle;

public:
    CEventCopCarBeingStolen(CPed* hijacker, CVehicle* vehicle);
    ~CEventCopCarBeingStolen() override;

    eEventType GetEventType() const override { return EVENT_COP_CAR_BEING_STOLEN; }
    int32 GetEventPriority() const override { return 38; }
    int32 GetLifeTime() override { return 0; }
    CEventCopCarBeingStolen* Clone() override { return new CEventCopCarBeingStolen(m_hijacker, m_vehicle); }
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventCopCarBeingStolen* Constructor(CPed* hijacker, CVehicle* vehicle);

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventCopCarBeingStolen, 0x14);

class CEventCarUpsideDown : public CEvent {
public:
    CVehicle* m_vehicle;

public:
    CEventCarUpsideDown(CVehicle* vehicle);
    ~CEventCarUpsideDown() override;

    eEventType GetEventType() const override { return EVENT_CAR_UPSIDE_DOWN; }
    int32 GetEventPriority() const override { return 18; }
    int32 GetLifeTime() override { return 0; }
    CEventCarUpsideDown* Clone() override { return new CEventCarUpsideDown(m_vehicle); }
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventCarUpsideDown* Constructor(CVehicle* vehicle);
    CEventCarUpsideDown* Destructor();

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventCarUpsideDown, 0x10);

class CEntity;

class CEventPassObject : public CEvent {
public:
    CEntity* m_giver;
    bool     m_dontPassObject;

public:
    CEventPassObject(CEntity* giver, bool dontPassObject);
    ~CEventPassObject() override;

    eEventType GetEventType() const override { return EVENT_PASS_OBJECT; }
    int32 GetEventPriority() const override { return 11; }
    int32 GetLifeTime() override { return 0; }
    CEventPassObject* Clone() override { return new CEventPassObject(m_giver, m_dontPassObject); }
    bool AffectsPed(CPed* ped) override { return true; }
    bool IsValid(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventPassObject* Constructor(CEntity* giver, bool dontPassObject);
    CEventPassObject* Destructor();

    bool IsValid_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPassObject, 0x14);

class CEventLeanOnVehicle : public CEvent {
public:
    CVehicle* m_vehicle;
    int32 m_leanAnimDurationInMs;

public:
    CEventLeanOnVehicle(CVehicle* vehicle, int32 leanAnimDurationInMs);
    ~CEventLeanOnVehicle() override;

    eEventType GetEventType() const override { return EVENT_LEAN_ON_VEHICLE; }
    int32 GetEventPriority() const override { return 12; }
    int32 GetLifeTime() override { return 0; }
    CEventLeanOnVehicle* Clone() override { return new CEventLeanOnVehicle(m_vehicle, m_leanAnimDurationInMs); }
    bool AffectsPed(CPed* ped) override { return true; }
    bool IsValid(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventLeanOnVehicle* Constructor(CVehicle* vehicle, int32 leanAnimDurationInMs);

    bool IsValid_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventLeanOnVehicle, 0x14);

class CEventOnFire : public CEvent {
public:
    CEventOnFire() = default;
    ~CEventOnFire() override = default;

    eEventType GetEventType() const override { return EVENT_ON_FIRE; }
    int32 GetEventPriority() const override { return 66; }
    int32 GetLifeTime() override { return 0; }
    CEventOnFire* Clone() override { return new CEventOnFire(); }
    bool AffectsPed(CPed* ped) override;
    float GetLocalSoundLevel() override { return 60.0f; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventOnFire* Constructor();

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventOnFire, 0xC);



