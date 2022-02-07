#pragma once

class CInterestingEvents {
public:
    enum EType {
        // 1  CTaskComplexChat::CreateFirstSubTask
        // 2  CTaskComplexSunbathe::CreateNextSubTask
        // 3  CTaskComplexUseAttractor::CreateFirstSubTask CTaskComplexUseClosestFreeScriptedAttractor::CreateFirstSubTask
        // 7  CInterestingEvents::ScanForNearbyEntities
        // 8  CEventHandler::ComputeSexyVehicleResponse
        // 9  CSexyPedScanner::ScanForSexyPedEvents
        // 11 CTaskSimpleGiveCPR::ReviveDeadPed
        // 12 CTaskComplexMedicTreatInjuredPed::CreateNextSubTask
        // 13 CTaskComplexFleeEntity::CreateFirstSubTask CTaskComplexSmartFleeEntity::CreateFirstSubTask
        // 14 CInterestingEvents::ScanForNearbyEntities
        // 15 CEventHandler::ComputeDamageResponse
        // 16 CEventHandler::ComputeKnockOffBikeResponse
        // 17 CAutomobile::VehicleDamage
        VEHICLE_DAMAGE = 17,
        // 18 CTaskComplexRoadRage::CreateFirstSubTask
        // 19 CTaskComplexKillPedOnFootMelee::CreateFirstSubTask
        // 20 CEventHandler::ComputePedEnteredVehicleResponse
        // 21 CHeli::ProcessControl
        // 22 CWeapon::FireSniper CWeapon::FireInstantHitFromCar2 CWeapon::FireInstantHit CWeapon::FireProjectile
        // 23 CTaskAllocatorKillThreatsDriveby::AllocateTasks sub_69D170 ComputeKillThreatsBasicResponse
        // 25 CTaskComplexKillCriminal::CreateFirstSubTask
        // 26 CHeli::ProcessControl
        EVENT_ATTRACTOR = 27, // 27 CExplosion::AddExplosion
        // 28 CEventHandler::ComputeDamageResponse
    };

public:
    static void InjectHooks();

    CInterestingEvents();
    CInterestingEvents* Constructor();

    ~CInterestingEvents();
    CInterestingEvents* Destructor();

    void Add(CInterestingEvents::EType type, CEntity* entity);
    void ScanForNearbyEntities();
    void GetInterestingEvent();
    void InvalidateEvent(const void* interestingEvent);
    void InvalidateNonVisibleEvents();
};

extern CInterestingEvents& g_InterestingEvents;
