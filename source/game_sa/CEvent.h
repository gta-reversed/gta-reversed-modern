#pragma once
#include "PluginBase.h"

class CPed;
class CPedGroup;
class CEntity;

class CEvent 
{
public:
    static void* operator_new();

    virtual CEvent* DeletingDestructor(uint8_t deletingFlags);
    virtual CEvent* GetEventType();
    virtual int GetEventPriority();
    virtual int GetLifeTime();
    virtual CEvent* Clone();
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
    virtual CEvent* CloneEditable();
    // We don't know the last one. TODO..
    // virtual field_40;

};

VALIDATE_SIZE(CEvent, 0x4);
