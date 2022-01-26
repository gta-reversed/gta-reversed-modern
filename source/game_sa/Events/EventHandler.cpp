#include "StdInc.h"

#include "EventHandler.h"

#include "TaskSimpleStandStill.h"
#include "TaskComplexInAirAndLand.h"
#include "TaskComplexStuckInAir.h"

void CEventHandler::InjectHooks() {
    using namespace ReversibleHooks;

    Install("CEventHandler", "Flush", 0x4C3790, &CEventHandler::Flush);
    Install("CEventHandler", "FlushImmediately", 0x4C3820, &CEventHandler::FlushImmediately);
    // Install("CEventHandler", "GetCurrentEventType", 0x4B8CC0, &CEventHandler::GetCurrentEventType);
    // Install("CEventHandler", "HandleEvents", 0x4C3F10, &CEventHandler::HandleEvents);
    // Install("CEventHandler", "IsKillTaskAppropriate", 0x4BC3E0, &CEventHandler::IsKillTaskAppropriate);
    Install("CEventHandler", "IsTemporaryEvent", 0x4BC370, &CEventHandler::IsTemporaryEvent);
    // Install("CEventHandler", "RecordActiveEvent", 0x0, &CEventHandler::RecordActiveEvent);
    // Install("CEventHandler", "RecordPassiveEvent", 0x0, &CEventHandler::RecordPassiveEvent);
    // Install("CEventHandler", "RegisterKill", 0x4B9340, &CEventHandler::RegisterKill);
    // Install("CEventHandler", "SetEventResponseTask", 0x4BC600, &CEventHandler::SetEventResponseTask);
    /*
    Install("CEventHandler", "ComputeAreaCodesResponse", 0x4BBF50, &CEventHandler::ComputeAreaCodesResponse);
    Install("CEventHandler", "ComputeAttractorResponse", 0x4B9BE0, &CEventHandler::ComputeAttractorResponse);
    Install("CEventHandler", "ComputeBuildingCollisionPassiveResponse", 0x0, &CEventHandler::ComputeBuildingCollisionPassiveResponse);
    Install("CEventHandler", "ComputeBuildingCollisionResponse", 0x4BF2B0, &CEventHandler::ComputeBuildingCollisionResponse);
    Install("CEventHandler", "ComputeCarUpsideDownResponse", 0x4BBC30, &CEventHandler::ComputeCarUpsideDownResponse);
    Install("CEventHandler", "ComputeChatPartnerResponse", 0x4B98E0, &CEventHandler::ComputeChatPartnerResponse);
    Install("CEventHandler", "ComputeCopCarBeingStolenResponse", 0x4BB740, &CEventHandler::ComputeCopCarBeingStolenResponse);
    Install("CEventHandler", "ComputeCreatePartnerTaskResponse", 0x4BB130, &CEventHandler::ComputeCreatePartnerTaskResponse);
    Install("CEventHandler", "ComputeDamageResponse", 0x4C0170, &CEventHandler::ComputeDamageResponse);
    Install("CEventHandler", "ComputeDangerResponse", 0x4BC230, &CEventHandler::ComputeDangerResponse);
    Install("CEventHandler", "ComputeDeadPedResponse", 0x4B9470, &CEventHandler::ComputeDeadPedResponse);
    Install("CEventHandler", "ComputeDeathResponse", 0x4B9400, &CEventHandler::ComputeDeathResponse);
    Install("CEventHandler", "ComputeDontJoinGroupResponse", 0x4BC1D0, &CEventHandler::ComputeDontJoinGroupResponse);
    Install("CEventHandler", "ComputeDraggedOutCarResponse", 0x4BCC30, &CEventHandler::ComputeDraggedOutCarResponse);
    Install("CEventHandler", "ComputeFireNearbyResponse", 0x4BBFB0, &CEventHandler::ComputeFireNearbyResponse);
    Install("CEventHandler", "ComputeGotKnockedOverByCarResponse", 0x4C3430, &CEventHandler::ComputeGotKnockedOverByCarResponse);
    Install("CEventHandler", "ComputeGunAimedAtResponse", 0x4C2840, &CEventHandler::ComputeGunAimedAtResponse);
    Install("CEventHandler", "ComputeHighAngerAtPlayerResponse", 0x4BAC10, &CEventHandler::ComputeHighAngerAtPlayerResponse);
    Install("CEventHandler", "ComputeInWaterResponse", 0x4BAF80, &CEventHandler::ComputeInWaterResponse);
    Install("CEventHandler", "ComputeInteriorUseInfoResponse", 0x4BAFE0, &CEventHandler::ComputeInteriorUseInfoResponse);
    Install("CEventHandler", "ComputeKnockOffBikeResponse", 0x4B9FF0, &CEventHandler::ComputeKnockOffBikeResponse);
    Install("CEventHandler", "ComputeLowAngerAtPlayerResponse", 0x4BAAD0, &CEventHandler::ComputeLowAngerAtPlayerResponse);
    Install("CEventHandler", "ComputeLowHealthResponse", 0x4BA990, &CEventHandler::ComputeLowHealthResponse);
    Install("CEventHandler", "ComputeObjectCollisionPassiveResponse", 0x4BBB90, &CEventHandler::ComputeObjectCollisionPassiveResponse);
    Install("CEventHandler", "ComputeObjectCollisionResponse", 0x4B92B0, &CEventHandler::ComputeObjectCollisionResponse);
    Install("CEventHandler", "ComputeOnEscalatorResponse", 0x4BC150, &CEventHandler::ComputeOnEscalatorResponse);
    Install("CEventHandler", "ComputeOnFireResponse", 0x4BAD50, &CEventHandler::ComputeOnFireResponse);
    Install("CEventHandler", "ComputePassObjectResponse", 0x4BB0C0, &CEventHandler::ComputePassObjectResponse);
    Install("CEventHandler", "ComputePedCollisionWithPedResponse", 0x4BDB80, &CEventHandler::ComputePedCollisionWithPedResponse);
    Install("CEventHandler", "ComputePedCollisionWithPlayerResponse", 0x4BE7D0, &CEventHandler::ComputePedCollisionWithPlayerResponse);
    Install("CEventHandler", "ComputePedEnteredVehicleResponse", 0x4C1590, &CEventHandler::ComputePedEnteredVehicleResponse);
    Install("CEventHandler", "ComputePedFriendResponse", 0x4B9DD0, &CEventHandler::ComputePedFriendResponse);
    Install("CEventHandler", "ComputePedSoundQuietResponse", 0x4B9D40, &CEventHandler::ComputePedSoundQuietResponse);
    Install("CEventHandler", "ComputePedThreatBadlyLitResponse", 0x4B9C90, &CEventHandler::ComputePedThreatBadlyLitResponse);
    Install("CEventHandler", "ComputePedThreatResponse", 0x4C19A0, &CEventHandler::ComputePedThreatResponse);
    Install("CEventHandler", "ComputePedToChaseResponse", 0x4C1910, &CEventHandler::ComputePedToChaseResponse);
    Install("CEventHandler", "ComputePedToFleeResponse", 0x4B9B50, &CEventHandler::ComputePedToFleeResponse);
    Install("CEventHandler", "ComputePersonalityResponseToDamage", 0x4BF9B0, &CEventHandler::ComputePersonalityResponseToDamage);
    Install("CEventHandler", "ComputePlayerCollisionWithPedResponse", 0x4B8CE0, &CEventHandler::ComputePlayerCollisionWithPedResponse);
    Install("CEventHandler", "ComputePlayerWantedLevelResponse", 0x4BB280, &CEventHandler::ComputePlayerWantedLevelResponse);
    Install("CEventHandler", "ComputePotentialPedCollideResponse", 0x4C2610, &CEventHandler::ComputePotentialPedCollideResponse);
    Install("CEventHandler", "ComputePotentialWalkIntoFireResponse", 0x4BBCD0, &CEventHandler::ComputePotentialWalkIntoFireResponse);
    Install("CEventHandler", "ComputeReallyLowHealthResponse", 0x4BAA30, &CEventHandler::ComputeReallyLowHealthResponse);
    Install("CEventHandler", "ComputeReviveResponse", 0x4B97B0, &CEventHandler::ComputeReviveResponse);
    Install("CEventHandler", "ComputeScriptCommandResponse", 0x4BA7C0, &CEventHandler::ComputeScriptCommandResponse);
    Install("CEventHandler", "ComputeSeenCopResponse", 0x4BC050, &CEventHandler::ComputeSeenCopResponse);
    Install("CEventHandler", "ComputeSeenPanickedPedResponse", 0x4C35F0, &CEventHandler::ComputeSeenPanickedPedResponse);
    Install("CEventHandler", "ComputeSexyPedResponse", 0x4B99F0, &CEventHandler::ComputeSexyPedResponse);
    Install("CEventHandler", "ComputeSexyVehicleResponse", 0x4B9AA0, &CEventHandler::ComputeSexyVehicleResponse);
    Install("CEventHandler", "ComputeShotFiredResponse", 0x4BC710, &CEventHandler::ComputeShotFiredResponse);
    Install("CEventHandler", "ComputeShotFiredWhizzedByResponse", 0x4BBE30, &CEventHandler::ComputeShotFiredWhizzedByResponse);
    Install("CEventHandler", "ComputeSignalAtPedResponse", 0x4BB050, &CEventHandler::ComputeSignalAtPedResponse);
    Install("CEventHandler", "ComputeSpecialResponse", 0x4BB800, &CEventHandler::ComputeSpecialResponse);
    Install("CEventHandler", "ComputeVehicleCollisionResponse", 0x4BD6A0, &CEventHandler::ComputeVehicleCollisionResponse);
    Install("CEventHandler", "ComputeVehicleDamageResponse", 0x4C2FC0, &CEventHandler::ComputeVehicleDamageResponse);
    Install("CEventHandler", "ComputeVehicleDiedResponse", 0x4BA8B0, &CEventHandler::ComputeVehicleDiedResponse);
    Install("CEventHandler", "ComputeVehicleHitAndRunResponse", 0x0, &CEventHandler::ComputeVehicleHitAndRunResponse);
    Install("CEventHandler", "ComputeVehicleOnFireResponse", 0x4BB2E0, &CEventHandler::ComputeVehicleOnFireResponse);
    Install("CEventHandler", "ComputeVehiclePotentialCollisionResponse", 0x4C0BD0, &CEventHandler::ComputeVehiclePotentialCollisionResponse);
    Install("CEventHandler", "ComputeVehiclePotentialPassiveCollisionResponse", 0x4B96D0, &CEventHandler::ComputeVehiclePotentialPassiveCollisionResponse);
    Install("CEventHandler", "ComputeVehicleToStealResponse", 0x4B9F80, &CEventHandler::ComputeVehicleToStealResponse);
    Install("CEventHandler", "ComputeWaterCannonResponse", 0x4BAE30, &CEventHandler::ComputeWaterCannonResponse);
    */

    // RH_ScopedOverloadedInstall(ComputeEventResponseTask, "0", 0x4C3870, void (CEventHandler::*)(CEvent*, CTask*));
    // RH_ScopedOverloadedInstall(ComputeEventResponseTask, "1", 0x4C4220, CTask* (CEventHandler::*)(CPed*, CEvent*));
}

