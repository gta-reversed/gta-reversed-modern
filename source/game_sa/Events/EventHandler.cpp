#include "StdInc.h"

#include "EventHandler.h"

#include "TaskSimpleStandStill.h"
#include "TaskComplexInAirAndLand.h"
#include "TaskComplexStuckInAir.h"
// #include "TaskComplexSmartFleeEntity.h"

#include "InterestingEvents.h"
#include "IKChainManager_c.h"
#include "EventSexyVehicle.h"

void CEventHandler::InjectHooks() {
    RH_ScopedClass(CEventHandler);
    RH_ScopedCategory("Events");

    using namespace ReversibleHooks;

    RH_ScopedInstall(Flush, 0x4C3790);
    RH_ScopedInstall(FlushImmediately, 0x4C3820);
    RH_ScopedInstall(GetCurrentEventType, 0x4B8CC0, { .reversed = false });
    RH_ScopedInstall(HandleEvents, 0x4C3F10, { .reversed = false });
    RH_ScopedInstall(IsKillTaskAppropriate, 0x4BC3E0, { .reversed = false });
    RH_ScopedInstall(IsTemporaryEvent, 0x4BC370);
    // RH_ScopedInstall(RecordActiveEvent, 0x0, { .reversed = false });
    // RH_ScopedInstall(RecordPassiveEvent, 0x0, { .reversed = false });
    RH_ScopedInstall(RegisterKill, 0x4B9340, { .reversed = false });
    RH_ScopedInstall(SetEventResponseTask, 0x4BC600, { .reversed = false });
   
    RH_ScopedInstall(ComputeAreaCodesResponse, 0x4BBF50, { .reversed = false });
    RH_ScopedInstall(ComputeAttractorResponse, 0x4B9BE0, { .reversed = false });
    // RH_ScopedInstall(ComputeBuildingCollisionPassiveResponse, 0x0, { .reversed = false });
    RH_ScopedInstall(ComputeBuildingCollisionResponse, 0x4BF2B0, { .reversed = false });
    RH_ScopedInstall(ComputeCarUpsideDownResponse, 0x4BBC30, { .reversed = false });
    RH_ScopedInstall(ComputeChatPartnerResponse, 0x4B98E0, { .reversed = false });
    RH_ScopedInstall(ComputeCopCarBeingStolenResponse, 0x4BB740, { .reversed = false });
    RH_ScopedInstall(ComputeCreatePartnerTaskResponse, 0x4BB130, { .reversed = false });
    RH_ScopedInstall(ComputeDamageResponse, 0x4C0170, { .reversed = false });
    RH_ScopedInstall(ComputeDangerResponse, 0x4BC230, { .reversed = false });
    RH_ScopedInstall(ComputeDeadPedResponse, 0x4B9470, { .reversed = false });
    RH_ScopedInstall(ComputeDeathResponse, 0x4B9400, { .reversed = false });
    RH_ScopedInstall(ComputeDontJoinGroupResponse, 0x4BC1D0, { .reversed = false });
    RH_ScopedInstall(ComputeDraggedOutCarResponse, 0x4BCC30, { .reversed = false });
    RH_ScopedInstall(ComputeFireNearbyResponse, 0x4BBFB0, { .reversed = false });
    RH_ScopedInstall(ComputeGotKnockedOverByCarResponse, 0x4C3430, { .reversed = false });
    RH_ScopedInstall(ComputeGunAimedAtResponse, 0x4C2840, { .reversed = false });
    RH_ScopedInstall(ComputeHighAngerAtPlayerResponse, 0x4BAC10, { .reversed = false });
    RH_ScopedInstall(ComputeInWaterResponse, 0x4BAF80, { .reversed = false });
    RH_ScopedInstall(ComputeInteriorUseInfoResponse, 0x4BAFE0, { .reversed = false });
    RH_ScopedInstall(ComputeKnockOffBikeResponse, 0x4B9FF0, { .reversed = false });
    RH_ScopedInstall(ComputeLowAngerAtPlayerResponse, 0x4BAAD0, { .reversed = false });
    RH_ScopedInstall(ComputeLowHealthResponse, 0x4BA990, { .reversed = false });
    RH_ScopedInstall(ComputeObjectCollisionPassiveResponse, 0x4BBB90, { .reversed = false });
    RH_ScopedInstall(ComputeObjectCollisionResponse, 0x4B92B0, { .reversed = false });
    RH_ScopedInstall(ComputeOnEscalatorResponse, 0x4BC150, { .reversed = false });
    RH_ScopedInstall(ComputeOnFireResponse, 0x4BAD50, { .reversed = false });
    RH_ScopedInstall(ComputePassObjectResponse, 0x4BB0C0, { .reversed = false });
    RH_ScopedInstall(ComputePedCollisionWithPedResponse, 0x4BDB80, { .reversed = false });
    RH_ScopedInstall(ComputePedCollisionWithPlayerResponse, 0x4BE7D0, { .reversed = false });
    RH_ScopedInstall(ComputePedEnteredVehicleResponse, 0x4C1590, { .reversed = false });
    RH_ScopedInstall(ComputePedFriendResponse, 0x4B9DD0, { .reversed = false });
    RH_ScopedInstall(ComputePedSoundQuietResponse, 0x4B9D40, { .reversed = false });
    RH_ScopedInstall(ComputePedThreatBadlyLitResponse, 0x4B9C90, { .reversed = false });
    RH_ScopedInstall(ComputePedThreatResponse, 0x4C19A0, { .reversed = false });
    RH_ScopedInstall(ComputePedToChaseResponse, 0x4C1910, { .reversed = false });
    RH_ScopedInstall(ComputePedToFleeResponse, 0x4B9B50, { .reversed = false });
    RH_ScopedInstall(ComputePersonalityResponseToDamage, 0x4BF9B0, { .reversed = false });
    RH_ScopedInstall(ComputePlayerCollisionWithPedResponse, 0x4B8CE0, { .reversed = false });
    RH_ScopedInstall(ComputePlayerWantedLevelResponse, 0x4BB280, { .reversed = false });
    RH_ScopedInstall(ComputePotentialPedCollideResponse, 0x4C2610, { .reversed = false });
    RH_ScopedInstall(ComputePotentialWalkIntoFireResponse, 0x4BBCD0, { .reversed = false });
    RH_ScopedInstall(ComputeReallyLowHealthResponse, 0x4BAA30, { .reversed = false });
    RH_ScopedInstall(ComputeReviveResponse, 0x4B97B0, { .reversed = false });
    RH_ScopedInstall(ComputeScriptCommandResponse, 0x4BA7C0, { .reversed = false });
    RH_ScopedInstall(ComputeSeenCopResponse, 0x4BC050, { .reversed = false });
    RH_ScopedInstall(ComputeSeenPanickedPedResponse, 0x4C35F0, { .reversed = false });
    RH_ScopedInstall(ComputeSexyPedResponse, 0x4B99F0, { .reversed = false });
    RH_ScopedInstall(ComputeSexyVehicleResponse, 0x4B9AA0, { .reversed = false });
    RH_ScopedInstall(ComputeShotFiredResponse, 0x4BC710, { .reversed = false });
    RH_ScopedInstall(ComputeShotFiredWhizzedByResponse, 0x4BBE30, { .reversed = false });
    RH_ScopedInstall(ComputeSignalAtPedResponse, 0x4BB050, { .reversed = false });
    RH_ScopedInstall(ComputeSpecialResponse, 0x4BB800, { .reversed = false });
    RH_ScopedInstall(ComputeVehicleCollisionResponse, 0x4BD6A0, { .reversed = false });
    RH_ScopedInstall(ComputeVehicleDamageResponse, 0x4C2FC0, { .reversed = false });
    RH_ScopedInstall(ComputeVehicleDiedResponse, 0x4BA8B0, { .reversed = false });
    // RH_ScopedInstall(ComputeVehicleHitAndRunResponse, 0x0, { .reversed = false });
    RH_ScopedInstall(ComputeVehicleOnFireResponse, 0x4BB2E0, { .reversed = false });
    RH_ScopedInstall(ComputeVehiclePotentialCollisionResponse, 0x4C0BD0, { .reversed = false });
    RH_ScopedInstall(ComputeVehiclePotentialPassiveCollisionResponse, 0x4B96D0, { .reversed = false });
    RH_ScopedInstall(ComputeVehicleToStealResponse, 0x4B9F80, { .reversed = false });
    RH_ScopedInstall(ComputeWaterCannonResponse, 0x4BAE30, { .reversed = false });

    // RH_ScopedOverloadedInstall(ComputeEventResponseTask, "0", 0x4C3870, void (CEventHandler::*)(CEvent*, CTask*));
    RH_ScopedOverloadedInstall(ComputeEventResponseTask, "Ped", 0x4C4220, CTask*(*)(const CPed&, const CEvent&));
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
    plugin::Call<0x4B9340, const CPed*, const CEntity*, eWeaponType, bool>(ped, entity, weaponType, a4);
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
    if (auto* ped = static_cast<CEventPedToFlee*>(event)->m_currPedToKill) {
        m_currPedToKill->Say(69);
        m_eventResponseTask = new CTaskComplexSmartFleeEntity(ped, 1, 100.0f, -1, 1000, 1.0f);
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
    auto evnt = reinterpret_cast<CEventSexyVehicle*>(event);
    if (evnt->m_vehicle) {
        g_InterestingEvents.Add(CInterestingEvents::EType::INTERESTING_EVENT_8, evnt->m_vehicle);
        m_eventResponseTask = new CTaskSimpleStandStill(5000, false, false, 8.0f);
        g_ikChainMan.LookAt("CompSexyVhclResp", m_ped, evnt->m_vehicle, 5000, BONE_UNKNOWN, nullptr, true, 0.25f, 500, 3, false);
    }
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

// 0x?
void CEventHandler::ComputeVehicleHitAndRunResponse(CEvent* event, CTask* task1, CTask* task2) {
    // NOP
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
    return plugin::CallMethod<0x4C3870, CEventHandler*, CEvent*, CTask*>(this, event, task);

    m_physicalResponseTask = nullptr;
    m_eventResponseTask = nullptr;
    m_attackTask = nullptr;
    m_sayTask = nullptr;
    m_partialAnimTask = nullptr;

    CTask* task1 = m_ped->GetTaskManager().GetActiveTask();
    CTask* task2 = nullptr;
    if (task1)
        task2 = m_ped->GetTaskManager().GetSimplestActiveTask();

    DEV_LOG("event: {} task1: {} task2: {}", (int32)event->GetEventType(), (int32)task1->GetTaskType(), (int32)task2->GetTaskType()); // NOTSA

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
        if (!m_ped->bIsStanding) {
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
}

// 0x4C4220
CTask* CEventHandler::ComputeEventResponseTask(const CPed& ped, const CEvent& e) {
    CTask* task = nullptr;

    CEventHandler eh{const_cast<CPed*>(&ped)};
    eh.ComputeEventResponseTask(const_cast<CEvent*>(&e), nullptr);
    if (eh.m_eventResponseTask) {
        task = eh.m_eventResponseTask;
        eh.m_eventResponseTask = nullptr;
    }
    eh.Flush();
    delete eh.m_history.m_tempEvent;
    delete eh.m_history.m_nonTempEvent;
    delete eh.m_history.m_storedActiveEvent;

    return task;
}
