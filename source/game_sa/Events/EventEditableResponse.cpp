#include "StdInc.h"

#include "EventEditableResponse.h"

#include "PedType.h"
#include "IKChainManager_c.h"

void CEventEditableResponse::InjectHooks() {
    RH_ScopedClass(CEventEditableResponse);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AC450);
    RH_ScopedInstall(Clone_Reversed, 0x420ED0);
    RH_ScopedInstall(HasEditableResponse_Reversed, 0x420EF0);
    RH_ScopedInstall(WillRespond, 0x4AC490);
    RH_ScopedInstall(InformVehicleOccupants, 0x4AC4A0);
    RH_ScopedInstall(InformRespectedFriends, 0x4B2B00);
    RH_ScopedInstall(InformGroup, 0x4B7DF0);
    RH_ScopedInstall(TriggerLookAt, 0x4AC5A0);
    RH_ScopedOverloadedInstall(ComputeResponseTaskType, "ped", 0x4B56C0, void (CEventEditableResponse::*)(CPed * ped, bool));
    RH_ScopedOverloadedInstall(ComputeResponseTaskType, "group", 0x4B57A0, void (CEventEditableResponse::*)(CPedGroup*));
    RH_ScopedInstall(ComputeResponseTaskOfType, 0x4B5730);
}

void CEventSpecial::InjectHooks()
{
    RH_ScopedClass(CEventSpecial);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1AE0);
}

void CEventFireNearby::InjectHooks()
{
    RH_ScopedClass(CEventFireNearby);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1F10);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B1F90);
}

void CEventDanger::InjectHooks()
{
    RH_ScopedClass(CEventDanger);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B2600);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B5470);
    RH_ScopedInstall(AffectsPedGroup_Reversed, 0x4B54E0);
    RH_ScopedInstall(GetSourceEntity_Reversed, 0x4B2700);
}

void CEventSeenPanickedPed::InjectHooks()
{
    RH_ScopedClass(CEventSeenPanickedPed);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B2080);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B53C0);
}

// 0x4AC450
CEventEditableResponse::CEventEditableResponse() {
    m_bAddToEventGroup = true;
    m_taskId = TASK_NONE;
    field_10 = -1;
}

CEventEditableResponse::~CEventEditableResponse() {
    // nothing here
}

CEventEditableResponse* CEventEditableResponse::Constructor() {
    this->CEventEditableResponse::CEventEditableResponse();
    return this;
}

// 0x420ED0
CEvent* CEventEditableResponse::Clone() {
    return CEventEditableResponse::Clone_Reversed();
}

// 0x420EF0
bool CEventEditableResponse::HasEditableResponse() const {
    return CEventEditableResponse::HasEditableResponse_Reversed();
}

CEvent* CEventEditableResponse::Clone_Reversed() {
    CEventEditableResponse* clonedEvent = CloneEditable();
    clonedEvent->m_taskId = m_taskId;
    clonedEvent->field_10 = field_10;
    clonedEvent->m_bAddToEventGroup = m_bAddToEventGroup;
    return clonedEvent;
}


// 0x4AC490
bool CEventEditableResponse::WillRespond() {
    return m_taskId != TASK_NONE;
}

// 0x4AC4A0
void CEventEditableResponse::InformVehicleOccupants(CPed* ped) {
    CVehicle* vehicle = ped->m_pVehicle;
    if (ped->bInVehicle && DoInformVehicleOccupants(ped) && m_bAddToEventGroup) {
        CPed* driver = vehicle->m_pDriver;
        if (driver && driver != ped) {
            auto clonedEvent = static_cast<CEventEditableResponse*>(Clone());
            clonedEvent->m_taskId = TASK_NONE;
            clonedEvent->m_bAddToEventGroup = false;
            driver->m_pIntelligence->m_eventGroup.Add(clonedEvent, false);
            delete clonedEvent;
        }
        for (uint8 i = 0; i < vehicle->m_nMaxPassengers; i++) {
            CPed* pPassenger = vehicle->m_apPassengers[i];
            if (pPassenger && pPassenger != ped) {
                auto clonedEvent = static_cast<CEventEditableResponse*>(Clone());
                clonedEvent->m_taskId = TASK_NONE;
                clonedEvent->m_bAddToEventGroup = false;
                pPassenger->m_pIntelligence->m_eventGroup.Add(clonedEvent, false);
                delete clonedEvent;
            }
        }
    }
}