// 0x4C3E80
CEventHandler::CEventHandler(CPed* ped) {
    m_ped                  = ped;
    m_physicalResponseTask = nullptr;
    m_eventResponseTask    = nullptr;
    m_attackTask           = nullptr;
    m_sayTask              = nullptr;
    m_partialAnimTask      = nullptr;
    m_history.ClearAllEvents();
}

CEventHandler* CEventHandler::Constructor(CPed* ped) {
    this->CEventHandler::CEventHandler(ped);
    return this;
}

// 0x4C3F10
void CEventHandler::HandleEvents() {
    plugin::CallMethod<0x4C3F10, CEventHandler*>(this);
}

void CEventHandler::RecordActiveEvent(const CEvent& event) {
    assert(false);
}

void CEventHandler::RecordPassiveEvent(const CEvent& event) {
    assert(false);
}

// 0x4B9340
void CEventHandler::RegisterKill(const CPed* ped, const CEntity* entity, eWeaponType weaponType, bool a4) {
    plugin::CallMethod<0x4B9340, CEventHandler*, const CPed*, const CEntity*, eWeaponType, bool>(this, ped, entity, weaponType, a4);
}

// 0x4BC600
void CEventHandler::SetEventResponseTask(const CEvent& event) {
    plugin::CallMethod<0x4BC600, CEventHandler*, const CEvent&>(this, event);
}

