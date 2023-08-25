#include "StdInc.h"

#include "EventHandler.h"

#include "Tasks/TaskTypes/TaskSimpleStandStill.h"
#include "Tasks/TaskTypes/TaskComplexInAirAndLand.h"
#include "Tasks/TaskTypes/TaskComplexStuckInAir.h"
#include "Tasks/TaskTypes/TaskComplexFacial.h"
#include "Tasks/TaskTypes/TaskSimpleWaitUntilAreaCodesMatch.h"
#include "Tasks/TaskTypes/TaskComplexUseEffect.h"
#include "Tasks/TaskTypes/TaskComplexKillPedOnFoot.h"
#include "Tasks/TaskTypes/SeekEntity/TaskComplexSeekEntity.h"
#include "Tasks/TaskTypes/TaskComplexWalkRoundObject.h"
#include "Tasks/TaskTypes/TaskSimpleGoTo.h"
#include "Tasks/TaskTypes/TaskSimpleHitHead.h"
#include "Tasks/TaskTypes/TaskComplexEnterCarAsPassengerWait.h"
#include "Tasks/TaskTypes/TaskComplexWalkRoundBuildingAttempt.h"
#include "Tasks/TaskTypes/TaskComplexMoveBackAndJump.h"
#include "Tasks/TaskTypes/TaskComplexJump.h"
#include "Tasks/TaskTypes/TaskComplexGangFollower.h"
#include "Tasks/TaskTypes/TaskSimpleClimb.h"
#include "Tasks/TaskTypes/TaskComplexLeaveCar.h"
#include "Tasks/TaskTypes/TaskComplexPartnerChat.h"
#include "Tasks/TaskTypes/TaskComplexPartnerDeal.h"
#include "Tasks/TaskTypes/TaskComplexPartnerGreet.h"
#include "Tasks/TaskTypes/TaskComplexCarDriveMission.h"
#include "Tasks/TaskTypes/TaskComplexSmartFleeEntity.h"
#include "Tasks/TaskTypes/TaskComplexInvestigateDeadPed.h"
#include "Tasks/TaskTypes/TaskSimpleDuck.h"
#include "Tasks/TaskTypes/TaskSimpleDead.h"
#include "Tasks/TaskTypes/TaskComplexGangJoinRespond.h"
#include "Tasks/TaskTypes/TaskComplexEnterCarAsDriver.h"
#include "Tasks/TaskTypes/TaskComplexEnterCarAsPassenger.h"
#include "Tasks/TaskTypes/TaskSimplePause.h"
#include "Tasks/TaskTypes/TaskSimpleAchieveHeading.h"
#include "Tasks/TaskTypes/TaskSimpleShakeFist.h"
#include "Tasks/TaskTypes/TaskComplexStealCar.h"
#include "Tasks/TaskTypes/TaskComplexDragPedFromCar.h"
#include "Tasks/TaskTypes/TaskComplexKillCriminal.h"
#include "Tasks/TaskTypes/TaskComplexDestroyCar.h"
#include "Tasks/TaskTypes/TaskComplexExtinguishFires.h"
#include "Tasks/TaskTypes/TaskComplexUseClosestFreeScriptedAttractor.h"
#include "Tasks/TaskTypes/TaskComplexUseClosestFreeScriptedAttractorRun.h"
#include "Tasks/TaskTypes/TaskComplexUseClosestFreeScriptedAttractorSprint.h"
#include "Tasks/TaskTypes/TaskSimpleCower.h"
#include "Tasks/TaskTypes/TaskSimpleHandsUp.h"
#include "Tasks/TaskTypes/TaskComplexReactToGunAimedAt.h"
#include "Tasks/TaskTypes/TaskComplexKillPedOnFootStealth.h"
#include "Tasks/TaskTypes/TaskComplexCarDriveMission.h"
#include "Tasks/TaskTypes/TaskComplexFleeEntity.h"
#include "Tasks/TaskTypes/TaskComplexFleeAnyMeans.h"
#include "Tasks/TaskTypes/TaskComplexDie.h"
#include "Tasks/TaskTypes/TaskSimpleStealthKill.h"
#include "Tasks/TaskTypes/TaskComplexFallToDeath.h"
#include "Tasks/TaskTypes/TaskSimpleFall.h"
#include "Tasks/TaskTypes/TaskSimpleGetUp.h"
#include "Tasks/TaskTypes/TaskSimpleUseGun.h"
#include "Tasks/TaskTypes/TaskSimpleGunControl.h"
#include "Tasks/TaskTypes/TaskSimpleChoking.h"
#include "Tasks/TaskTypes/TaskSimpleBeHit.h"
#include "Tasks/TaskTypes/TaskComplexFallAndGetUp.h"
#include "Tasks/TaskTypes/TaskComplexInWater.h"
#include "Tasks/TaskTypes/Interior/TaskInteriorUseInfo.h"
#include "Tasks/TaskTypes/TaskComplexDiveFromAttachedEntityAndGetUp.h"
#include "Tasks/TaskTypes/TaskComplexWalkRoundObject.h"
#include "Tasks/TaskTypes/TaskSimplePlayerOnFire.h"
#include "Tasks/TaskTypes/TaskComplexOnFire.h"

#include "InterestingEvents.h"
#include "IKChainManager_c.h"

#include "Events/EventOnFire.h"
#include "Events/PotentialWalkIntoEvents.h"
#include "Events/EventLowAngerAtPlayer.h"
#include "Events/EventInteriorUseInfo.h"
#include "Events/EventInWater.h"
#include "Events/MentalStateEvents.h"
#include "Events/EventSexyVehicle.h"
#include "Events/EventDamage.h"
#include "Events/EventGunAimedAt.h"
#include "Events/EventDraggedOutCar.h"
#include "Events/EventGotKnockedOverByCar.h"
#include "Events/GroupEvents.h"
#include "Events/EventDeath.h"
#include "Events/EventDeadPed.h"
#include "Events/EventDanger.h"
#include "Events/EventCreatePartnerTask.h"
#include "Events/EventCopCarBeingStolen.h"
#include "Events/EventChatPartner.h"
#include "Events/EventAttractor.h"
#include "Events/EntityCollisionEvents.h"
#include "Events/EventCarUpsideDown.h"
#include "Events/EventFireNearby.h"

constexpr auto fSafeDistance = 60.f;

void CEventHandler::InjectHooks() {
    RH_ScopedClass(CEventHandler);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4C3E80);
    RH_ScopedInstall(Destructor, 0x4C3EC0);

    RH_ScopedInstall(Flush, 0x4C3790);
    RH_ScopedInstall(FlushImmediately, 0x4C3820);
    RH_ScopedInstall(GetCurrentEventType, 0x4B8CC0);
    RH_ScopedInstall(HandleEvents, 0x4C3F10);
    RH_ScopedInstall(IsKillTaskAppropriate, 0x4BC3E0);
    RH_ScopedInstall(IsTemporaryEvent, 0x4BC370);
    // RH_ScopedInstall(RecordActiveEvent, 0x0, { .reversed = false });
    // RH_ScopedInstall(RecordPassiveEvent, 0x0, { .reversed = false });
    RH_ScopedInstall(RegisterKill, 0x4B9340);
    RH_ScopedInstall(SetEventResponseTask, 0x4BC600);
    RH_ScopedInstall(ComputeAreaCodesResponse, 0x4BBF50);
    RH_ScopedInstall(ComputeAttractorResponse, 0x4B9BE0);
    // RH_ScopedInstall(ComputeBuildingCollisionPassiveResponse, 0x0, { .reversed = false });
    RH_ScopedInstall(ComputeBuildingCollisionResponse, 0x4BF2B0);
    RH_ScopedInstall(ComputeCarUpsideDownResponse, 0x4BBC30);
    RH_ScopedInstall(ComputeChatPartnerResponse, 0x4B98E0);
    RH_ScopedInstall(ComputeCopCarBeingStolenResponse, 0x4BB740);
    RH_ScopedInstall(ComputeCreatePartnerTaskResponse, 0x4BB130);
    RH_ScopedInstall(ComputeDamageResponse, 0x4C0170);
    RH_ScopedInstall(ComputeDangerResponse, 0x4BC230);
    RH_ScopedInstall(ComputeDeadPedResponse, 0x4B9470);
    RH_ScopedInstall(ComputeDeathResponse, 0x4B9400);
    RH_ScopedInstall(ComputeDontJoinGroupResponse, 0x4BC1D0);
    RH_ScopedInstall(ComputeDraggedOutCarResponse, 0x4BCC30);
    RH_ScopedInstall(ComputeFireNearbyResponse, 0x4BBFB0);
    RH_ScopedInstall(ComputeGotKnockedOverByCarResponse, 0x4C3430);
    RH_ScopedInstall(ComputeGunAimedAtResponse, 0x4C2840);
    RH_ScopedInstall(ComputeHighAngerAtPlayerResponse, 0x4BAC10);
    RH_ScopedInstall(ComputeInWaterResponse, 0x4BAF80);
    RH_ScopedInstall(ComputeInteriorUseInfoResponse, 0x4BAFE0);
    RH_ScopedInstall(ComputeKnockOffBikeResponse, 0x4B9FF0, { .reversed = false });
    RH_ScopedInstall(ComputeLowAngerAtPlayerResponse, 0x4BAAD0);
    RH_ScopedInstall(ComputeLowHealthResponse, 0x4BA990);
    RH_ScopedInstall(ComputeObjectCollisionPassiveResponse, 0x4BBB90);
    RH_ScopedInstall(ComputeObjectCollisionResponse, 0x4B92B0);
    RH_ScopedInstall(ComputeOnEscalatorResponse, 0x4BC150);
    RH_ScopedInstall(ComputeOnFireResponse, 0x4BAD50);
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
CEventHandler::CEventHandler(CPed* ped) :
    m_ped{ped}
{
}