// 0x4B2B00
void CEventEditableResponse::InformRespectedFriends(CPed* ped) {
    if (!m_bAddToEventGroup)
        return;

    uint32 numPedsToScan = ped->m_pIntelligence->m_nDmNumPedsToScan;
    if (!numPedsToScan)
        return;

    CEntity** entities = ped->m_pIntelligence->m_entityScanner.m_apEntities;
    for (size_t entityIndex = 0; entityIndex < numPedsToScan; entityIndex++) {
        CEntity* entity = entities[entityIndex];
        if (!entity)
            continue;

        CPed* entityPed = entity->AsPed();
        if (entityPed->m_nPedType == PED_TYPE_COP) {
            if (entityPed->m_nPedType != PED_TYPE_COP)
                continue;

            CPlayerPedData * playerData = FindPlayerPed(0)->m_pPlayerData;
            if (playerData->m_pWanted && playerData->m_pWanted->m_nWantedLevel)
                continue;
        }
        else {
            uint32 pedAcquaintances = ped->m_acquaintance.GetAcquaintances(0);
            bool bFlagSet = pedAcquaintances & CPedType::GetPedFlag(entityPed->m_nPedType);
            if (entityPed->IsPlayer()) {
                uint32 entityAcquaintances = entityPed->m_acquaintance.GetAcquaintances(0);
                bFlagSet = entityAcquaintances & CPedType::GetPedFlag(ped->m_nPedType);
            }
            if (!bFlagSet)
                continue;
        }
        float fDmRadius = ped->m_pIntelligence->m_fDmRadius;
        CVector direction = ped->GetPosition() - entity->GetPosition();
        if (fDmRadius * fDmRadius > direction.SquaredMagnitude()) {
            auto clonedEvent = static_cast<CEventEditableResponse*>(Clone());
            clonedEvent->m_taskId = TASK_NONE;
            clonedEvent->m_bAddToEventGroup = false;
            if (!CInformFriendsEventQueue::Add(entity, clonedEvent))
                delete clonedEvent;
        }
    }
}

// 0x4B7DF0
void CEventEditableResponse::InformGroup(CPed* ped) {
    CPedGroup* pedGroup = CPedGroups::GetPedsGroup(ped);
    if (!pedGroup)
        return;

    auto clonedEvent = static_cast<CEventEditableResponse*>(Clone());
    clonedEvent->m_taskId = TASK_NONE;
    clonedEvent->m_bAddToEventGroup = false;
    if (!CInformGroupEventQueue::Add(ped, pedGroup, clonedEvent))
        delete clonedEvent;
}

// 0x4AC5A0
void CEventEditableResponse::TriggerLookAt(CPed* ped) {
    CEntity* sourceEntity = GetSourceEntity();
    if (sourceEntity) {
        if (sourceEntity->IsPed()) {
            g_ikChainMan.LookAt("CEventEditableResponse", ped, sourceEntity->AsPed(), 2000, BONE_HEAD, nullptr, true, 0.25f, 500, 3, false);
            return;
        }
        g_ikChainMan.LookAt("CEventEditableResponse", ped, sourceEntity, 2000, BONE_UNKNOWN, nullptr, true, 0.25f, 500, 3, false);
    }
}

// 0x4B56C0
void CEventEditableResponse::ComputeResponseTaskType(CPed* ped, bool bDecisionMakerTypeInGroup) {
    if (m_taskId == TASK_NONE) {
        int32 eventSourceType = CEventSource::ComputeEventSourceType(*this, *ped);
        CDecisionMakerTypes::GetInstance()->MakeDecision(ped, GetEventType(), eventSourceType, ped->bInVehicle,
            TASK_SIMPLE_INFORM_RESPECTED_FRIENDS, 
            TASK_SIMPLE_INFORM_GROUP, 
            TASK_SIMPLE_LOOK_AT_ENTITY_OR_COORD, 
            -1,
            bDecisionMakerTypeInGroup, &m_taskId, &field_10);
    }
}

// 0x4B57A0
void CEventEditableResponse::ComputeResponseTaskType(CPedGroup* pedGroup) {
    if (m_taskId == TASK_NONE) {
        CPed* pGroupLeader = pedGroup->m_groupMembership.GetLeader();
        CPed* pMember = pGroupLeader;
        if (pGroupLeader && pGroupLeader->IsPlayer())
            pMember = nullptr;
        if (!pMember){
            for (size_t memberId = 0; memberId < TOTAL_PED_GROUP_FOLLOWERS; memberId++) {
                pMember = pedGroup->m_groupMembership.GetMember(memberId);
                if (pMember)
                    break;
            }
        }
        if (pMember) {
            int32 eventSourceType = CEventSource::ComputeEventSourceType(*this, *pMember);
            m_taskId = CDecisionMakerTypes::GetInstance()->MakeDecision(pedGroup, GetEventType(), eventSourceType, pMember->bInVehicle,
                TASK_SIMPLE_INFORM_GROUP,
                TASK_SIMPLE_INFORM_RESPECTED_FRIENDS,
                TASK_SIMPLE_LOOK_AT_ENTITY_OR_COORD,
                -1);
        }
        else {
            m_taskId = TASK_NONE;
        }
        pGroupLeader = pedGroup->m_groupMembership.GetLeader();
        if (m_taskId == TASK_NONE && pGroupLeader) {
            if (pGroupLeader->IsPlayer()) {
                int32 eventSourceType = CEventSource::ComputeEventSourceType(*this, *pGroupLeader);
                m_taskId = CDecisionMakerTypes::GetInstance()->MakeDecision(pedGroup, GetEventType(), eventSourceType, pGroupLeader->bInVehicle,
                    TASK_SIMPLE_INFORM_GROUP,
                    TASK_SIMPLE_INFORM_RESPECTED_FRIENDS,
                    TASK_SIMPLE_LOOK_AT_ENTITY_OR_COORD,
                    -1);
            }
        }
    }
}

