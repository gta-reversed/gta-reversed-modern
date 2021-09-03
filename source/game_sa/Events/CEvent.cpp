#include "StdInc.h"

void CEvent::InjectHooks()
{
    ReversibleHooks::Install("CEvent", "CEvent", 0x4ABFC0, &CEvent::Constructor);
    ReversibleHooks::Install("CEvent", "CalcSoundLevelIncrement", 0x4AC050, &CEvent::CalcSoundLevelIncrement);
    ReversibleHooks::Install("CEvent", "GetSoundLevel", 0x4B2850, &CEvent::GetSoundLevel);
}

void CEventRevived::InjectHooks()
{
    ReversibleHooks::Install("CEventRevived", "CEventRevived", 0x4AEC50, &CEventRevived::Constructor);
    ReversibleHooks::Install("CEventRevived", "AffectsPed_Reversed", 0x4AECB0, &CEventRevived::AffectsPed_Reversed);
}

void CEventEscalator::InjectHooks()
{
    ReversibleHooks::Install("CEventEscalator", "CEventEscalator", 0x5FF820, &CEventEscalator::Constructor);
    ReversibleHooks::Install("CEventEscalator", "AffectsPed_Reversed", 0x4B2580, &CEventEscalator::AffectsPed_Reversed);
}

void CEventSexyVehicle::InjectHooks()
{
    ReversibleHooks::Install("CEventSexyVehicle", "CEventSexyVehicle", 0x4AF010, &CEventSexyVehicle::Constructor);
}

void CEventChatPartner::InjectHooks()
{
    ReversibleHooks::Install("CEventChatPartner", "CEventChatPartner", 0x4AECD0, &CEventChatPartner::Constructor);
}

void CEventCopCarBeingStolen::InjectHooks()
{
    ReversibleHooks::Install("CEventCopCarBeingStolen", "CEventCopCarBeingStolen", 0x4B1740, &CEventCopCarBeingStolen::Constructor);
    ReversibleHooks::Install("CEventCopCarBeingStolen", "AffectsPed_Reversed", 0x4B1860, &CEventCopCarBeingStolen::AffectsPed_Reversed);
}

void CEventCarUpsideDown::InjectHooks()
{
    ReversibleHooks::Install("CEventCarUpsideDown", "CEventCarUpsideDown", 0x4B1CC0, &CEventCarUpsideDown::Constructor);
    ReversibleHooks::Install("CEventCarUpsideDown", "AffectsPed_Reversed", 0x4B1DB0, &CEventCarUpsideDown::AffectsPed_Reversed);
}

void CEventPassObject::InjectHooks()
{
    ReversibleHooks::Install("CEventPassObject", "CEventPassObject", 0x65DC70, &CEventPassObject::Constructor);
    ReversibleHooks::Install("CEventPassObject", "IsValid_Reversed", 0x4B1700, &CEventPassObject::IsValid_Reversed);
}

void CEventLeanOnVehicle::InjectHooks()
{
    ReversibleHooks::Install("CEventLeanOnVehicle", "CEventLeanOnVehicle", 0x65DAF0, &CEventLeanOnVehicle::Constructor);
    ReversibleHooks::Install("CEventLeanOnVehicle", "IsValid_Reversed", 0x4B16C0, &CEventLeanOnVehicle::IsValid_Reversed);
}