// 0x4C3F10
void CEventHandler::HandleEvents() {
    m_history.TickStoredEvent(m_ped);

    const auto lastAbortedTask  = m_history.m_AbortedTask;

    const auto pedTM                   = &m_ped->GetTaskManager();
    const auto primaryTask             = m_ped->GetIntelligence()->GetActivePrimaryTask();
    const auto tempEventRespTask       = pedTM->GetTemporaryEventResponseTask();
    const auto presistentEventRespTask = pedTM->GetPresistentEventResponseTask();

    const auto pedEG                = &m_ped->GetEventGroup();
    const auto highestPriorityEvent = pedEG->GetHighestPriorityEvent();

    pedEG->TickEvents();

    m_history.RecordAbortedTask(!lastAbortedTask || !primaryTask || lastAbortedTask != primaryTask ? nullptr : primaryTask);

    if (!tempEventRespTask) {
        if (!presistentEventRespTask) {
            m_history.RecordAbortedTask(nullptr);
        }
        m_history.ClearTempEvent();
    }

    if (!presistentEventRespTask) {
        m_history.ClearNonTempEvent();
    }

    if (const auto priorityEvent = pedEG->GetHighestPriorityEvent()) {
        if (priorityEvent->GetEventType() == EVENT_DAMAGE) { // 0x4C4004
            m_ped->SetIsStatic(false);
        }

        if (const auto currEvent = m_history.GetCurrentEvent()) { // 0x4C4015
            if (currEvent->GetEventType() == highestPriorityEvent->GetEventType()) {
                pedEG->Remove(highestPriorityEvent);
                pedEG->RemoveInvalidEvents(false);
                pedEG->Reorganise();
                if (!primaryTask) {
                    m_history.RecordAbortedTask(nullptr);
                    m_history.ClearAllEvents();
                }
                return;
            }
        }

        if (m_history.TakesPriorityOverCurrentEvent(*priorityEvent)) { // 0x4C40DE
            const auto activeTask = pedTM->GetActiveTask();

            const auto hasStoppedTimers = [&]{
                if (!activeTask || activeTask->MakeAbortable(m_ped, ABORT_PRIORITY_URGENT, priorityEvent)) {
                    pedTM->StopTimers(priorityEvent);
                    return true;
                }
                return false;
            }();

            if (primaryTask) {
                if (!hasStoppedTimers) { // 0x4C41A9
                    priorityEvent->UnTick();
                    activeTask->MakeAbortable(m_ped, ABORT_PRIORITY_LEISURE, priorityEvent);
                    m_history.RecordAbortedTask(activeTask);
                    pedEG->RemoveInvalidEvents(false);
                    pedEG->Reorganise();
                    return;
                } else {
                    ComputeEventResponseTask(priorityEvent, lastAbortedTask);
                    m_history.RecordAbortedTask(nullptr);
                    if (m_eventResponseTask) {
                        m_history.RecordCurrentEvent(m_ped, *priorityEvent);
                    }
                }
            } else if (lastAbortedTask) { // 0x4C4176
                ComputeEventResponseTask(priorityEvent, lastAbortedTask);
                m_history.RecordAbortedTask(nullptr);
                if (m_eventResponseTask) {
                    m_history.RecordCurrentEvent(m_ped, *priorityEvent);
                }
            } else { // 0x4C4135
                if (!hasStoppedTimers) {
                    priorityEvent->UnTick();
                    pedEG->RemoveInvalidEvents(false);
                    pedEG->Reorganise();
                    return;
                } else {
                    ComputeEventResponseTask(priorityEvent, lastAbortedTask);
                    if (m_eventResponseTask) {
                        m_history.RecordCurrentEvent(m_ped, *priorityEvent);
                    }
                }
            }
            SetEventResponseTask(*priorityEvent);
            pedEG->Remove(priorityEvent);
        }
        pedEG->RemoveInvalidEvents(false);
        pedEG->Reorganise();
    } else if (!primaryTask) {
        m_history.RecordAbortedTask(nullptr);
        m_history.ClearAllEvents();
    }
}

void CEventHandler::RecordActiveEvent(const CEvent& event) {
    assert(false);
}

void CEventHandler::RecordPassiveEvent(const CEvent& event) {
    assert(false);
}

// 0x4B9340
void CEventHandler::RegisterKill(const CPed* ped, const CEntity* inflictedBy, eWeaponType weaponUsed, bool wasHeadShot) {
    if (!ped) {
        return;
    }
    if (inflictedBy && inflictedBy->IsPed() && inflictedBy->AsPed()->IsPlayer() && inflictedBy != ped) {
        const auto pi = &FindPlayerInfo();
        pi->m_nHavocCaused += 10;
        pi->m_fCurrentChaseValue += 5.f;
        CDarkel::RegisterKillByPlayer(*ped, weaponUsed, wasHeadShot, inflictedBy->AsPed()->m_nPedType);
        CPedGroups::RegisterKillByPlayer();
    } else if (inflictedBy && inflictedBy->IsVehicle() && inflictedBy == FindPlayerVehicle()) {
        CStats::IncrementStat(STAT_PEOPLE_YOUVE_WASTED);
    } else {
        CDarkel::RegisterKillNotByPlayer(ped);
    }
}