// 0x4B5730
bool CEventEditableResponse::ComputeResponseTaskOfType(CPed* ped, int32 taskId) {
    int16 outTaskId = -1;
    int16 unknownId = -1;
    int32 eventSourceType = CEventSource::ComputeEventSourceType(*this, *ped);
    CDecisionMakerTypes::GetInstance()->MakeDecision(ped, GetEventType(), eventSourceType, ped->bInVehicle,
        -1, -1, -1, taskId, false, &outTaskId, &unknownId);
    return taskId == outTaskId;
}

CEventSpecial* CEventSpecial::Constructor()
{
    this->CEventSpecial::CEventSpecial();
    return this;
}

CEventFireNearby::CEventFireNearby(const CVector& position)
{
    m_position = position;
}

CEventFireNearby* CEventFireNearby::Constructor(const CVector& position)
{
    this->CEventFireNearby::CEventFireNearby(position);
    return this;
}

// 0x4B1F90
bool CEventFireNearby::AffectsPed(CPed* ped)
{
    return CEventFireNearby::AffectsPed_Reversed(ped);
}

bool CEventFireNearby::AffectsPed_Reversed(CPed* ped)
{
    if (ped->GetTaskManager().Find<TASK_COMPLEX_EXTINGUISH_FIRES>())
        return false;
    return ped->IsAlive();
}


CEventDanger::CEventDanger(CEntity* dangerFrom, float dangerRadius)
{
    m_dangerFrom = dangerFrom;
    if (dangerFrom)
        dangerFrom->RegisterReference(reinterpret_cast<CEntity**>(&m_dangerFrom));
    m_dangerRadius = dangerRadius;
}

CEventDanger::~CEventDanger()
{
    if (m_dangerFrom)
        m_dangerFrom->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_dangerFrom));
}

CEventDanger* CEventDanger::Constructor(CEntity* dangerFrom, float dangerRadius)
{
    this->CEventDanger::CEventDanger(dangerFrom, dangerRadius);
    return this;
}

// 0x4B5470
bool CEventDanger::AffectsPed(CPed* ped)
{
    return CEventDanger::AffectsPed_Reversed(ped);
}

// 0x4B54E0
bool CEventDanger::AffectsPedGroup(CPedGroup* pedGroup)
{
    return CEventDanger::AffectsPedGroup_Reversed(pedGroup);
}

// 0x4B2700
CEntity* CEventDanger::GetSourceEntity() const
{
    return CEventDanger::GetSourceEntity_Reversed();
}

bool CEventDanger::AffectsPed_Reversed(CPed* ped)
{
    CVehicle* dangerFrom = static_cast<CVehicle*>(m_dangerFrom);
    if (dangerFrom && dangerFrom != ped->m_pVehicle) {
        CVector2D distance = ped->GetPosition() - dangerFrom->GetPosition();
        if (m_dangerRadius * m_dangerRadius >= distance.SquaredMagnitude())
            return ped->IsAlive();
    }
    return false;
}

bool CEventDanger::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    if (GetSourceEntity() && GetSourceEntity()->IsPed()) {
        CPed* leader = pedGroup->GetMembership().GetLeader();
        if (leader) {
            CVector2D distance = leader->GetPosition() - m_dangerFrom->GetPosition();
            return distance.SquaredMagnitude() <= m_dangerRadius * m_dangerRadius;
        }
    }
    return false;
}

CEntity* CEventDanger::GetSourceEntity_Reversed() const
{
    if (m_dangerFrom && !m_dangerFrom->IsPed() && m_dangerFrom->IsVehicle()) {
        CVehicle* vehicle = m_dangerFrom->AsVehicle();
        if (vehicle->m_pDriver)
            return vehicle->m_pDriver;
    }
    return m_dangerFrom;
}

CEventSeenPanickedPed::CEventSeenPanickedPed(CPed* ped)
{
    m_ped = ped;
    if (ped)
        ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventSeenPanickedPed::~CEventSeenPanickedPed()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventSeenPanickedPed* CEventSeenPanickedPed::Constructor(CPed* ped)
{
    this->CEventSeenPanickedPed::CEventSeenPanickedPed(ped);
    return this;
}

// 0x4B53C0
bool CEventSeenPanickedPed::AffectsPed(CPed* ped)
{
    return CEventSeenPanickedPed::AffectsPed_Reversed(ped);
}

bool CEventSeenPanickedPed::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->IsPlayer() && m_ped && m_ped != ped) {
        CEvent* currentEvent = m_ped->GetEventHandlerHistory().GetCurrentEvent();
        if (currentEvent && currentEvent->GetSourceEntity()) {
            CVector distance = ped->GetPosition() - m_ped->GetPosition();
            return distance.SquaredMagnitude() < 100.0f;
        }
    }
    return false;
}

