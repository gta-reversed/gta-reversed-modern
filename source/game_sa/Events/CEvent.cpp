#include "StdInc.h"

void CEvent::InjectHooks()
{
    HookInstall(0x4ABFC0, &CEvent::Constructor);
    HookInstall(0x4AC050, &CEvent::CalcSoundLevelIncrement);
    HookInstall(0x4B2850, &CEvent::GetSoundLevel);
}

void CEventRevived::InjectHooks()
{
    HookInstall(0x4AEC50, &CEventRevived::Constructor);
    HookInstall(0x4AECB0, &CEventRevived::AffectsPed_Reversed);
}

void CEventEscalator::InjectHooks()
{
    HookInstall(0x5FF820, &CEventEscalator::Constructor);
    HookInstall(0x4B2580, &CEventEscalator::AffectsPed_Reversed);
}

void CEventSexyVehicle::InjectHooks()
{
    HookInstall(0x4AF010, &CEventSexyVehicle::Constructor);
}

void CEventChatPartner::InjectHooks()
{
    HookInstall(0x4AECD0, &CEventChatPartner::Constructor);
}

void CEventCopCarBeingStolen::InjectHooks()
{
    HookInstall(0x4B1740, &CEventCopCarBeingStolen::Constructor);
    HookInstall(0x4B1860, &CEventCopCarBeingStolen::AffectsPed_Reversed);
}

CEvent::CEvent() {
    m_nTimeActive = 0;
    m_bValid = false;
}

CEvent::~CEvent() {
    // nothing here
}

CEvent* CEvent::Constructor()
{
    this->CEvent::CEvent();
    return this;
}

float CEvent::GetSoundLevel(CEntity* entity, CVector& position)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<float, 0x4B2850, CEvent*, CEntity*, CVector&>(this, entity, position);
#else
    if ((entity && entity != GetSourceEntity()) || GetLocalSoundLevel() == 0.0f)
        return 0.0f;

    float level = 1000.0f;
    if (GetEventType() == EVENT_SOUND_QUIET) {
        CVector& sourcePos = static_cast<CEventSoundQuiet*>(this)->m_position;
        level = std::min((position - sourcePos).Magnitude(), 1.0f);
    }
    else if (GetSourceEntity()) {
        CVector& sourcePos = GetSourceEntity()->GetPosition();
        level = std::min((position - sourcePos).Magnitude(), 1.0f);
    }
    return (GetLocalSoundLevel() - (log10f(level * level) * 10.0f)) - (level / 100.0f);
#endif
}

float CEvent::CalcSoundLevelIncrement(float level1, float level2)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<float, 0x4AC050, float, float>(level1, level2);
#else
    if (level2 == 0.0f)
        return 0.0f;
    if (level1 == 0.0f)
        return level2;
    level1 = powf(10.0f, level1 * 0.1f);
    level2 = powf(10.0f, level2 * 0.1f);
    return log10f((level1 + level2) / level1) * 10.0f;
#endif
}

CEventRevived* CEventRevived::Constructor()
{
    this->CEventRevived::CEventRevived();
    return this;
}

bool CEventRevived::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AECB0, CEventRevived*, CPed*>(this, ped);
#else
    return CEventRevived::AffectsPed_Reversed(ped);
#endif
}

bool CEventRevived::AffectsPed_Reversed(CPed* ped)
{
    if (ped->m_nCreatedBy == PED_MISSION)
        return false;
    return !ped->IsAlive();
}

CEventEscalator* CEventEscalator::Constructor()
{
    this->CEventEscalator::CEventEscalator();
    return this;
}

bool CEventEscalator::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B2580, CEventEscalator*, CPed*>(this, ped);
#else
    return CEventEscalator::AffectsPed_Reversed(ped);
#endif
}

bool CEventEscalator::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && !ped->IsPlayer() && ped->m_pContactEntity) {
        std::int32_t modelId = ped->m_pContactEntity->m_nModelIndex;
        if (modelId == MI_ESCALATORSTEP || modelId == MI_ESCALATORSTEP8)
            return true;
    }
    return false;
}

CEventSexyVehicle::CEventSexyVehicle(CVehicle* vehicle)
{
    m_vehicle = vehicle;
    if (vehicle)
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventSexyVehicle::~CEventSexyVehicle()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventSexyVehicle* CEventSexyVehicle::Constructor(CVehicle* vehicle)
{
    this->CEventSexyVehicle::CEventSexyVehicle(vehicle);
    return this;
}

CEventChatPartner::CEventChatPartner(bool leadSpeaker, CPed* partner)
{
    m_leadSpeaker = leadSpeaker;
    m_partner = partner;
    if (partner)
        partner->RegisterReference(reinterpret_cast<CEntity**>(&m_partner));
}

CEventChatPartner::~CEventChatPartner()
{
    if (m_partner)
        m_partner->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_partner));
}

CEventChatPartner* CEventChatPartner::Constructor(bool leadSpeaker, CPed* partner)
{
    this->CEventChatPartner::CEventChatPartner(leadSpeaker, partner);
    return this;
}

CEventCopCarBeingStolen::CEventCopCarBeingStolen(CPed* hijacker, CVehicle* vehicle)
{
    m_hijacker = hijacker;
    m_vehicle = vehicle;
    if (hijacker)
        hijacker->RegisterReference(reinterpret_cast<CEntity**>(&m_hijacker));
    if (vehicle)
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventCopCarBeingStolen::~CEventCopCarBeingStolen()
{
    if (m_hijacker)
        m_hijacker->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_hijacker));
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventCopCarBeingStolen* CEventCopCarBeingStolen::Constructor(CPed* hijacker, CVehicle* vehicle)
{
    this->CEventCopCarBeingStolen::CEventCopCarBeingStolen(hijacker, vehicle);
    return this;
}

bool CEventCopCarBeingStolen::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1860, CEventCopCarBeingStolen*, CPed*>(this, ped);
#else
    return CEventCopCarBeingStolen::AffectsPed_Reversed(ped);
#endif
}

bool CEventCopCarBeingStolen::AffectsPed_Reversed(CPed* ped)
{
    if (m_hijacker && m_vehicle && m_hijacker->IsAlive() && ped->IsAlive() && ped->m_nPedType == PED_TYPE_COP) {
        if (m_vehicle == ped->m_pVehicle && ped->bInVehicle)
            return true;
    }
    return false;
}