// 0x4BC600
void CEventHandler::SetEventResponseTask(const CEvent& event) {
    const auto i  = m_ped->GetIntelligence();
    const auto tm = &i->m_TaskMgr;

    if (m_physicalResponseTask) {
        i->AddTaskPhysResponse(m_physicalResponseTask, true);
    }

    if (m_eventResponseTask) {
        if (IsTemporaryEvent(event)) {
            i->AddTaskEventResponseTemp(m_eventResponseTask, false);
        } else {
            i->AddTaskEventResponseTemp(nullptr, 0);
            i->AddTaskEventResponseNonTemp(m_eventResponseTask, false);
        }
    }

    if (m_attackTask) {
        if (const auto tattack = tm->GetTaskSecondary(TASK_SECONDARY_ATTACK)) {
            tattack->MakeAbortable(m_ped);
        }
        tm->SetTaskSecondary(m_attackTask, TASK_SECONDARY_ATTACK);
    }

    if (m_sayTask) {
        tm->SetTaskSecondary(m_sayTask, TASK_SECONDARY_SAY);
    }

    if (m_partialAnimTask) {
        tm->SetTaskSecondary(m_partialAnimTask, TASK_SECONDARY_PARTIAL_ANIM);
    }

    if (event.HasEditableResponse()) {
        const auto eeditable = &static_cast<const CEventEditableResponse&>(event);
        if (const auto tfacial = tm->GetTaskSecondaryFacial()) {
            if (eeditable->GetFacialExpressionType() != eFacialExpression::NONE) {
                tfacial->SetRequest(eeditable->GetFacialExpressionType(), 10'000);
            }
        }
    }
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
eEventType CEventHandler::GetCurrentEventType() const {
    if (const auto e = m_history.GetCurrentEvent()) {
        return e->GetEventType();
    }
    return EVENT_NONE;
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
    return !ped1->IsCreatedByMission() && (!ped1->GetActiveWeapon().IsTypeMelee() || ped2->GetActiveWeapon().IsTypeMelee());
}

// 0x4BBF50
void CEventHandler::ComputeAreaCodesResponse(CEventAreaCodes* e, CTask* tactive, CTask* tsimplest) {
    if (!e->m_ped) {
        return;
    }
    m_eventResponseTask = new CTaskSimpleWaitUntilAreaCodesMatch{e->m_ped};
}

// 0x4B9BE0
void CEventHandler::ComputeAttractorResponse(CEventAttractor* e, CTask* tactive, CTask* tsimplest) {
    if (e->GetEventType() == EVENT_ATTRACTOR && !e->m_entity) {
        return;
    }
    if (e->m_taskId == TASK_NONE) {
        m_eventResponseTask = nullptr;
    } else if (e->m_taskId == TASK_COMPLEX_USE_EFFECT) {
        if (GetPedAttractorManager()->HasEmptySlot(e->m_2dEffect, e->m_entity)) { // inverted
            m_eventResponseTask = new CTaskComplexUseEffect{e->m_2dEffect, e->m_entity};
        }
    }
}

// 0x0
// EVENT_POTENTIAL_WALK_INTO_BUILDING
// ANDROID IDB 0x3025F8 (1.0)
void CEventHandler::ComputeBuildingCollisionPassiveResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    // NOP
}

// 0x4BF2B0
void CEventHandler::ComputeBuildingCollisionResponse(CEventBuildingCollision* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!tactive || !e->m_building || e->m_moveState == PEDMOVE_STILL) {
            return nullptr;
        }

        const auto tm = &m_ped->GetTaskManager();

        const auto tKillPedOnFoot    = tm->Find<CTaskComplexKillPedOnFoot>(false);
        const auto tSeekEntity       = tm->Find<CTaskComplexSeekEntity<>>(false); // Hackery, because we don't know what `T_PosCalc` actually is...
        const auto tEnterCarPsgrWait = tm->Find<CTaskComplexEnterCarAsPassengerWait>(false);
        const auto tGoToPoint        = CTask::IsGoToTask(tsimplest)
            ? static_cast<CTaskSimpleGoTo*>(tsimplest)
            : nullptr;

        const auto isHeadOnCollision = e->IsHeadOnCollision(m_ped) ;

        if (e->CanTreatBuildingAsObject(e->m_building)) { // 0x4BF36E
            if (tGoToPoint) {
                return new CTaskComplexWalkRoundObject{
                    e->m_moveState,
                    tGoToPoint->m_vecTargetPoint,
                    e->m_building
                };
            }
            return nullptr;
        }

        const auto randomBool = CGeneral::RandomBool(1.f / 15.f * 100.f); // 0x4BF3D4

        if (m_ped->bIsStanding && e->m_impactNormal.z > COS_45) { // 0x4BF3FE
            return nullptr;
        }

        if (!tGoToPoint && (!tKillPedOnFoot || !tKillPedOnFoot->m_target)) { // 0x4BF41E
            if (isHeadOnCollision && !CPedGeometryAnalyser::CanPedJumpObstacle(*m_ped, *e->m_building, e->m_impactNormal, e->m_impactPos) && e->m_moveState > eMoveState::PEDMOVE_WALK) {
                return new CTaskSimpleHitHead{};
            }
        }

        if (isHeadOnCollision) { // 0x4BF4D1
            if (!tSeekEntity && !tKillPedOnFoot && !tEnterCarPsgrWait && !randomBool) {
                return new CTaskComplexWalkRoundBuildingAttempt{
                    (eMoveState)e->m_moveState,
                    tGoToPoint->m_vecTargetPoint,
                    e->m_impactPos,
                    e->m_impactNormal,
                    isHeadOnCollision
                };
            }

            if (CPedGeometryAnalyser::CanPedJumpObstacle(*m_ped, *e->m_building, e->m_impactNormal, e->m_impactPos)) { // 0x4BF540
                if (e->m_moveState > eMoveState::PEDMOVE_WALK) {
                    return new CTaskComplexMoveBackAndJump{};
                }
                return new CTaskComplexJump{COMPLEX_JUMP_TYPE_JUMP};
            }

            if (tKillPedOnFoot) { // 0x4BF5C2
                if (!tKillPedOnFoot->m_target) {
                    return nullptr;
                }
                if (CPedGeometryAnalyser::CanPedTargetPed(*m_ped, *tKillPedOnFoot->m_target, true)) {
                    return nullptr;
                }
                return new CTaskComplexWalkRoundBuildingAttempt{
                    (eMoveState)e->m_moveState,
                    tKillPedOnFoot->m_target,
                    {},
                    e->m_impactPos,
                    e->m_impactNormal,
                    isHeadOnCollision
                };
            }

            CEntity* targetEntity{};
            if (tSeekEntity) { // 0x4BF660
                targetEntity = tSeekEntity->GetEntityToSeek();
            } else if (!tEnterCarPsgrWait) { // 0x4BF664
                return new CTaskComplexWalkRoundBuildingAttempt{
                    (eMoveState)e->m_moveState,
                    tGoToPoint->m_vecTargetPoint, // For this code path to be reachable the code at 0x4BF47F can't be reachable, thus we use `tGoToPoint->m_vecTargetPoint`
                    e->m_impactPos,
                    e->m_impactNormal,
                    isHeadOnCollision
                };
            } else if (const auto targetv = tEnterCarPsgrWait->GetTarget()) {
                targetEntity = targetv->m_pDriver;
            } else {
                return nullptr;
            }

            if (!targetEntity) { // 0x4BF6A6
                return nullptr;
            }

            if (CTaskComplexGangFollower::ms_bUseClimbing) { // 0x4BF6B3
                if (CPedGroups::IsInPlayersGroup(m_ped)) {
                    CVector climbPos;
                    float   climbGrabHeading;
                    uint8   climbSurfaceType;
                    if (const auto entityToClimb = CTaskSimpleClimb::TestForClimb(m_ped, climbPos, climbGrabHeading, climbSurfaceType, true)) {
                        return new CTaskSimpleClimb{
                            entityToClimb,
                            climbPos,
                            climbGrabHeading,
                            climbSurfaceType,
                            climbPos.z - m_ped->GetPosition().z < CTaskSimpleClimb::ms_fMinForStretchGrab ? CLIMB_PULLUP : CLIMB_GRAB,
                            true
                        };
                    }
                }
            }

            if (targetEntity->IsPed()) {
                if (!g_ikChainMan.IsLooking(m_ped)) { // 0x4BF77F
                    g_ikChainMan.LookAt(
                        "CompBldgCollResp",
                        m_ped,
                        targetEntity,
                        3'000,
                        BONE_HEAD,
                        nullptr,
                        true,
                        0.25f,
                        500,
                        3,
                        false
                    );
                }
                /* nop GetTaskSecondary */
            }

            return new CTaskComplexWalkRoundBuildingAttempt{ // 0x4BF814
                (eMoveState)e->m_moveState,
                targetEntity,
                {},
                e->m_impactPos,
                e->m_impactNormal,
                isHeadOnCollision
            };
        } else {
            const auto DoWalkAroundBuldingTask = [&](CEntity* aroundEntity) {
                if (aroundEntity) {
                    return new CTaskComplexWalkRoundBuildingAttempt{
                        (eMoveState)e->m_moveState,
                        aroundEntity,
                        {},
                        e->m_impactPos,
                        e->m_impactNormal,
                        false
                    }; 
                }
                return new CTaskComplexWalkRoundBuildingAttempt{
                    (eMoveState)e->m_moveState,
                    tGoToPoint->m_vecTargetPoint, // For this code path to be reachable the code at 0x4BF47F can't be reachable, thus we use `tGoToPoint->m_vecTargetPoint`
                    e->m_impactPos,
                    e->m_impactNormal,
                    false
                };
            };
            if (tKillPedOnFoot) { // 0x004BF825
                return DoWalkAroundBuldingTask(tKillPedOnFoot->m_target);
            } else if (tSeekEntity) { // 0x4BF8C3
                return DoWalkAroundBuldingTask(tSeekEntity->GetEntityToSeek());
            }
        }
        return nullptr;
    }();
}

// 0x4BBC30
void CEventHandler::ComputeCarUpsideDownResponse(CEventCarUpsideDown* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!m_ped->IsInVehicle() || m_ped->m_pVehicle != e->m_vehicle) {
            return nullptr;
        }
        return new CTaskComplexLeaveCar{
            e->m_vehicle,
            0,
            CGeneral::GetRandomNumberInRange(100, 400),
            true,
            false
        };
    }();
}

// 0x4B98E0
void CEventHandler::ComputeChatPartnerResponse(CEventChatPartner* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!e->m_partner || m_ped->GetTaskManager().Has<CTaskComplexPartnerChat>(false)) {
            return nullptr;
        }
        return new CTaskComplexPartnerChat{
            "EventChatPartnerResponse",
            e->m_partner,
            e->m_leadSpeaker,
            0.5f,
            4,
            true,
            false,
            {}
        };
    }();
}

// 0x4BB740
void CEventHandler::ComputeCopCarBeingStolenResponse(CEventCopCarBeingStolen* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!e->m_hijacker || !e->m_vehicle || m_ped->GetVehicleIfInOne() != e->m_vehicle) {
            return nullptr;
        }
        if (e->m_hijacker->IsPlayer()) {
            FindPlayerWanted()->SetWantedLevelNoDrop(1);
        }
        return new CTaskComplexLeaveCar{ e->m_vehicle, 0, 0, true, false };
    }();
}

// 0x4BB130
void CEventHandler::ComputeCreatePartnerTaskResponse(CEventCreatePartnerTask* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!e->m_partner) {
            return nullptr;
        }
        switch (e->m_partnerType) {
        case 0:
            return new CTaskComplexPartnerDeal{
                "CompPartnerTaskResp",
                e->m_partner,
                e->m_isLeadSpeaker,
                e->m_meetDist,
                {}
            };
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6: 
            return new CTaskComplexPartnerGreet{
                "CompPartnerTaskResp",
                e->m_partner,
                e->m_isLeadSpeaker,
                e->m_meetDist,
                e->m_partnerType - 1,
                {}
            };
        default:
            return nullptr;
        }
    }();
}

