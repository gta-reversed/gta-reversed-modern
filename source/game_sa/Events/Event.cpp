#include "StdInc.h"

#include "Event.h"

void CEvent::InjectHooks()
{
    RH_ScopedClass(CEvent);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4ABFC0);
    RH_ScopedInstall(CalcSoundLevelIncrement, 0x4AC050);
    RH_ScopedInstall(GetSoundLevel, 0x4B2850);
}

void CEventRevived::InjectHooks()
{
    RH_ScopedClass(CEventRevived);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AEC50);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4AECB0);
}

void CEventEscalator::InjectHooks()
{
    RH_ScopedClass(CEventEscalator);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x5FF820);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B2580);
}

void CEventSexyVehicle::InjectHooks()
{
    RH_ScopedClass(CEventSexyVehicle);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AF010);
}

void CEventChatPartner::InjectHooks()
{
    RH_ScopedClass(CEventChatPartner);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AECD0);
}

void CEventCopCarBeingStolen::InjectHooks()
{
    RH_ScopedClass(CEventCopCarBeingStolen);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1740);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B1860);
}

void CEventCarUpsideDown::InjectHooks()
{
    RH_ScopedClass(CEventCarUpsideDown);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1CC0);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B1DB0);
}

void CEventPassObject::InjectHooks()
{
    RH_ScopedClass(CEventPassObject);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x65DC70);
    RH_ScopedInstall(IsValid_Reversed, 0x4B1700);
}

void CEventLeanOnVehicle::InjectHooks()
{
    RH_ScopedClass(CEventLeanOnVehicle);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x65DAF0);
    RH_ScopedInstall(IsValid_Reversed, 0x4B16C0);
}

void CEventOnFire::InjectHooks()
{
    RH_ScopedClass(CEventOnFire);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x5FF740);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B1050);
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

// 0x4B2850
float CEvent::GetSoundLevel(CEntity* entity, CVector& position)
{
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
}

// 0x4AC050
float CEvent::CalcSoundLevelIncrement(float level1, float level2)
{
    if (level2 == 0.0f)
        return 0.0f;

    if (level1 == 0.0f)
        return level2;

    level1 = powf(10.0f, level1 * 0.1f);
    level2 = powf(10.0f, level2 * 0.1f);
    return log10f((level1 + level2) / level1) * 10.0f;
}

CEventRevived* CEventRevived::Constructor()
{
    this->CEventRevived::CEventRevived();
    return this;
}

// 0x4AECB0
bool CEventRevived::AffectsPed(CPed* ped)
{
    return CEventRevived::AffectsPed_Reversed(ped);
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

// 0x4B2580
bool CEventEscalator::AffectsPed(CPed* ped)
{
    return CEventEscalator::AffectsPed_Reversed(ped);
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

// 0x4B1860
bool CEventCopCarBeingStolen::AffectsPed(CPed* ped)
{
    return CEventCopCarBeingStolen::AffectsPed_Reversed(ped);
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

// 0x4B1DB0
bool CEventCarUpsideDown::AffectsPed(CPed* ped)
{
    return CEventCarUpsideDown::AffectsPed_Reversed(ped);
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

// 0x4B1700
bool CEventPassObject::IsValid(CPed* ped)
{
    return CEventPassObject::IsValid_Reversed(ped);
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

// 0x4B16C0
bool CEventLeanOnVehicle::IsValid(CPed* ped)
{
    return CEventLeanOnVehicle::IsValid_Reversed(ped);
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

// 0x4B1050
bool CEventOnFire::AffectsPed(CPed* ped)
{
    return CEventOnFire::AffectsPed_Reversed(ped);
}

bool CEventOnFire::AffectsPed_Reversed(CPed* ped)
{
    if (ped->m_pFire && !ped->physicalFlags.bFireProof) {
        CTask* activeTask = ped->GetTaskManager().GetActiveTask();
        if (activeTask && activeTask->GetTaskType() == TASK_COMPLEX_ON_FIRE)
            return false;

        CTask* partialAnimTask = ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
        if (partialAnimTask && partialAnimTask->GetTaskType() == TASK_SIMPLE_PLAYER_ON_FIRE)
            return false;

        return ped->IsAlive(); 
    }
    return false;
}