// 0x4C3790
void CEventHandler::Flush() {
    delete m_physicalResponseTask;
    m_physicalResponseTask = nullptr;

    delete m_eventResponseTask;
    m_eventResponseTask = nullptr;

    delete m_attackTask;
    m_attackTask = nullptr;

    delete m_sayTask;
    m_sayTask = nullptr;

    delete m_partialAnimTask;
    m_partialAnimTask = nullptr;

    m_history.Flush();
}

// 0x4C3820
void CEventHandler::FlushImmediately() {
    m_history.Flush();
}

// 0x4B8CC0
eEventType CEventHandler::GetCurrentEventType() {
    return plugin::CallMethodAndReturn<eEventType, 0x4B8CC0, CEventHandler*>(this);
}

// 0x4BC370
bool CEventHandler::IsTemporaryEvent(const CEvent& event) {
    auto eventType = event.GetEventType();
    switch (eventType) {
    case EVENT_VEHICLE_COLLISION:
    case EVENT_PED_COLLISION_WITH_PED:
    case EVENT_PED_COLLISION_WITH_PLAYER:
    case EVENT_PLAYER_COLLISION_WITH_PED:
    case EVENT_OBJECT_COLLISION:
    case EVENT_BUILDING_COLLISION:
    case EVENT_IN_AIR:
    case EVENT_POTENTIAL_WALK_INTO_VEHICLE:
    case EVENT_POTENTIAL_WALK_INTO_BUILDING:
    case EVENT_POTENTIAL_WALK_INTO_OBJECT:
    case EVENT_POTENTIAL_WALK_INTO_PED:
    case EVENT_POTENTIAL_WALK_INTO_FIRE:
    case EVENT_AREA_CODES:
    case EVENT_STUCK_IN_AIR:
    case EVENT_POTENTIAL_GET_RUN_OVER:
    case EVENT_ON_ESCALATOR:
    case EVENT_FIRE_NEARBY:
        return true;
    default:
        return false;
    }
}