// 0x4C0170
void CEventHandler::ComputeDamageResponse(CEventDamage* e, CTask* tactive, CTask* tsimplest, CTask* abortedTaskEventResponse) {
    m_eventResponseTask = [&]() -> CTask* {
        const auto DoComputeDamageAndResponseForPersonality = [&] {
            const auto ce = m_history.GetCurrentEvent();
            if (!ce || ce->GetEventType() != EVENT_DAMAGE || !e->IsSameEventForAI(static_cast<CEventDamage&>(*ce))) {
                if (!m_ped->GetTaskManager().Has<TASK_COMPLEX_REACT_TO_ATTACK>() && !m_ped->IsPlayer()) {
                    if (const auto esrc = e->GetSourceEntity()) {
                        if (esrc->IsPed()) {
                            ComputePersonalityResponseToDamage(e, esrc);
                        }
                    }
                }
            }
            return m_eventResponseTask;
        };

        if (!e->m_bAddToEventGroup) {
            // NOTE(Pirulax): Originally the code here used `e->m_pSourceEntity`, but that was probably just a mistake, as the other code piece [copy paste of it] used `e->GetSourceEntity()`.
            return DoComputeDamageAndResponseForPersonality();
        }

        e->ProcessDamage(m_ped);

        switch (e->m_weaponType) {
        case WEAPON_RAMMEDBYCAR:
        case WEAPON_RUNOVERBYCAR:
            g_InterestingEvents.Add(CInterestingEvents::INTERESTING_EVENT_15, m_ped);
        }

        if (const auto v = m_ped->GetVehicleIfInOne()) {
            if (v->IsBike() || v->IsSubQuad()) {
                if (!e->m_bFallDown && !e->HasKilledPed()) {
                    ComputePersonalityResponseToDamage(e, e->m_pSourceEntity);
                } else {
                    ComputeKnockOffBikeResponse(e, tactive, tsimplest); // 0x4C02DE
                }
                return m_eventResponseTask;
            }
        }

        if (e->HasKilledPed() || m_ped->m_fHealth < 1.f || (m_ped->bInVehicle && e->m_bFallDown)) { // 0x4C0315
            if (const auto v = m_ped->GetVehicleIfInOne()) {
                if (v->IsBike() || v->IsSubQuad()) { // 0x4C07E5
                    ComputeKnockOffBikeResponse(e, tactive, tsimplest);
                    return m_eventResponseTask;
                }
            }

            // TODO(Pirulax):
            // Eventually remove these lambdas.
            // I'm pretty sure this code can be linearized, but first I want to make sure it actually works :D
            const auto DoDie = [&](bool bFallingToDeath = false, eDirection fallToDeathDir = eDirection::FORWARD, bool bFallToDeathOverRailing = false) { // 0x4C0AA2
                g_InterestingEvents.Add(CInterestingEvents::INTERESTING_EVENT_28, m_ped);
                if (const auto tPhyResp = m_ped->GetTaskManager().GetTaskPrimary(TASK_PRIMARY_PHYSICAL_RESPONSE)) {
                    if (tPhyResp->GetTaskType() != TASK_SIMPLE_CHOKING || !notsa::contains({ WEAPON_SPRAYCAN, WEAPON_EXTINGUISHER, WEAPON_TEARGAS }, e->m_weaponType)) {
                        m_ped->GetIntelligence()->AddTaskPhysResponse(nullptr);
                    }
                }

                if (e->m_pSourceEntity) {
                    RegisterKill(m_ped, e->m_pSourceEntity, e->m_weaponType, e->WasHeadShot());
                }

                return new CTaskComplexDie{
                    e->m_weaponType,
                    e->m_nAnimGroup,
                    e->m_nAnimID,
                    e->m_fAnimBlend,
                    e->m_fAnimSpeed,
                    tactive && tactive->GetTaskType() == TASK_SIMPLE_STEALTH_KILL && !static_cast<CTaskSimpleStealthKill*>(tactive)->m_bKeepTargetAlive,
                    bFallingToDeath,
                    fallToDeathDir,
                    bFallToDeathOverRailing
                };
            };

            const auto DoDieMaybeFall = [&]{ // 0x4C0A1C
                if (notsa::contains({ ANIM_ID_NO_ANIMATION_SET, ANIM_ID_DOOR_LHINGE_O }, e->m_nAnimID)) {
                    e->ComputeDeathAnim(m_ped, false);
                }
                if (!m_ped->IsPlayer() && e->m_pSourceEntity) {
                    if (notsa::contains({
                        WEAPON_PISTOL,
                        WEAPON_PISTOL_SILENCED,
                        WEAPON_DESERT_EAGLE,
                        WEAPON_SHOTGUN,
                        WEAPON_SAWNOFF_SHOTGUN,
                        WEAPON_SPAS12_SHOTGUN,
                        WEAPON_MICRO_UZI,
                        WEAPON_MP5,
                        WEAPON_AK47,
                        WEAPON_M4,
                        WEAPON_TEC9,
                        WEAPON_COUNTRYRIFLE,
                        WEAPON_MINIGUN
                    }, e->m_weaponType)) {
                        if (e->m_pSourceEntity->IsPed() && e->m_pSourceEntity->AsPed()->IsCreatedByMission()) {
                            int32 fallToDeathDir;
                            bool  bFallToDeathOverRailing;
                            bool  bFallToDeath = CTaskComplexFallToDeath::CalcFall(m_ped, fallToDeathDir, bFallToDeathOverRailing);
                            return DoDie(bFallToDeath, (eDirection)(fallToDeathDir), bFallToDeathOverRailing);
                        }
                    }
                }
                return DoDie();
            };

            if (!notsa::contains({ ANIM_ID_NO_ANIMATION_SET, ANIM_ID_DOOR_LHINGE_O }, e->m_nAnimID)) {
                return DoDie();
            }

            if (!tsimplest) {
                return DoDieMaybeFall();
            }

            switch (tsimplest->GetTaskType()) {
            case TASK_SIMPLE_FALL: {
                if (const auto dr = &e->m_damageResponse; e->m_weaponType == WEAPON_FALL && dr->m_fDamageArmor + dr->m_fDamageHealth >= 20.f) { // 0x4C083E - Add blood
                    for (auto i = 10; i-- > 0;) {
                        g_fx.AddBlood(
                            m_ped->GetPosition() + CVector::Random({-0.5f, -0.5f, 0.f}, {0.5f, 0.5f, 0.f}),
                            {0.f, 0.f, 2.f},
                            10,
                            m_ped->m_fContactSurfaceBrightness
                        );
                    }
                }
                const auto tfall = CTask::Cast<CTaskSimpleFall>(tsimplest);
                if (const auto a = tfall->m_pAnim) { // 0x4C08ED
                    if (a->m_fBlendAmount > 0.5f && a->m_fBlendDelta >= 0.f && a->m_fCurrentTime < a->m_pHierarchy->m_fTotalTime) {
                        e->m_nAnimGroup = (AssocGroupId)a->m_nAnimGroup;
                        e->m_nAnimID    = (AnimationId)a->m_nAnimId;
                        e->m_fAnimBlend = 4.f;
                        e->m_fAnimSpeed = 1.f;
                        return DoDieMaybeFall();
                    }
                }
                if (!tfall->m_bIsFinished) {
                    return DoDieMaybeFall();
                }
                e->m_fAnimBlend = 4.f;
                e->m_fAnimSpeed = 1.f;
                e->m_nAnimGroup = ANIM_GROUP_DEFAULT;
                if (const auto a = RpAnimBlendClumpGetFirstAssociation(m_ped->m_pRwClump, ANIMATION_800)) { // 0x4C094E
                    e->m_nAnimID = ANIM_ID_FLOOR_HIT_F;
                    return DoDieMaybeFall();
                }
                break;
            }
            case TASK_SIMPLE_GET_UP: { // 0x4C0987
                const auto tgup = CTask::Cast<CTaskSimpleGetUp>(tsimplest);
                if (!tgup->m_Anim || tgup->m_Anim->GetTimeProgress() >= 0.5f) {
                    if (tgup->m_bHasPedGotUp) {
                        return DoDieMaybeFall();
                    }
                    e->m_nAnimID = RpAnimBlendClumpGetFirstAssociation(m_ped->m_pRwClump, ANIMATION_800)
                        ? ANIM_ID_FLOOR_HIT_F
                        : ANIM_ID_FLOOR_HIT;
                    
                } else if (!tgup->m_bHasPedGotUp) {
                    e->m_nAnimID = tgup->m_Anim->m_nAnimId == ANIM_ID_GETUP_FRONT
                        ? ANIM_ID_FLOOR_HIT_F
                        : ANIM_ID_FLOOR_HIT;
                }
                e->m_nAnimGroup = ANIM_GROUP_DEFAULT;
                e->m_fAnimBlend = 4.f;
                e->m_fAnimSpeed = 1.f;
                return DoDieMaybeFall();
            }
            default:
                return DoDieMaybeFall();
            }
        }

        if (!e->m_pSourceEntity) {
            return nullptr;
        }

        if (CWeaponInfo::TypeIsWeapon(e->m_weaponType)) {
            if (m_ped->bInVehicle) { // 0x4C0332
                return DoComputeDamageAndResponseForPersonality();
            }

            const auto eventSrcPed = e->m_pSourceEntity->IsPed()
                ? e->m_pSourceEntity->AsPed()
                : nullptr;

            if (eventSrcPed) { // 0x4C0338
                if (const auto killerStealthTask = eventSrcPed->GetTaskManager().GetActiveTaskAs<CTaskSimpleStealthKill>()) {
                    m_physicalResponseTask = new CTaskSimpleStealthKill{false, eventSrcPed, killerStealthTask->m_animGrpId};
                    m_ped->SetPedState(PEDSTATE_DIE_BY_STEALTH);
                    return nullptr;
                }
            }

            if (e->m_nAnimID == ANIM_ID_NO_ANIMATION_SET) {
                e->ComputeAnim(m_ped, false);
            }

            // Do choking if it applies to this weapon type
            if (notsa::contains({ WEAPON_SPRAYCAN, WEAPON_EXTINGUISHER, WEAPON_TEARGAS }, e->m_weaponType)) { // 0x4C03F8 - TODO: `WeaponIsChocking`
                if (!notsa::IsFixBugs() || eventSrcPed) { // Original code just crashed at this point
                    const auto t = eventSrcPed->GetIntelligence()->GetTaskUseGun();
                    if (!t || t->GetLastGunCommand() != eGunCommand::PISTOLWHIP) {
                        const auto bIsTearGas = e->m_weaponType == WEAPON_TEARGAS;
                        if (const auto t = CTask::DynCast<CTaskSimpleChoking>(m_ped->GetTaskManager().GetTaskPrimary(TASK_PRIMARY_PHYSICAL_RESPONSE))) {
                            t->UpdateChoke(m_ped, eventSrcPed, bIsTearGas);
                        } else {
                            m_physicalResponseTask = new CTaskSimpleChoking{eventSrcPed, bIsTearGas};
                        }
                        return DoComputeDamageAndResponseForPersonality();
                    }
                }
            }

            // Otherwise
            if (!e->m_bFallDown && !notsa::contains({ ANIM_ID_NO_ANIMATION_SET, ANIM_ID_DOOR_LHINGE_O }, e->m_nAnimID)) {
                if (CAnimManager::GetAnimAssociation(e->m_nAnimGroup, e->m_nAnimID)->m_nFlags & ANIMATION_ADD_TO_BLEND) { // 0x4C04B7
                    if (!e->GetAnimAdded()) {
                        if (!notsa::contains({ANIM_ID_SHOT_PARTIAL, ANIM_ID_SHOT_LEFTP, ANIM_ID_SHOT_PARTIAL_B, ANIM_ID_SHOT_RIGHTP}, e->m_nAnimID)) {
                            const auto a = CAnimManager::BlendAnimation(m_ped->m_pRwClump, e->m_nAnimGroup, e->m_nAnimID, e->m_fAnimBlend);
                            a->SetSpeed(e->m_fAnimSpeed);
                            a->SetCurrentTime(0.f);
                            e->m_bAnimAdded = true;
                        } else {
                            auto a = RpAnimBlendClumpGetAssociation(m_ped->m_pRwClump, e->GetAnimId()); // 0x4C04DE
                            if (!a) {
                                a = CAnimManager::BlendAnimation(m_ped->m_pRwClump, e->GetAnimGroup(), e->GetAnimId());
                            }
                            a->SetBlend(0.f, e->m_fAnimBlend);
                            a->SetSpeed(e->m_fAnimSpeed);
                            a->SetCurrentTime(0.f);
                        }
                    }
                } else { // 0x4C0593 
                    const auto tBeHit = new CTaskSimpleBeHit{
                        eventSrcPed,
                        e->m_pedPieceType,
                        e->m_ucDirection,
                        (int32)e->GetDamageResponse().GetTotalDamage()
                    };
                    m_physicalResponseTask = tBeHit;

                    tBeHit->m_nAnimId    = e->GetAnimId();
                    tBeHit->m_nAnimGroup = e->GetAnimGroup();
                    tBeHit->m_bAnimAdded = e->GetAnimAdded();
                }
            } else {
                m_physicalResponseTask = new CTaskComplexFallAndGetUp{
                    e->GetAnimId(),
                    e->GetAnimGroup(),
                    (int32)(1000.f / ((float)m_ped->m_nWeaponShootingRate / 40.f))
                };
            }

            return DoComputeDamageAndResponseForPersonality();
        }

        if (!m_ped->bInVehicle) { // 0x4C06D9
            if (!notsa::contains({ ANIM_ID_NO_ANIMATION_SET, ANIM_ID_DOOR_LHINGE_O }, e->m_nAnimID)) {
                if (notsa::contains({ WEAPON_RAMMEDBYCAR, WEAPON_RUNOVERBYCAR, WEAPON_FALL }, e->m_weaponType)) {
                    m_physicalResponseTask = new CTaskComplexFallAndGetUp{ // 0x4C0748
                        e->GetAnimId(),
                        e->GetAnimGroup(),
                        m_ped->IsPlayer() ? 500 : 1000
                    };
                    const auto knockedOverByVeh = e->m_pSourceEntity->IsVehicle()
                        ? e->m_pSourceEntity->AsVehicle()
                        : e->m_pSourceEntity->IsPed()
                            ? e->m_pSourceEntity->AsPed()->GetVehicleIfInOne()
                            : nullptr;
                    if (knockedOverByVeh) {
                        m_ped->GetEventGroup().Add(CEventGotKnockedOverByCar{knockedOverByVeh});
                    }
                }
            }
        }

        return nullptr;
    }();
}

