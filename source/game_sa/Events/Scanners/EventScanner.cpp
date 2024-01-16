#include "StdInc.h"

#include "TaskComplexKillPedOnFoot.h"

#include "EventOnFire.h"
#include "EventEscalator.h"
#include "EventPedEnteredMyVehicle.h"

#include "EventScanner.h"
#include "PedPotentialCollisionScanner.h"

void CEventScanner::InjectHooks() {
    RH_ScopedClass(CEventScanner);
    RH_ScopedCategory("Events/Scanners");

    RH_ScopedInstall(Constructor, 0x605300);

    RH_ScopedInstall(ScanForEventsNow, 0x6053D0);
    RH_ScopedInstall(ScanForEvents, 0x607E30);
}

// 0x605300
CEventScanner::CEventScanner() :
    m_NextScanTime{CTimer::GetTimeInMS() + CGeneral::GetRandomNumberInRange<uint32>(3000)}   
{
    m_AttractorScanner.Clear();
}

void CEventScanner::Clear() {
    m_AttractorScanner.Clear();
}

// 0x607E30
void CEventScanner::ScanForEvents(CPed& ped) {
    if (CTimer::GetTimeInMS() <= m_NextScanTime) {
        return;
    }
    const auto intel = ped.GetIntelligence();
    const auto eg    = &intel->GetEventGroup();

    m_VehCollisionScanner.ScanForVehiclePotentialCollisionEvents(ped, intel->GetVehicleScanner().GetEntitiesPtr(), CEntityScanner::MAX_ENTITIES);
    CPedPotentialCollisionScanner::ScanForPedPotentialCollisionEvents(ped, intel->GetPedScanner().GetClosestPedInRange());
    m_ObjCollisionScanner.ScanForObjectPotentialCollisionEvents(ped);
    m_AcquaintanceScanner.ScanForPedAcquaintanceEvents(ped, intel->GetPedScanner().GetEntitiesPtr(), CEntityScanner::MAX_ENTITIES);
    m_AttractorScanner.ScanForAttractorsInRange(ped);
    m_FireScanner.ScanForNearbyFires(ped);
    intel->m_mentalState.Process();

    // 0x607ECE
    if (!ped.bIsStanding && (ped.bIsInTheAir || CPedGeometryAnalyser::IsInAir(ped))) {
        eg->Add(CEventInAir{});
    } else if (ped.bIsInTheAir) {
        if (intel->GetEventHandler().GetCurrentEventType() != EVENT_IN_AIR) {
            ped.bIsInTheAir = false;
        }
    }

    // 0x607F5A
    if (ped.m_pFire) {
        CEventOnFire onFireEvent{};

        const auto currTask = intel->GetTaskManager().GetSimplestActiveTask();
        if (ped.IsPlayer() || !currTask || currTask->MakeAbortable(&ped, ABORT_PRIORITY_URGENT, &onFireEvent)) {
            eg->Add(&onFireEvent);
        } else {
            CWeapon::GenerateDamageEvent(&ped, ped.m_pFire->m_pEntityCreator, WEAPON_FLAMETHROWER, 5, PED_PIECE_TORSO, 0);
        }
    }

    m_SexyPedScanner.ScanForSexyPedEvents(ped, reinterpret_cast<CPed**>(intel->GetPedScanner().GetEntitiesPtr()), CEntityScanner::MAX_ENTITIES);

    // 0x608023
    if (const auto tKillPedOnFoot = intel->GetTaskManager().Find<CTaskComplexKillPedOnFoot>(false)) {
        if (const auto killTarget = tKillPedOnFoot->GetTarget()) {
            if (killTarget->m_pContactEntity && ped.m_pContactEntity) {
                if (killTarget->m_pContactEntity->m_nAreaCode != ped.m_pContactEntity->m_nAreaCode) {
                    eg->Add(CEventAreaCodes{killTarget});
                }
            }
        }
    }

    // 0x6080BA
    if (const auto contacte = ped.m_pContactEntity) {
        if (contacte->m_nModelIndex == ModelIndices::MI_ESCALATORSTEP || contacte->m_nModelIndex == ModelIndices::MI_ESCALATORSTEP8) {
            eg->Add(CEventEscalator{});
        }
    }

    // 0x608123
    if (ped.IsInVehicle()) {
        if (ped.m_pVehicle->IsBoat() && !ped.IsPlayer()) {
            const auto player = FindPlayerPed();
            if (player->m_pContactEntity == ped.m_pVehicle) {
                eg->Add(CEventPedEnteredMyVehicle{ player, ped.m_pVehicle, TARGET_DOOR_DRIVER });
            }
        }
    }

    // 0x6081B5
    if (ped.m_fHealth <= 0.f && ped.IsAlive()) {
        if (CTimer::GetTimeInMS() > m_sDeadPedWalkingTimer) {
            CEventDamage dmgEvent{
                nullptr,
                0,
                WEAPON_UNIDENTIFIED,
                PED_PIECE_TORSO,
                0,
                false,
                false
            };
            if (!eg->HasEventOfType(&dmgEvent)) {
                CWeapon::GenerateDamageEvent(&ped, nullptr, WEAPON_FALL, 10, PED_PIECE_TORSO, 0);
                m_sDeadPedWalkingTimer = CTimer::GetTimeInMS() + 2000;
            }
        }
    }
}

// 0x6053D0
void CEventScanner::ScanForEventsNow(const CPed& ped, bool bDontScan) {
    if (bDontScan) {
        return;
    }

    m_VehCollisionScanner.ResetTimer();
    m_VehCollisionScanner.ScanForVehiclePotentialCollisionEvents(ped, ped.GetIntelligence()->GetVehicleEntities(), CEntityScanner::MAX_ENTITIES);
}