// 0x4BC3E0
bool CEventHandler::IsKillTaskAppropriate(CPed* ped1, CPed* ped2, const CEvent& event) {
    return plugin::CallMethodAndReturn<bool, 0x4BC3E0, CEventHandler*, CPed*, CPed*, const CEvent&>(this, ped1, ped2, event);
}

// 0x4BBF50
void CEventHandler::ComputeAreaCodesResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BBF50, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B9BE0
void CEventHandler::ComputeAttractorResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9BE0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x0
// EVENT_POTENTIAL_WALK_INTO_BUILDING
// ANDROID IDB 0x3025F8 (1.0)
void CEventHandler::ComputeBuildingCollisionPassiveResponse(CEvent* event, CTask* task1, CTask* task2) {
    // NOP
}

// 0x4BF2B0
void CEventHandler::ComputeBuildingCollisionResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BF2B0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BBC30
void CEventHandler::ComputeCarUpsideDownResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BBC30, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B98E0
void CEventHandler::ComputeChatPartnerResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B98E0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BB740
void CEventHandler::ComputeCopCarBeingStolenResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BB740, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BB130
void CEventHandler::ComputeCreatePartnerTaskResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BB130, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C0170
void CEventHandler::ComputeDamageResponse(CEvent* event, CTask* task1, CTask* task2, CTask* task3) {
    plugin::CallMethod<0x4C0170, CEventHandler*, CEvent*, CTask*, CTask*, CTask*>(this, event, task1, task2, task3);
}

// 0x4BC230
void CEventHandler::ComputeDangerResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BC230, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B9470
void CEventHandler::ComputeDeadPedResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9470, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B9400
void CEventHandler::ComputeDeathResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9400, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BC1D0
void CEventHandler::ComputeDontJoinGroupResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BC1D0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);

    // m_eventResponseTask = new CTaskComplexGangJoinRespond(0);
}

// 0x4BCC30
void CEventHandler::ComputeDraggedOutCarResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BCC30, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BBFB0
void CEventHandler::ComputeFireNearbyResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BBFB0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    /*
    auto taskId = task1->GetTaskType();
    if (taskId == TASK_NONE) {
        m_eventResponseTask = nullptr;
    } else if (taskId == TASK_COMPLEX_EXTINGUISH_FIRES) {
        m_eventResponseTask = new CTaskComplexExtinguishFires();
    }
    */
}

