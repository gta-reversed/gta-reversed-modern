#include "StdInc.h"

void* CEvent::operator new(unsigned int size)
{
    return ((CEvent * (__cdecl*)(unsigned int))0x4B5620)(size);
}

void CEvent::operator delete(void* object)
{
    ((void(__cdecl*)(void*))0x4B5630)(object);
}


CEvent::CEvent() {
    m_nTimeActive = 0;
    m_bValid = false;
}

CEvent::~CEvent() {
    // nothing here
}

bool CEvent::AffectsPed(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool (__thiscall*)(CEvent*, CPed*))0x4ABFE0)(this, ped);
#else
    return CEvent::AffectsPed_Reversed(ped);
#endif
}

bool CEvent::AffectsPedGroup(CPedGroup* pedGroup) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*, CPedGroup*))0x4ABFF0)(this, pedGroup);
#else
    return CEvent::AffectsPedGroup_Reversed(pedGroup);
#endif
}

bool CEvent::IsCriminalEvent() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*))0x420E90)(this);
#else
return CEvent::IsCriminalEvent_Reversed();
#endif
}

void CEvent::ReportCriminalEvent(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((void(__thiscall*)(CEvent*, CPed*))0x420EA0)(this, ped);
#else
return CEvent::ReportCriminalEvent_Reversed(ped);
#endif
}

bool CEvent::HasEditableResponse() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*))0x43E1E0)(this);
#else
return CEvent::HasEditableResponse_Reversed();
#endif
}

CEntity* CEvent::GetSourceEntity() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CEntity * (__thiscall*)(CEvent*))0x43E1F0)(this);
#else
return CEvent::GetSourceEntity_Reversed();
#endif
}

bool CEvent::TakesPriorityOver(CEvent* refEvent) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*, CEvent*))0x4ABC30)(this, refEvent);
#else
return CEvent::TakesPriorityOver_Reversed(refEvent);
#endif
}

float CEvent::GetLocalSoundLevel() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*))0x420EB0)(this);
#else
return CEvent::GetLocalSoundLevel_Reversed();
#endif
}


bool CEvent::DoInformVehicleOccupants(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*, CPed*))0x420EC0)(this, ped);
#else
return CEvent::DoInformVehicleOccupants_Reversed(ped);
#endif
}

bool CEvent::IsValid(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*, CPed*))0x4AC020)(this, ped);
#else
return CEvent::IsValid_Reversed(ped);
#endif
}

bool CEvent::CanBeInterruptedBySameEvent() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*))0x4AC000)(this);
#else
return CEvent::CanBeInterruptedBySameEvent_Reversed();
#endif
}