void CEventOnFire::InjectHooks()
{
    ReversibleHooks::Install("CEventOnFire", "CEventOnFire", 0x5FF740, &CEventOnFire::Constructor);
    ReversibleHooks::Install("CEventOnFire", "AffectsPed_Reversed", 0x4B1050, &CEventOnFire::AffectsPed_Reversed);
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
        int32 modelId = ped->m_pContactEntity->m_nModelIndex;
        if (modelId == ModelIndices::MI_ESCALATORSTEP || modelId == ModelIndices::MI_ESCALATORSTEP8)
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

CEventCarUpsideDown::CEventCarUpsideDown(CVehicle* vehicle)
{
    m_vehicle = vehicle;
    if (vehicle)
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventCarUpsideDown::~CEventCarUpsideDown()
{
    if (m_vehicle) // BUG: This should be CEntity::CleanUpOldReference
        m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventCarUpsideDown* CEventCarUpsideDown::Constructor(CVehicle* vehicle)
{
    this->CEventCarUpsideDown::CEventCarUpsideDown(vehicle);
    return this;
}

bool CEventCarUpsideDown::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1DB0, CEventCarUpsideDown*, CPed*>(this, ped);
#else
    return CEventCarUpsideDown::AffectsPed_Reversed(ped);
#endif
}

bool CEventCarUpsideDown::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->IsPlayer()
        && ped->bGetOutUpsideDownCar
        && ped->bInVehicle
        && (ped->m_nCreatedBy != PED_MISSION || ped->m_pVehicle && !ped->m_pVehicle->IsBoat())
        && !ped->m_pVehicle->IsBike() && !ped->m_pVehicle->IsQuad())
    {
        return ped->IsAlive();
    }
    return false;
}

CEventPassObject::CEventPassObject(CEntity* giver, bool dontPassObject)
{
    m_giver = giver;
    if (giver)
        giver->RegisterReference(&m_giver);
    m_dontPassObject = dontPassObject;
}

CEventPassObject::~CEventPassObject()
{
    if (m_giver)
        m_giver->CleanUpOldReference(&m_giver);
}

CEventPassObject* CEventPassObject::Constructor(CEntity* giver, bool dontPassObject)
{
    this->CEventPassObject::CEventPassObject(giver, dontPassObject);
    return this;
}

bool CEventPassObject::IsValid(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1700, CEventPassObject*, CPed*>(this, ped);
#else
    return CEventPassObject::IsValid_Reversed(ped);
#endif
}

bool CEventPassObject::IsValid_Reversed(CPed* ped)
{
    if (ped)
        return ped->IsAlive();
    if (CEvent::IsValid(ped))
        return true;
    return false;
}

CEventLeanOnVehicle::CEventLeanOnVehicle(CVehicle* vehicle, int32 leanAnimDurationInMs)
{
    m_vehicle = vehicle;
    m_leanAnimDurationInMs = leanAnimDurationInMs;
    if (vehicle)
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventLeanOnVehicle::~CEventLeanOnVehicle()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventLeanOnVehicle* CEventLeanOnVehicle::Constructor(CVehicle* vehicle, int32 leanAnimDurationInMs)
{
    this->CEventLeanOnVehicle::CEventLeanOnVehicle(vehicle, leanAnimDurationInMs);
    return this;
}

bool CEventLeanOnVehicle::IsValid(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B16C0, CEventLeanOnVehicle*, CPed*>(this, ped);
#else
    return CEventLeanOnVehicle::IsValid_Reversed(ped);
#endif
}

bool CEventLeanOnVehicle::IsValid_Reversed(CPed* ped)
{
    if (ped)
        return ped->IsAlive();
    if (CEvent::IsValid(ped))
        return true;
    return false;
}

CEventOnFire* CEventOnFire::Constructor()
{
    this->CEventOnFire::CEventOnFire();
    return this;
}

bool CEventOnFire::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1050, CEventOnFire*, CPed*>(this, ped);
#else
    return CEventOnFire::AffectsPed_Reversed(ped);
#endif
}

bool CEventOnFire::AffectsPed_Reversed(CPed* ped)
{
    if (ped->m_pFire && !ped->physicalFlags.bFireProof) {
        CTask* activeTask = ped->GetTaskManager().GetActiveTask();
        if (activeTask && activeTask->GetId() == TASK_COMPLEX_ON_FIRE)
            return false;
        CTask* partialAnimTask = ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
        if (partialAnimTask && partialAnimTask->GetId() == TASK_SIMPLE_PLAYER_ON_FIRE)
            return false;
        return ped->IsAlive(); 
    }
    return false;
}