// 0x4C3430
void CEventHandler::ComputeGotKnockedOverByCarResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C3430, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C2840
void CEventHandler::ComputeGunAimedAtResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C2840, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BAC10
void CEventHandler::ComputeHighAngerAtPlayerResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BAC10, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BAF80
void CEventHandler::ComputeInWaterResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BAF80, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    // m_eventResponseTask = new CTaskComplexInWater();
}

// 0x4BAFE0
void CEventHandler::ComputeInteriorUseInfoResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BAFE0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    // m_eventResponseTask = new CTaskInteriorUseInfo(task1->m_interiorInfo, task1->m_interior, task1->m_actionAnimTime, task1->m_loopAction);
}

// 0x4B9FF0
void CEventHandler::ComputeKnockOffBikeResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9FF0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BAAD0
void CEventHandler::ComputeLowAngerAtPlayerResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BAAD0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BA990
void CEventHandler::ComputeLowHealthResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BA990, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    /*
    auto taskId = task1->GetTaskType();
    if (taskId == TASK_NONE) {
        m_eventResponseTask = nullptr;
    } else if (taskId == TASK_COMPLEX_DIVE_FROM_ATTACHED_ENTITY_AND_GET_UP) {
        m_eventResponseTask = new CTaskComplexDiveFromAttachedEntityAndGetUp(0);
    }
    */
}

// 0x4BBB90
void CEventHandler::ComputeObjectCollisionPassiveResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BBB90, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B92B0
void CEventHandler::ComputeObjectCollisionResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B92B0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BC150
void CEventHandler::ComputeOnEscalatorResponse(CEvent* event, CTask* task1, CTask* task2) {
    m_eventResponseTask = new CTaskSimpleStandStill(0, true, false, 8.0f);
}

// 0x4BAD50
void CEventHandler::ComputeOnFireResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BAD50, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BB0C0
void CEventHandler::ComputePassObjectResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BB0C0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    /*
    auto _event = static_cast<CEventPassObject*>(event);
    // m_eventResponseTask = new CTaskComplexPassObject(_event->m_giver, _event->m_dontPassObject);
    */
}

// 0x4BDB80
void CEventHandler::ComputePedCollisionWithPedResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BDB80, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BE7D0
void CEventHandler::ComputePedCollisionWithPlayerResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BE7D0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C1590
void CEventHandler::ComputePedEnteredVehicleResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C1590, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B9DD0
void CEventHandler::ComputePedFriendResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9DD0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B9D40
void CEventHandler::ComputePedSoundQuietResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9D40, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B9C90
void CEventHandler::ComputePedThreatBadlyLitResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9C90, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C19A0
void CEventHandler::ComputePedThreatResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C19A0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C1910
void CEventHandler::ComputePedToChaseResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C1910, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    /*
    m_eventResponseTask = new CTaskComplexSeekEntity(static_cast<CTask*>(task1)->entity, 30000, 1000, 1.0f, 2.0f, 2.0f, 1, 1);
    */
}

// 0x4B9B50
void CEventHandler::ComputePedToFleeResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9B50, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);

    /*
    auto _task1 = static_cast<CTask*>(task1);
    if (_task1->entity) {
        m_ped->Say(69, 0, 1.0f, 0, 0, 0);
        m_eventResponseTask = new CTaskComplexSmartFleeEntity(_task1->entity, 1, 100.0f, -1, 1000, 1.0f);
    }
    */
}

// 0x4BF9B0
void CEventHandler::ComputePersonalityResponseToDamage(CEventDamage* damageEvent, CEntity* entity) {
    plugin::CallMethod<0x4BF9B0, CEventHandler*, CEventDamage*, CEntity*>(this, damageEvent, entity);
}

// 0x4B8CE0
void CEventHandler::ComputePlayerCollisionWithPedResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B8CE0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BB280
void CEventHandler::ComputePlayerWantedLevelResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BB280, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    //m_eventResponseTask = new CTaskComplexPolicePursuit();
}