// 0x4BC230
void CEventHandler::ComputeDangerResponse(CEventDanger* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!e->m_dangerFrom) {
            return nullptr;
        }
        switch (e->m_taskId) {
        case TASK_COMPLEX_CAR_DRIVE_MISSION_FLEE_SCENE: {
            if (m_ped->bInVehicle) {
                if (!m_ped->m_pVehicle->IsDriver(m_ped)) {
                    return nullptr;
                }
                return new CTaskComplexCarDriveMissionFleeScene{m_ped->m_pVehicle};
            }
            [[fallthrough]];
        }
        case TASK_COMPLEX_SMART_FLEE_ENTITY: {
            return new CTaskComplexSmartFleeEntity{ e->m_dangerFrom, true, 100'000.f };
        }
        }
        return nullptr;
    }();
}

// 0x4B9470
void CEventHandler::ComputeDeadPedResponse(CEventDeadPed* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!e->GetDeadPed()) {
            return nullptr;
        }
        if (m_ped->IsPlayer()) {
            if ((m_ped->GetPosition() - e->GetDeadPed()->GetPosition()).SquaredMagnitude2D() >= sq(0.75f)) {
                return nullptr;
            }
            if (m_ped->GetIntelligence()->GetTaskFighting()) {
                return nullptr;
            }
            if (g_ikChainMan.IsLooking(m_ped)) {
                return nullptr;
            }
            const auto c = &TheCamera.GetActiveCam();
            switch (c->m_nMode) {
            case MODE_SNIPER:
            case MODE_CAMERA:
            case MODE_ROCKETLAUNCHER:
            case MODE_ROCKETLAUNCHER_HS:
            case MODE_M16_1STPERSON:
            case MODE_1STPERSON:
            case MODE_HELICANNON_1STPERSON:
                return nullptr;
            }
            if (c->GetWeaponFirstPersonOn()) {
                return nullptr;
            }
            g_ikChainMan.LookAt(
                "CompDeadPedResp",
                m_ped,
                e->GetDeadPed(),
                500,
                BONE_HEAD,
                nullptr,
                true,
                0.25f,
                500,
                3,
                false
            );
            return nullptr;
        }
        switch (e->m_taskId) {
        case TASK_COMPLEX_SMART_FLEE_ENTITY:
            return new CTaskComplexSmartFleeEntity{e->GetDeadPed(), true, 100'000.f};
        case TASK_COMPLEX_INVESTIGATE_DEAD_PED:
            return new CTaskComplexInvestigateDeadPed{e->GetDeadPed()};
        case TASK_SIMPLE_DUCK_FOREVER:
            return new CTaskSimpleDuck{
                DUCK_STANDALONE,
                57599u,
                -1
            };
        default:
            return nullptr;
        }
    }();
}

// 0x4B9400
void CEventHandler::ComputeDeathResponse(CEventDeath* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = new CTaskSimpleDead{e->GetDeathTime(), e->HasDrowned()};
}

// 0x4BC1D0
void CEventHandler::ComputeDontJoinGroupResponse(CEventDontJoinPlayerGroup* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = new CTaskComplexGangJoinRespond{false};
}

