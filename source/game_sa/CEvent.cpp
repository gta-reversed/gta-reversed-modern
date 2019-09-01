#include "StdInc.h"

void* CEvent::operator_new()
{
    return plugin::CallAndReturn<void*, 0x4B5620>();
}

CEvent* CEvent::DeletingDestructor(uint8_t deletingFlags)
{
    return ((CEvent * (__thiscall*)(CEvent*, uint8_t))plugin::GetVMT(this, 0))(this, deletingFlags);
}

CEvent* CEvent::GetEventType()
{
    return ((CEvent * (__thiscall*)(CEvent*))plugin::GetVMT(this, 1))(this);
}

int CEvent::GetEventPriority()
{
    return (( int(__thiscall*)(CEvent*))plugin::GetVMT(this, 2))(this);
}

int CEvent::GetLifeTime()
{
    return ((int (__thiscall*)(CEvent*))plugin::GetVMT(this, 3))(this);
}

CEvent* CEvent::Clone()
{
    return ((CEvent * (__thiscall*)(CEvent*))plugin::GetVMT(this, 4))(this);
}

bool CEvent::AffectsPed(CPed* ped)
{
    return ((bool (__thiscall*)(CEvent*, CPed*))plugin::GetVMT(this, 5))(this, ped);
}

bool CEvent::AffectsPedGroup(CPedGroup* pedGroup)
{
    return ((bool(__thiscall*)(CEvent*, CPedGroup*))plugin::GetVMT(this, 6))(this, pedGroup);
}

bool CEvent::IsCriminalEvent()
{
    return ((bool(__thiscall*)(CEvent*))plugin::GetVMT(this, 7))(this);
}

void CEvent::ReportCriminalEvent(CPed* ped)
{
    return ((void(__thiscall*)(CEvent*, CPed*))plugin::GetVMT(this, 8))(this, ped);
}

bool CEvent::HasEditableResponse()
{
    return ((bool(__thiscall*)(CEvent*))plugin::GetVMT(this, 9))(this);
}

CEntity* CEvent::GetSourceEntity()
{
    return ((CEntity * (__thiscall*)(CEvent*))plugin::GetVMT(this, 10))(this);
}

bool CEvent::TakesPriorityOver(CEvent* refEvent)
{
    return ((bool(__thiscall*)(CEvent*, CEvent*))plugin::GetVMT(this, 11))(this, refEvent);
}

float CEvent::GetLocalSoundLevel()
{
    return ((bool(__thiscall*)(CEvent*))plugin::GetVMT(this, 12))(this);
}


bool CEvent::DoInformVehicleOccupants(CPed* ped)
{
    return ((bool(__thiscall*)(CEvent*, CPed*))plugin::GetVMT(this, 13))(this, ped);
}

bool CEvent::IsValid(CPed* ped)
{
    return ((bool(__thiscall*)(CEvent*, CPed*))plugin::GetVMT(this, 14))(this, ped);
}

bool CEvent::CanBeInterruptedBySameEvent()
{
    return ((bool(__thiscall*)(CEvent*))plugin::GetVMT(this, 15))(this);
}

CEvent* CEvent::CloneEditable()
{
    return ((CEvent * (__thiscall*)(CEvent*))plugin::GetVMT(this, 16))(this);
}

