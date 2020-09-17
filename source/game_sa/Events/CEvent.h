#pragma once
#include "PluginBase.h"
#include "eEventType.h"
#include "CPed.h"

class CPed;
class CPedGroup;
class CEntity;
enum eEventType;

class CEvent {
public:
    int m_nTimeActive;
    bool m_bValid;
    bool field_9;
    bool field_A;
    bool field_B;

    static void* CEvent::operator new(unsigned int size)
    {
        return ((CEvent * (__cdecl*)(unsigned int))0x4B5620)(size);
    }

    static void CEvent::operator delete(void* object)
    {
        ((void(__cdecl*)(void*))0x4B5630)(object);
    }

    static void InjectHooks();

private:
    CEvent* Constructor();
public:
    CEvent();
    virtual ~CEvent();
    virtual eEventType GetEventType() = 0;
    virtual int GetEventPriority() = 0;
    virtual int GetLifeTime() = 0;
    virtual CEvent* Clone() = 0;
    virtual bool AffectsPed(CPed* ped) { return true; };
    virtual bool AffectsPedGroup(CPedGroup* pedGroup) { return true; };
    virtual bool IsCriminalEvent() { return false; }
    virtual void ReportCriminalEvent(CPed* ped) { }; // empty
    virtual bool HasEditableResponse() { return false; }
    virtual CEntity* GetSourceEntity() { return nullptr; }
    virtual bool TakesPriorityOver(CEvent* refEvent) { return GetEventPriority() >= refEvent->GetEventPriority(); }
    virtual float GetLocalSoundLevel() { return 0.0f; }
    virtual bool DoInformVehicleOccupants(CPed* ped) { return false; }
    virtual bool IsValid(CPed* ped) { return m_bValid || m_nTimeActive <= GetLifeTime(); }
    virtual bool CanBeInterruptedBySameEvent() { return false; };
public:
    float GetSoundLevel(CEntity* entity, CVector& position);
    static float CalcSoundLevelIncrement(float level1, float level2);
};

VALIDATE_SIZE(CEvent, 0xC);

class CEventRevived : public CEvent {
public:
    static void InjectHooks();

    CEventRevived() {}
    ~CEventRevived() {}
    CEventRevived* Constructor();
    eEventType GetEventType() override { return EVENT_REVIVE; }
    std::int32_t GetEventPriority() override { return 74; }
    std::int32_t GetLifeTime() override { return 0; }
    CEventRevived* Clone() override { return new CEventRevived(); }
    bool AffectsPed(CPed* ped) override;
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventRevived, 0xC);

class CEventEscalator : public CEvent {
public:
    static void InjectHooks();

    CEventEscalator() {}
    ~CEventEscalator() {}
private:
    CEventEscalator* Constructor();
public:
    eEventType GetEventType() override { return EVENT_ON_ESCALATOR; }
    std::int32_t GetEventPriority() override { return 56; }
    std::int32_t GetLifeTime() override { return 0; }
    CEventEscalator* Clone() override { return new CEventEscalator(); }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(CEvent* refEvent) override { return GetEventType() != refEvent->GetEventType(); }
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventEscalator, 0xC);

class CEventSexyVehicle : public CEvent {
public:
    CVehicle* m_vehicle;

    static void InjectHooks();

    CEventSexyVehicle(CVehicle* vehicle);
    ~CEventSexyVehicle();
private:
    CEventSexyVehicle* Constructor(CVehicle* vehicle);
public:
    eEventType GetEventType() override { return EVENT_SEXY_VEHICLE; }
    std::int32_t GetEventPriority() override { return 3; }
    std::int32_t GetLifeTime() override { return 0; }
    CEventSexyVehicle* Clone() override { return new CEventSexyVehicle(m_vehicle); }
    bool AffectsPed(CPed* ped) override { return ped->IsAlive() && m_vehicle; }
};

VALIDATE_SIZE(CEventSexyVehicle, 0x10);

class CEventChatPartner : public CEvent {
public:
    bool m_leadSpeaker;
    std::int8_t padding[3];
    CPed* m_partner;

    static void InjectHooks();

    CEventChatPartner(bool leadSpeaker, CPed* partner);
    ~CEventChatPartner();
private:
    CEventChatPartner* Constructor(bool leadSpeaker, CPed* partner);
public:
    eEventType GetEventType() override { return EVENT_CHAT_PARTNER; }
    std::int32_t GetEventPriority() override { return 5; }
    std::int32_t GetLifeTime() override { return 0; }
    CEventChatPartner* Clone() override { return new CEventChatPartner(m_leadSpeaker, m_partner); }
    bool AffectsPed(CPed* ped) override { return ped->IsAlive() && m_partner; }

};

VALIDATE_SIZE(CEventChatPartner, 0x14);

class CEventCopCarBeingStolen : public CEvent {
public:
    CPed* m_hijacker;
    CVehicle* m_vehicle;

    static void InjectHooks();

    CEventCopCarBeingStolen(CPed* hijacker, CVehicle* vehicle);
    ~CEventCopCarBeingStolen();
private:
    CEventCopCarBeingStolen* Constructor(CPed* hijacker, CVehicle* vehicle);
public:
    eEventType GetEventType() override { return EVENT_COP_CAR_BEING_STOLEN; }
    std::int32_t GetEventPriority() override { return 38; }
    std::int32_t GetLifeTime() override { return 0; }
    CEventCopCarBeingStolen* Clone() override { return new CEventCopCarBeingStolen(m_hijacker, m_vehicle); }
    bool AffectsPed(CPed* ped) override;
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventCopCarBeingStolen, 0x14);