// 0x4C2610
void CEventHandler::ComputePotentialPedCollideResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C2610, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BBCD0
void CEventHandler::ComputePotentialWalkIntoFireResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BBCD0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BAA30
void CEventHandler::ComputeReallyLowHealthResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BAA30, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    /*
    auto taskId = task1->GetTaskType();
    if (taskId == TASK_NONE) {
        m_eventResponseTask = nullptr;
    } else if (taskId == TASK_COMPLEX_DIVE_FROM_ATTACHED_ENTITY_AND_GET_UP) {
        m_eventResponseTask = new CTaskComplexDiveFromAttachedEntityAndGetUp(0);
    }
    */
}

// 0x4B97B0
void CEventHandler::ComputeReviveResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B97B0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BA7C0
void CEventHandler::ComputeScriptCommandResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BA7C0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BC050
void CEventHandler::ComputeSeenCopResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BC050, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C35F0
void CEventHandler::ComputeSeenPanickedPedResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C35F0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B99F0
void CEventHandler::ComputeSexyPedResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B99F0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
    /*
    const auto taskId = task1->GetTaskType();
    auto entity = static_cast<CTask*>(task1)->entity;
    if (!entity)
        return;

    if (taskId == TASK_NONE) {
        m_eventResponseTask = nullptr;
    } else if (taskId == TASK_COMPLEX_GANG_HASSLE_PED) {
        m_eventResponseTask = new CTaskComplexGangHasslePed(entity, 0, 10000, 30000);
    }
    */
}

// 0x4B9AA0
void CEventHandler::ComputeSexyVehicleResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9AA0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// task1 TASK_COMPLEX_CAR_DRIVE_WANDER 711 911 912 911 1204
// task2 TASK_SIMPLE_CAR_DRIVE         709 400 900 900 900
// 0x4BC710
void CEventHandler::ComputeShotFiredResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BC710, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BBE30
void CEventHandler::ComputeShotFiredWhizzedByResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BBE30, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BB050
void CEventHandler::ComputeSignalAtPedResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BB050, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);

    //m_eventResponseTask = new CTaskComplexSignalAtPed(*(task1 + 12), *(task1 + 16), *(task1 + 20));
}

// 0x4BB800
void CEventHandler::ComputeSpecialResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BB800, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BD6A0
void CEventHandler::ComputeVehicleCollisionResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BD6A0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C2FC0
void CEventHandler::ComputeVehicleDamageResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C2FC0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BA8B0
void CEventHandler::ComputeVehicleDiedResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BA8B0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// TODO: 0x?
void CEventHandler::ComputeVehicleHitAndRunResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BB2E0
void CEventHandler::ComputeVehicleOnFireResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BB2E0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C0BD0
void CEventHandler::ComputeVehiclePotentialCollisionResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4C0BD0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B96D0
void CEventHandler::ComputeVehiclePotentialPassiveCollisionResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B96D0, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4B9F80
void CEventHandler::ComputeVehicleToStealResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4B9F80, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4BAE30
void CEventHandler::ComputeWaterCannonResponse(CEvent* event, CTask* task1, CTask* task2) {
    plugin::CallMethod<0x4BAE30, CEventHandler*, CEvent*, CTask*, CTask*>(this, event, task1, task2);
}