// 0x4BCC30
void CEventHandler::ComputeDraggedOutCarResponse(CEventDraggedOutCar* e, CTask* tactive, CTask* tsimplest) {
    // Pirulax: You gotta love when 500+ sloc is compressed to 100 :D
    m_eventResponseTask = [&]() -> CTask* {
        if (m_ped->IsPlayer() || !e->m_Vehicle) {
            return nullptr;
        }

        if (e->m_Vehicle->GetAnimGroupId() == ANIM_GROUP_COACHCARANIMS) { // 0x4BCC7E
            return new CTaskComplexSmartFleeEntity{e->m_CarJacker, false, fSafeDistance};
        }

        const auto CreateFinalSeq = [&](CTask* response) -> CTask* {
            const auto leaveCarTask = e->m_Vehicle->IsDriver(m_ped) || e->m_Vehicle->GetPassengers()[0] == m_ped // 0x4BCCF2
                ? new CTaskComplexLeaveCar{ e->m_Vehicle, 0, 0, false, true }
                : nullptr;

            if (leaveCarTask && response) { // 0x4BD63A
                return new CTaskComplexSequence{ leaveCarTask, response };
            }

            return leaveCarTask
                ? leaveCarTask // NOTE: Slightly changed the code. Originally it boiled down to `new CTaskComplexSequence{ leaveCarTask, nullptr }`. This way we save an allocation.
                : response;    // `response` might be null, that's fine
        };

        const auto CreateStealCarBackSeq = [&](bool dragOutPedIfPassenger, bool killJacker) {
            const auto s = new CTaskComplexSequence{};

            // Make important life decisions
            if (CGeneral::RandomBool(50.f)) {
                s->AddTask(new CTaskSimplePause{CGeneral::GetRandomNumberInRange(500, 1'500)});
            } else {
                s->AddTasks(
                    new CTaskSimpleAchieveHeading{m_ped, e->m_CarJacker},
                    new CTaskSimpleShakeFist{}
                );
            }

            // Maybe kill the fucker
            if (killJacker) {
                s->AddTask(new CTaskComplexKillPedOnFoot{e->m_CarJacker});
            }

            // Talk a little
            m_ped->Say(120);

            // Try stealing the car back
            if (e->m_IsDriverSeat) {
                s->AddTask(new CTaskComplexStealCar{e->m_Vehicle});
            } else {
                if (dragOutPedIfPassenger) { // TODO/BUG: I really wonder if this is just a bug [that is, that they didn't include this in both [0x4BCF68 and 0x4BD3FA] places]
                    s->AddTask(new CTaskComplexDragPedFromCar{e->m_CarJacker});
                } 
                s->AddTask(new CTaskComplexEnterCarAsPassenger{e->m_Vehicle});
            }

            return CreateFinalSeq(s);
        };
        switch (e->m_taskId) {
        case TASK_NONE: // 0x4BCD68
            return CreateFinalSeq(nullptr); // Nothing to do
        case TASK_SIMPLE_HIT_HEAD: { // 0x4BCD74
            if (e->m_IsDriverSeat) {
                return CreateFinalSeq(new CTaskComplexEnterCarAsDriver{ e->m_Vehicle });
            }
            return CreateFinalSeq(new CTaskComplexEnterCarAsPassenger{ e->m_Vehicle });
        }
        case TASK_COMPLEX_EVASIVE_STEP: { // 0x4BCD85
            return CreateStealCarBackSeq(false, true);
        }
        case TASK_COMPLEX_KILL_CRIMINAL: { // 0x4BD111
            if (!e->m_CarJacker || e->m_CarJacker->IsPlayer()) {
                return CreateFinalSeq(nullptr);
            }
            return CreateFinalSeq(new CTaskComplexKillCriminal{e->m_CarJacker});
        }
        case TASK_COMPLEX_DESTROY_CAR: { // 0x4BD173
            return CreateFinalSeq(new CTaskComplexDestroyCar{e->m_Vehicle});
        }
        case TASK_COMPLEX_KILL_PED_ON_FOOT: { // 0x4BD1B4
            assert(e->m_CarJacker); // There's some code after fleeing, but it makes no sense since `e->m_CarJacker` would be null. Pretty sure they forgot a `break`.
            if (IsKillTaskAppropriate(m_ped, e->m_CarJacker, *e)) {
                return CreateStealCarBackSeq(true, false);
            }
            return CreateFinalSeq(new CTaskComplexSmartFleeEntity{e->m_CarJacker, true, 100'000.f});
        }
        default:
            return nullptr;
        }
    }();
}

// 0x4BBFB0
void CEventHandler::ComputeFireNearbyResponse(CEventFireNearby* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        switch (e->m_taskId) {
        case TASK_COMPLEX_EXTINGUISH_FIRES:
            return new CTaskComplexExtinguishFires{};
        }
        return nullptr;
    }();
}

// 0x4C3430
void CEventHandler::ComputeGotKnockedOverByCarResponse(CEventGotKnockedOverByCar* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!e->m_vehicle) {
            return nullptr;
        }
        const auto drvr = e->m_vehicle->m_pDriver;
        if (!drvr) {
            return nullptr;
        }
        switch (e->m_taskId) {
        case TASK_COMPLEX_KILL_PED_ON_FOOT: { // 0x4C346E
            if (IsKillTaskAppropriate(m_ped, drvr, *e)) {
                return new CTaskComplexKillPedOnFoot{drvr};
            }
            return new CTaskComplexSmartFleeEntity{drvr, true, 100'000.f};
        }
        case TASK_COMPLEX_FLEE_ENTITY: { // 0x4C347B
            // There was an incorrect (it was inverted) null check at `0x4C3496`
            // The opposite case (when `drvr == nullptr` was a no-op anyways because `CTaskComplexSmartFleeEntity` does nothing when `fleeEntity == nullptr`)
            return notsa::IsFixBugs()
                ? new CTaskComplexSmartFleeEntity{drvr, true, 100'000.f}
                : nullptr; 
        }
        case TASK_COMPLEX_KILL_CRIMINAL: {
            return new CTaskComplexKillCriminal{drvr};
        }
        }
        return nullptr;
    }();
}

// 0x4C2840
void CEventHandler::ComputeGunAimedAtResponse(CEventGunAimedAt* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (m_ped->IsPlayer()) {
            return nullptr;
        }

        const auto IsFleeTask = [](CTask* t) {
            return notsa::contains({TASK_COMPLEX_SMART_FLEE_ENTITY, TASK_COMPLEX_SMART_FLEE_POINT}, t->GetTaskType());
        };
        if (IsFleeTask(tactive) || IsFleeTask(tsimplest)) {
            return new CTaskComplexSmartFleeEntity{e->m_ped, false, fSafeDistance}; // 0x4C28F5
        }

        if (m_ped->IsCreatedBy(PED_GAME) && !m_ped->bInVehicle && !m_ped->GetActiveWeapon().IsTypeMelee()) {
            if (e->m_ped && e->m_ped->IsPlayer() && !m_ped->GetIntelligence()->IsFriendlyWith(*e->m_ped)) {
                e->m_taskId = TASK_COMPLEX_KILL_PED_ON_FOOT; // 0x4C296F
            }
        }

        switch (e->m_taskId) {
        case TASK_COMPLEX_USE_CLOSEST_FREE_SCRIPTED_ATTRACTOR: // 0x4C2A7A
            return new CTaskComplexUseClosestFreeScriptedAttractor{};
        case TASK_COMPLEX_USE_CLOSEST_FREE_SCRIPTED_ATTRACTOR_RUN:
            return new CTaskComplexUseClosestFreeScriptedAttractorRun{};
        case TASK_COMPLEX_USE_CLOSEST_FREE_SCRIPTED_ATTRACTOR_SPRINT:
            return new CTaskComplexUseClosestFreeScriptedAttractorSprint{};
        case TASK_SIMPLE_COWER:
            return new CTaskSimpleCower{};
        case TASK_SIMPLE_HANDS_UP:
            return new CTaskSimpleHandsUp{5'000};
        case TASK_SIMPLE_DUCK: {
            if (const auto t = m_ped->GetIntelligence()->GetTaskDuck()) {
                return t;
            }
            return new CTaskSimpleDuck{DUCK_STANDALONE, 5'000};
        }
        case TASK_SIMPLE_DUCK_FOREVER:
            return new CTaskSimpleDuck{DUCK_STANDALONE, 0x967Fu}; // are they trying to tell us something? "Fu" :D
        case TASK_COMPLEX_REACT_TO_GUN_AIMED_AT: // 0x4C2B2C
            return new CTaskComplexReactToGunAimedAt{e->m_ped}; 
        case TASK_COMPLEX_KILL_PED_ON_FOOT_STEALTH: // 0x4C2E30
            return new CTaskComplexKillPedOnFootStealth{e->m_ped};
        case TASK_COMPLEX_KILL_CRIMINAL:
            return new CTaskComplexKillCriminal{e->m_ped};
        case TASK_COMPLEX_KILL_PED_ON_FOOT: { // 0x4C2E3D
            if (IsKillTaskAppropriate(m_ped, e->m_ped, *e)) {
                return new CTaskComplexKillPedOnFoot{e->m_ped};
            }
            return new CTaskComplexFleeEntity{e->m_ped, false};
        }
        case TASK_COMPLEX_FLEE_ANY_MEANS: // 0x4C2B36
            return new CTaskComplexFleeAnyMeans{e->m_ped, true, fSafeDistance};
        case TASK_COMPLEX_CAR_DRIVE_MISSION_FLEE_SCENE: {// 0x4C2BF
            if (const auto v = m_ped->m_pVehicle) {
                if (v->IsDriver(m_ped)) {
                    return new CTaskComplexCarDriveMissionFleeScene{v}; // 0x4C2C39
                }
            }
            if (!m_ped->bWantedByPolice || !e->m_ped->IsCop()) {
                return new CTaskComplexFleeEntity{e->m_ped, false};
            }
            return new CTaskComplexFleeAnyMeans{e->m_ped, true, fSafeDistance};
        }
        case TASK_COMPLEX_FLEE_ENTITY: // 0x4C2BEE
            return new CTaskComplexFleeEntity{e->m_ped, false};
        case TASK_COMPLEX_SMART_FLEE_ENTITY: { // 0x4C2B5C
            if (!m_ped->bWantedByPolice || !e->m_ped->IsCop()) {
                return new CTaskComplexFleeEntity{e->m_ped, false};
            }
            return new CTaskComplexFleeAnyMeans{e->m_ped, true, fSafeDistance};
        }
        }
        NOTSA_UNREACHABLE();
    }();
}

// 0x4BAC10
void CEventHandler::ComputeHighAngerAtPlayerResponse(CEventHighAngerAtPlayer* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        switch (e->m_taskId) {
        case TASK_COMPLEX_KILL_PED_ON_FOOT:
            return new CTaskComplexKillPedOnFoot{FindPlayerPed()};
        case TASK_COMPLEX_SMART_FLEE_ENTITY:
            return new CTaskComplexSmartFleeEntity{FindPlayerPed(), false, 60.f};
        case TASK_NONE:
            return nullptr;
        case TASK_SIMPLE_DUCK_FOREVER:
            return new CTaskSimpleDuck{DUCK_STANDALONE, 0xE0FFu, -1};
        default:
            NOTSA_UNREACHABLE();
        }
    }();
}

// 0x4BAF80
void CEventHandler::ComputeInWaterResponse(CEventInWater* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = new CTaskComplexInWater{};
}

// 0x4BAFE0
void CEventHandler::ComputeInteriorUseInfoResponse(CEventInteriorUseInfo* e, CTaskInteriorUseInfo* tUseInfo, CTask* tsimplest) {
    m_eventResponseTask = tUseInfo->Clone();
}

// 0x4B9FF0
void CEventHandler::ComputeKnockOffBikeResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B9FF0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BAAD0
void CEventHandler::ComputeLowAngerAtPlayerResponse(CEventLowAngerAtPlayer* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* { // Same code as `ComputeHighAngerAtPlayerResponse`
        switch (e->m_taskId) {
        case TASK_COMPLEX_KILL_PED_ON_FOOT:
            return new CTaskComplexKillPedOnFoot{FindPlayerPed()};
        case TASK_COMPLEX_SMART_FLEE_ENTITY:
            return new CTaskComplexSmartFleeEntity{FindPlayerPed(), false, 60.f};
        case TASK_NONE:
            return nullptr;
        case TASK_SIMPLE_DUCK_FOREVER:
            return new CTaskSimpleDuck{DUCK_STANDALONE, 0xE0FFu, -1};
        default:
            NOTSA_UNREACHABLE();
        }
    }();
}

// 0x4BA990
void CEventHandler::ComputeLowHealthResponse(CEventHealthLow* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        switch (e->m_taskId) {
        case TASK_COMPLEX_DIVE_FROM_ATTACHED_ENTITY_AND_GET_UP:
            return new CTaskComplexDiveFromAttachedEntityAndGetUp{};
        case TASK_NONE:
            return nullptr;
        default:
            NOTSA_UNREACHABLE();
        }
    }();
}

// 0x4BBB90
void CEventHandler::ComputeObjectCollisionPassiveResponse(CEventPotentialWalkIntoObject* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (!e->m_object || m_ped->bInVehicle || e->m_moveState == PEDMOVE_STILL) {
            return nullptr;
        }
        if (!tsimplest || !CTask::IsGoToTask(tsimplest)) {
            return nullptr;
        }
        const auto tGoTo = static_cast<CTaskSimpleGoTo*>(tsimplest);
        return new CTaskComplexWalkRoundObject{
            e->m_moveState,
            tGoTo->m_vecTargetPoint,
            e->m_object
        };
    }();
}

/*
m_eventResponseTask = [&]() -> CTask* {

}();
*/
// 0x4B92B0
void CEventHandler::ComputeObjectCollisionResponse(CEventObjectCollision* e, CTask* tactive, CTask* tsimplest) { // Same code as `ComputeObjectCollisionPassiveResponse`
    m_eventResponseTask = [&]() -> CTask* {
        if (!e->m_object || m_ped->bInVehicle || e->m_moveState == PEDMOVE_STILL) {
            return nullptr;
        }
        if (!tsimplest || !CTask::IsGoToTask(tsimplest)) {
            return nullptr;
        }
        const auto tGoTo = static_cast<CTaskSimpleGoTo*>(tsimplest);
        return new CTaskComplexWalkRoundObject{
            e->m_moveState,
            tGoTo->m_vecTargetPoint,
            e->m_object
        };
    }();
}

// 0x4BC150
void CEventHandler::ComputeOnEscalatorResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = new CTaskSimpleStandStill{0, true};
}

// 0x4BAD50
void CEventHandler::ComputeOnFireResponse(CEventOnFire* e, CTask* tactive, CTask* tsimplest) {
    m_eventResponseTask = [&]() -> CTask* {
        if (m_ped->IsPlayer()) {
            if (m_ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM)) {
                return nullptr;
            }
            return new CTaskSimplePlayerOnFire{};
        } else {
            return new CTaskComplexOnFire{};
        }
    }();
}

