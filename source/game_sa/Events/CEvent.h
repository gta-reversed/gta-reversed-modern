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

    static void* operator new(unsigned int size);
    static void operator delete(void* object);

    CEvent();
    virtual ~CEvent();
    virtual eEventType GetEventType() = 0;
    virtual int GetEventPriority() = 0;
    virtual int GetLifeTime() = 0;
    virtual CEvent* Clone() = 0;
    virtual bool AffectsPed(CPed* ped);
    virtual bool AffectsPedGroup(CPedGroup* pedGroup);
    virtual bool IsCriminalEvent();
    virtual void ReportCriminalEvent(CPed* ped);
    virtual bool HasEditableResponse();
    virtual CEntity* GetSourceEntity();
    virtual bool TakesPriorityOver(CEvent* refEvent);
    virtual float GetLocalSoundLevel();
    virtual bool DoInformVehicleOccupants(CPed* ped);
    virtual bool IsValid(CPed* ped);
    virtual bool CanBeInterruptedBySameEvent();
private:
    bool AffectsPed_Reversed(CPed* ped) { return true; };
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup) { return true; };
    bool IsCriminalEvent_Reversed() { return false; }
    void ReportCriminalEvent_Reversed(CPed* ped) { }; // empty
    bool HasEditableResponse_Reversed() { return false; }
    CEntity* GetSourceEntity_Reversed() { return nullptr; }
    bool TakesPriorityOver_Reversed(CEvent* refEvent) { return GetEventPriority() >= refEvent->GetEventPriority(); }
    float GetLocalSoundLevel_Reversed() { return 0.0f; }
    bool DoInformVehicleOccupants_Reversed(CPed* ped) { return false; }
    bool IsValid_Reversed(CPed* ped) { return m_bValid || m_nTimeActive <= GetLifeTime(); }
    bool CanBeInterruptedBySameEvent_Reversed() { return false; };
public:
    float GetSoundLevel(CEntity* entity, CVector& position);
    static float CalcSoundLevelIncrement(float level1, float level2);
};

VALIDATE_SIZE(CEvent, 0xC);