// 0x4C3870
void CEventHandler::ComputeEventResponseTask(CEvent* event, CTask* task) {
    plugin::CallMethod<0x4C3870, CEventHandler*, CEvent*, CTask*>(this, event, task);

    /*
    m_physicalResponseTask = nullptr;
    m_eventResponseTask = nullptr;
    m_attackTask = nullptr;
    m_sayTask = nullptr;
    m_partialAnimTask = nullptr;

    CTask* task1 = m_ped->GetTaskManager().GetActiveTask();
    CTask* task2 = nullptr;
    if (task1)
        task2 = m_ped->GetTaskManager().GetSimplestActiveTask();

    printf("event: %d task1: %d task2: %d\n", event->GetEventType(), task1->GetTaskType(), task2->GetTaskType()); // NOTSA

    switch (event->GetEventType()) {
    case EVENT_VEHICLE_COLLISION:
        ComputeVehicleCollisionResponse(event, task1, task2);
        break;
    case EVENT_PED_COLLISION_WITH_PED:
        ComputePedCollisionWithPedResponse(event, task1, task2);
        break;
    case EVENT_PED_COLLISION_WITH_PLAYER:
        ComputePedCollisionWithPlayerResponse(event, task1, task2);
        break;
    case EVENT_PLAYER_COLLISION_WITH_PED:
        ComputePlayerCollisionWithPedResponse(event, task1, task2);
        break;
    case EVENT_OBJECT_COLLISION:
        ComputeObjectCollisionResponse(event, task1, task2);
        break;
    case EVENT_BUILDING_COLLISION:
        ComputeBuildingCollisionResponse(event, task1, task2);
        break;
    case EVENT_DRAGGED_OUT_CAR:
        ComputeDraggedOutCarResponse(event, task1, task2);
        break;
    case EVENT_KNOCK_OFF_BIKE:
        ComputeKnockOffBikeResponse(event, task1, task2);
        break;
    case EVENT_DAMAGE:
        ComputeDamageResponse(event, task1, task2, task);
        break;
    case EVENT_DEATH:
        ComputeDeathResponse(event, task1, task2);
        break;
    case EVENT_DEAD_PED:
        ComputeDeadPedResponse(event, task1, task2);
        break;
    case EVENT_POTENTIAL_GET_RUN_OVER:
        ComputeVehiclePotentialCollisionResponse(event, task1, task2);
        break;
    case EVENT_POTENTIAL_WALK_INTO_PED:
        ComputePotentialPedCollideResponse(event, task1, task2);
        break;
    case EVENT_SHOT_FIRED:
        ComputeShotFiredResponse(event, task1, task2);
        break;
    case EVENT_COP_CAR_BEING_STOLEN:
        ComputeCopCarBeingStolenResponse(event, task1, task2);
        break;
    case EVENT_PED_ENTERED_MY_VEHICLE:
        ComputePedEnteredVehicleResponse(event, task1, task2);
        break;
    case EVENT_REVIVE:
        ComputeReviveResponse(event, task1, task2);
        break;
    case EVENT_CHAT_PARTNER:
        ComputeChatPartnerResponse(event, task1, task2);
        break;
    case EVENT_SEXY_PED:
        ComputeSexyPedResponse(event, task1, task2);
        break;
    case EVENT_SEXY_VEHICLE:
        ComputeSexyVehicleResponse(event, task1, task2);
        break;
    case EVENT_PED_TO_CHASE:
        ComputePedToChaseResponse(event, task1, task2);
        break;
    case EVENT_PED_TO_FLEE:
        ComputePedToFleeResponse(event, task1, task2);
        break;
    case EVENT_ATTRACTOR:
    case EVENT_SCRIPTED_ATTRACTOR:
        ComputeAttractorResponse(event, task1, task2);
        break;
    case EVENT_VEHICLE_TO_STEAL:
        ComputeVehicleToStealResponse(event, task1, task2);
        break;
    case EVENT_GUN_AIMED_AT:
        ComputeGunAimedAtResponse(event, task1, task2);
        break;
    case EVENT_SCRIPT_COMMAND:
        ComputeScriptCommandResponse(event, task1, task2);
        break;
    case EVENT_IN_AIR:
        if ((m_ped->m_nPedFlags & 1) == 0) { // !m_ped->bIsStanding
            m_eventResponseTask = new CTaskComplexInAirAndLand(false, false);
        }
        break;
    case EVENT_VEHICLE_DIED:
        ComputeVehicleDiedResponse(event, task1, task2);
        break;
    case EVENT_ACQUAINTANCE_PED_HATE:
    case EVENT_ACQUAINTANCE_PED_DISLIKE:
        ComputePedThreatResponse(event, task1, task2);
        break;
    case EVENT_ACQUAINTANCE_PED_LIKE:
    case EVENT_ACQUAINTANCE_PED_RESPECT:
        ComputePedFriendResponse(event, task1, task2);
        break;
    case EVENT_VEHICLE_DAMAGE_WEAPON:
    case EVENT_VEHICLE_DAMAGE_COLLISION:
        ComputeVehicleDamageResponse(event, task1, task2);
        break;
    case EVENT_SPECIAL:
        ComputeSpecialResponse(event, task1, task2);
        break;
    case EVENT_GOT_KNOCKED_OVER_BY_CAR:
        ComputeGotKnockedOverByCarResponse(event, task1, task2);
        break;
    case EVENT_POTENTIAL_WALK_INTO_OBJECT:
        ComputeObjectCollisionPassiveResponse(event, task1, task2);
        break;
    case EVENT_CAR_UPSIDE_DOWN:
        ComputeCarUpsideDownResponse(event, task1, task2);
        break;
    case EVENT_POTENTIAL_WALK_INTO_FIRE:
        ComputePotentialWalkIntoFireResponse(event, task1, task2);
        break;
    case EVENT_SHOT_FIRED_WHIZZED_BY:
        ComputeShotFiredWhizzedByResponse(event, task1, task2);
        break;
    case EVENT_LOW_ANGER_AT_PLAYER:
        ComputeLowAngerAtPlayerResponse(event, task1, task2);
        break;
    case EVENT_HIGH_ANGER_AT_PLAYER:
        ComputeHighAngerAtPlayerResponse(event, task1, task2);
        break;
    case EVENT_HEALTH_REALLY_LOW:
        ComputeReallyLowHealthResponse(event, task1, task2);
        break;
    case EVENT_HEALTH_LOW:
        ComputeLowHealthResponse(event, task1, task2);
        break;
    case EVENT_POTENTIAL_WALK_INTO_VEHICLE:
        ComputeVehiclePotentialPassiveCollisionResponse(event, task1, task2);
        break;
    case EVENT_ON_FIRE:
        ComputeOnFireResponse(event, task1, task2);
        break;
    case EVENT_FIRE_NEARBY:
        ComputeFireNearbyResponse(event, task1, task2);
        break;
    case EVENT_SOUND_QUIET:
        ComputePedSoundQuietResponse(event, task1, task2);
        break;
    case EVENT_ACQUAINTANCE_PED_HATE_BADLY_LIT:
        ComputePedThreatBadlyLitResponse(event, task1, task2);
        break;
    case EVENT_WATER_CANNON:
        ComputeWaterCannonResponse(event, task1, task2);
        break;
    case EVENT_SEEN_PANICKED_PED:
        ComputeSeenPanickedPedResponse(event, task1, task2);
        break;
    case EVENT_IN_WATER:
        ComputeInWaterResponse(event, task1, task2);
        break;
    case EVENT_AREA_CODES:
        ComputeAreaCodesResponse(event, task1, task2);
        break;
    case EVENT_PLAYER_WANTED_LEVEL:
        ComputePlayerWantedLevelResponse(event, task1, task2);
        break;
    case EVENT_CREATE_PARTNER_TASK:
        ComputeCreatePartnerTaskResponse(event, task1, task2);
        break;
    case EVENT_SEEN_COP:
        ComputeSeenCopResponse(event, task1, task2);
        break;
    case EVENT_ON_ESCALATOR:
        ComputeOnEscalatorResponse(event, task1, task2);
        break;
    case EVENT_DANGER:
        ComputeDangerResponse(event, task1, task2);
        break;
    case EVENT_VEHICLE_ON_FIRE:
        ComputeVehicleOnFireResponse(event, task1, task2);
        break;
    case EVENT_INTERIOR_USE_INFO:
        ComputeInteriorUseInfoResponse(event, task1, task2);
        break;
    case EVENT_SIGNAL_AT_PED:
        ComputeSignalAtPedResponse(event, task1, task2);
        break;
    case EVENT_PASS_OBJECT:
        ComputePassObjectResponse(event, task1, task2);
        break;
    case EVENT_STUCK_IN_AIR:
        m_eventResponseTask = new CTaskComplexStuckInAir();
        break;
    case EVENT_DONT_JOIN_GROUP:
        ComputeDontJoinGroupResponse(event, task1, task2);
        break;
    default:
        return;
    }
    */
}

// should be (const CPed& ped, const CEvent& event);
// 0x4C4220
CTask* CEventHandler::ComputeEventResponseTask(CPed* ped, CEvent* event) {
    return plugin::CallAndReturn<CTask*, 0x4C4220, CPed*, CEvent*>(ped, event);
    /*
    CTask* task = nullptr;

    CEventHandler handler(ped);
    handler.ComputeEventResponseTask(event, nullptr);
    if (handler.m_eventResponseTask) {
        task = handler.m_eventResponseTask;
        handler.m_eventResponseTask = nullptr;
    }
    handler.Flush();
    delete handler.m_history.m_tempEvent;
    delete handler.m_history.m_nonTempEvent;
    delete handler.m_history.m_storedActiveEvent;

    return task;
    */
}