// 0x4BB0C0
void CEventHandler::ComputePassObjectResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BB0C0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
    /*
    auto _event = static_cast<CEventPassObject*>(event);
    // m_eventResponseTask = new CTaskComplexPassObject(_event->m_giver, _event->m_dontPassObject);
    */
}

// 0x4BDB80
void CEventHandler::ComputePedCollisionWithPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BDB80, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BE7D0
void CEventHandler::ComputePedCollisionWithPlayerResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BE7D0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4C1590
void CEventHandler::ComputePedEnteredVehicleResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4C1590, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4B9DD0
void CEventHandler::ComputePedFriendResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B9DD0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4B9D40
void CEventHandler::ComputePedSoundQuietResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B9D40, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4B9C90
void CEventHandler::ComputePedThreatBadlyLitResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B9C90, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4C19A0
void CEventHandler::ComputePedThreatResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4C19A0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4C1910
void CEventHandler::ComputePedToChaseResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4C1910, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
    /*
    m_eventResponseTask = new CTaskComplexSeekEntity(static_cast<CTask*>(task1)->entity, 30000, 1000, 1.0f, 2.0f, 2.0f, 1, 1);
    */
}

// 0x4B9B50
void CEventHandler::ComputePedToFleeResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B9B50, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);

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
void CEventHandler::ComputePlayerCollisionWithPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B8CE0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BB280
void CEventHandler::ComputePlayerWantedLevelResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BB280, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
    //m_eventResponseTask = new CTaskComplexPolicePursuit();
}

// 0x4C2610
void CEventHandler::ComputePotentialPedCollideResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4C2610, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BBCD0
void CEventHandler::ComputePotentialWalkIntoFireResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BBCD0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BAA30
void CEventHandler::ComputeReallyLowHealthResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BAA30, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
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
void CEventHandler::ComputeReviveResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B97B0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BA7C0
void CEventHandler::ComputeScriptCommandResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BA7C0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BC050
void CEventHandler::ComputeSeenCopResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BC050, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4C35F0
void CEventHandler::ComputeSeenPanickedPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4C35F0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4B99F0
void CEventHandler::ComputeSexyPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B99F0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
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
void CEventHandler::ComputeSexyVehicleResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    auto evnt = reinterpret_cast<CEventSexyVehicle*>(e);
    if (evnt->m_vehicle) {
        g_InterestingEvents.Add(CInterestingEvents::EType::INTERESTING_EVENT_8, evnt->m_vehicle);
        m_eventResponseTask = new CTaskSimpleStandStill(5000, false, false, 8.0f);
        g_ikChainMan.LookAt("CompSexyVhclResp", m_ped, evnt->m_vehicle, 5000, BONE_UNKNOWN, nullptr, true, 0.25f, 500, 3, false);
    }
}

// task1 TASK_COMPLEX_CAR_DRIVE_WANDER 711 911 912 911 1204
// task2 TASK_SIMPLE_CAR_DRIVE         709 400 900 900 900
// 0x4BC710
void CEventHandler::ComputeShotFiredResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BC710, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BBE30
void CEventHandler::ComputeShotFiredWhizzedByResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BBE30, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BB050
void CEventHandler::ComputeSignalAtPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BB050, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);

    //m_eventResponseTask = new CTaskComplexSignalAtPed(*(task1 + 12), *(task1 + 16), *(task1 + 20));
}

// 0x4BB800
void CEventHandler::ComputeSpecialResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BB800, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BD6A0
void CEventHandler::ComputeVehicleCollisionResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BD6A0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4C2FC0
void CEventHandler::ComputeVehicleDamageResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4C2FC0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BA8B0
void CEventHandler::ComputeVehicleDiedResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BA8B0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x?
void CEventHandler::ComputeVehicleHitAndRunResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    // NOP
}

// 0x4BB2E0
void CEventHandler::ComputeVehicleOnFireResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BB2E0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4C0BD0
void CEventHandler::ComputeVehiclePotentialCollisionResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4C0BD0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4B96D0
void CEventHandler::ComputeVehiclePotentialPassiveCollisionResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B96D0, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4B9F80
void CEventHandler::ComputeVehicleToStealResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4B9F80, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4BAE30
void CEventHandler::ComputeWaterCannonResponse(CEvent* e, CTask* tactive, CTask* tsimplest) {
    plugin::CallMethod<0x4BAE30, CEventHandler*, CEvent*, CTask*, CTask*>(this, e, tactive, tsimplest);
}

