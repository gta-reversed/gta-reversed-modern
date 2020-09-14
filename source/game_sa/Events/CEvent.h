#pragma once
#include "PluginBase.h"
#include "eEventType.h"

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