// 0x4C3870
void CEventHandler::ComputeEventResponseTask(CEvent* e, CTask* task) {
    return plugin::CallMethod<0x4C3870, CEventHandler*, CEvent*, CTask*>(this, e, task);

    m_physicalResponseTask = nullptr;
    m_eventResponseTask    = nullptr;
    m_attackTask           = nullptr;
    m_sayTask              = nullptr;
    m_partialAnimTask      = nullptr;

    const auto tactive = m_ped->GetTaskManager().GetActiveTask();
    const auto tsimplest = tactive ? m_ped->GetTaskManager().GetSimplestActiveTask() : nullptr;
    
    //DEV_LOG("event: {} tactive: {} tsimplest: {}", (int32)event->GetEventType(), (int32)tactive->GetTaskType(), (int32)tsimplest->GetTaskType()); // NOTSA

    switch (e->GetEventType()) {
    case EVENT_VEHICLE_COLLISION:
        ComputeVehicleCollisionResponse(e, tactive, tsimplest);
        break;
    case EVENT_PED_COLLISION_WITH_PED:
        ComputePedCollisionWithPedResponse(e, tactive, tsimplest);
        break;
    case EVENT_PED_COLLISION_WITH_PLAYER:
        ComputePedCollisionWithPlayerResponse(e, tactive, tsimplest);
        break;
    case EVENT_PLAYER_COLLISION_WITH_PED:
        ComputePlayerCollisionWithPedResponse(e, tactive, tsimplest);
        break;
    case EVENT_OBJECT_COLLISION:
        ComputeObjectCollisionResponse(static_cast<CEventObjectCollision*>(e), tactive, tsimplest);
        break;
    case EVENT_BUILDING_COLLISION:
        ComputeBuildingCollisionResponse(static_cast<CEventBuildingCollision*>(e), tactive, tsimplest);
        break;
    case EVENT_DRAGGED_OUT_CAR:
        ComputeDraggedOutCarResponse(static_cast<CEventDraggedOutCar*>(e), tactive, tsimplest);
        break;
    case EVENT_KNOCK_OFF_BIKE:
        ComputeKnockOffBikeResponse(e, tactive, tsimplest);
        break;
    case EVENT_DAMAGE:
        ComputeDamageResponse(static_cast<CEventDamage*>(e), tactive, tsimplest, task);
        break;
    case EVENT_DEATH:
        ComputeDeathResponse(static_cast<CEventDeath*>(e), tactive, tsimplest);
        break;
    case EVENT_DEAD_PED:
        ComputeDeadPedResponse(static_cast<CEventDeadPed*>(e), tactive, tsimplest);
        break;
    case EVENT_POTENTIAL_GET_RUN_OVER:
        ComputeVehiclePotentialCollisionResponse(e, tactive, tsimplest);
        break;
    case EVENT_POTENTIAL_WALK_INTO_PED:
        ComputePotentialPedCollideResponse(e, tactive, tsimplest);
        break;
    case EVENT_SHOT_FIRED:
        ComputeShotFiredResponse(e, tactive, tsimplest);
        break;
    case EVENT_COP_CAR_BEING_STOLEN:
        ComputeCopCarBeingStolenResponse(static_cast<CEventCopCarBeingStolen*>(e), tactive, tsimplest);
        break;
    case EVENT_PED_ENTERED_MY_VEHICLE:
        ComputePedEnteredVehicleResponse(e, tactive, tsimplest);
        break;
    case EVENT_REVIVE:
        ComputeReviveResponse(e, tactive, tsimplest);
        break;
    case EVENT_CHAT_PARTNER:
        ComputeChatPartnerResponse(static_cast<CEventChatPartner*>(e), tactive, tsimplest);
        break;
    case EVENT_SEXY_PED:
        ComputeSexyPedResponse(e, tactive, tsimplest);
        break;
    case EVENT_SEXY_VEHICLE:
        ComputeSexyVehicleResponse(e, tactive, tsimplest);
        break;
    case EVENT_PED_TO_CHASE:
        ComputePedToChaseResponse(e, tactive, tsimplest);
        break;
    case EVENT_PED_TO_FLEE:
        ComputePedToFleeResponse(e, tactive, tsimplest);
        break;
    case EVENT_ATTRACTOR:
    case EVENT_SCRIPTED_ATTRACTOR:
        ComputeAttractorResponse(static_cast<CEventAttractor*>(e), tactive, tsimplest);
        break;
    case EVENT_VEHICLE_TO_STEAL:
        ComputeVehicleToStealResponse(e, tactive, tsimplest);
        break;
    case EVENT_GUN_AIMED_AT:
        ComputeGunAimedAtResponse(static_cast<CEventGunAimedAt*>(e), tactive, tsimplest);
        break;
    case EVENT_SCRIPT_COMMAND:
        ComputeScriptCommandResponse(e, tactive, tsimplest);
        break;
    case EVENT_IN_AIR:
        if (!m_ped->bIsStanding) {
            m_eventResponseTask = new CTaskComplexInAirAndLand(false, false);
        }
        break;
    case EVENT_VEHICLE_DIED:
        ComputeVehicleDiedResponse(e, tactive, tsimplest);
        break;
    case EVENT_ACQUAINTANCE_PED_HATE:
    case EVENT_ACQUAINTANCE_PED_DISLIKE:
        ComputePedThreatResponse(e, tactive, tsimplest);
        break;
    case EVENT_ACQUAINTANCE_PED_LIKE:
    case EVENT_ACQUAINTANCE_PED_RESPECT:
        ComputePedFriendResponse(e, tactive, tsimplest);
        break;
    case EVENT_VEHICLE_DAMAGE_WEAPON:
    case EVENT_VEHICLE_DAMAGE_COLLISION:
        ComputeVehicleDamageResponse(e, tactive, tsimplest);
        break;
    case EVENT_SPECIAL:
        ComputeSpecialResponse(e, tactive, tsimplest);
        break;
    case EVENT_GOT_KNOCKED_OVER_BY_CAR:
        ComputeGotKnockedOverByCarResponse(static_cast<CEventGotKnockedOverByCar*>(e), tactive, tsimplest);
        break;
    case EVENT_POTENTIAL_WALK_INTO_OBJECT:
        ComputeObjectCollisionPassiveResponse(static_cast<CEventPotentialWalkIntoObject*>(e), tactive, tsimplest);
        break;
    case EVENT_CAR_UPSIDE_DOWN:
        ComputeCarUpsideDownResponse(static_cast<CEventCarUpsideDown*>(e), tactive, tsimplest);
        break;
    case EVENT_POTENTIAL_WALK_INTO_FIRE:
        ComputePotentialWalkIntoFireResponse(e, tactive, tsimplest);
        break;
    case EVENT_SHOT_FIRED_WHIZZED_BY:
        ComputeShotFiredWhizzedByResponse(e, tactive, tsimplest);
        break;
    case EVENT_LOW_ANGER_AT_PLAYER:
        ComputeLowAngerAtPlayerResponse(static_cast<CEventLowAngerAtPlayer*>(e), tactive, tsimplest);
        break;
    case EVENT_HIGH_ANGER_AT_PLAYER:
        ComputeHighAngerAtPlayerResponse(static_cast<CEventHighAngerAtPlayer*>(e), tactive, tsimplest);
        break;
    case EVENT_HEALTH_REALLY_LOW:
        ComputeReallyLowHealthResponse(e, tactive, tsimplest);
        break;
    case EVENT_HEALTH_LOW:
        ComputeLowHealthResponse(static_cast<CEventHealthLow*>(e), tactive, tsimplest);
        break;
    case EVENT_POTENTIAL_WALK_INTO_VEHICLE:
        ComputeVehiclePotentialPassiveCollisionResponse(e, tactive, tsimplest);
        break;
    case EVENT_ON_FIRE:
        ComputeOnFireResponse(static_cast<CEventOnFire*>(e), tactive, tsimplest);
        break;
    case EVENT_FIRE_NEARBY:
        ComputeFireNearbyResponse(static_cast<CEventFireNearby*>(e), tactive, tsimplest);
        break;
    case EVENT_SOUND_QUIET:
        ComputePedSoundQuietResponse(e, tactive, tsimplest);
        break;
    case EVENT_ACQUAINTANCE_PED_HATE_BADLY_LIT:
        ComputePedThreatBadlyLitResponse(e, tactive, tsimplest);
        break;
    case EVENT_WATER_CANNON:
        ComputeWaterCannonResponse(e, tactive, tsimplest);
        break;
    case EVENT_SEEN_PANICKED_PED:
        ComputeSeenPanickedPedResponse(e, tactive, tsimplest);
        break;
    case EVENT_IN_WATER:
        ComputeInWaterResponse(static_cast<CEventInWater*>(e), tactive, tsimplest);
        break;
    case EVENT_AREA_CODES:
        ComputeAreaCodesResponse(static_cast<CEventAreaCodes*>(e), tactive, tsimplest);
        break;
    case EVENT_PLAYER_WANTED_LEVEL:
        ComputePlayerWantedLevelResponse(e, tactive, tsimplest);
        break;
    case EVENT_CREATE_PARTNER_TASK:
        ComputeCreatePartnerTaskResponse(static_cast<CEventCreatePartnerTask*>(e), tactive, tsimplest);
        break;
    case EVENT_SEEN_COP:
        ComputeSeenCopResponse(e, tactive, tsimplest);
        break;
    case EVENT_ON_ESCALATOR:
        ComputeOnEscalatorResponse(e, tactive, tsimplest);
        break;
    case EVENT_DANGER:
        ComputeDangerResponse(static_cast<CEventDanger*>(e), tactive, tsimplest);
        break;
    case EVENT_VEHICLE_ON_FIRE:
        ComputeVehicleOnFireResponse(e, tactive, tsimplest);
        break;
    case EVENT_INTERIOR_USE_INFO:
        ComputeInteriorUseInfoResponse(static_cast<CEventInteriorUseInfo*>(e), CTask::DynCast<CTaskInteriorUseInfo>(tactive), tsimplest);
        break;
    case EVENT_SIGNAL_AT_PED:
        ComputeSignalAtPedResponse(e, tactive, tsimplest);
        break;
    case EVENT_PASS_OBJECT:
        ComputePassObjectResponse(e, tactive, tsimplest);
        break;
    case EVENT_STUCK_IN_AIR:
        m_eventResponseTask = new CTaskComplexStuckInAir();
        break;
    case EVENT_DONT_JOIN_GROUP:
        ComputeDontJoinGroupResponse(static_cast<CEventDontJoinPlayerGroup*>(e), tactive, tsimplest);
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
    return task;
}
