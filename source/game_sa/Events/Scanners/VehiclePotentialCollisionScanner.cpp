#include "StdInc.h"

#include "VehiclePotentialCollisionScanner.h"
#include "TaskSimpleGoTo.h"

void CVehiclePotentialCollisionScanner::InjectHooks() {
    RH_ScopedClass(CVehiclePotentialCollisionScanner);
    RH_ScopedCategory("Events/Scanners");

    RH_ScopedInstall(ScanForVehiclePotentialCollisionEvents, 0x603720);
}

// 0x603720
void CVehiclePotentialCollisionScanner::ScanForVehiclePotentialCollisionEvents(const CPed& ped, CEntity** entities, size_t count) {
    UNUSED(entities);
    UNUSED(count);

    constexpr auto CHECK_INTERVAL            = 500;  // How often to check for collision [in ms]
    constexpr auto VEH_BB_UP_DOWN_THRESHHOLD = 0.5f; // How much above/below the ped can be (Relative to the height of the veh's BB)

    if (!m_timer.IsStarted()) {
        m_timer.Start(CHECK_INTERVAL);
    }
    if (!m_timer.IsOutOfTime()) {
        return;
    }
    m_timer.Start(CHECK_INTERVAL);

    // Find ped's goto task
    const auto pedGoToTask = static_cast<CTaskSimpleGoTo*>(ped.GetTaskManager().GetSimplestActiveTask()); // Can't use `CTask::Cast`, different goto tasks have different id's
    if (!pedGoToTask || !CTask::IsGoToTask(pedGoToTask)) {
        return;
    }

    // Find a vehicle close-by
    const auto closestVeh = ped.GetIntelligence()->GetVehicleScanner().GetClosestVehicleInRange();
    if (!closestVeh) {
        return;
    }

    // Quickly check if the ped is within the BB on the Z axis
    {
        // Originally the BB positions were transformed into world-space,
        // but for simplicity I'm transforming the ped's position into object space instead.

        const auto& vehBB  = closestVeh->GetBoundingBox();
        const auto& vehMat = closestVeh->GetMatrix();
    
        const auto CheckPedInBB = [
            &,
            pedPosOS = vehMat.InverseTransformPoint(ped.GetPosition())
        ](CVector dir, CVector bbPt) {
            return dir.Dot(pedPosOS - bbPt) <= VEH_BB_UP_DOWN_THRESHHOLD;
        };
        if (!CheckPedInBB(vehMat.GetUp(), vehBB.m_vecMax) || !CheckPedInBB(-vehMat.GetUp(), vehBB.m_vecMin)) {
            return;
        }
    }

    // Check if ped's close enough to the vehicle (NOTE: Not sure why this isn't checked a lot earlier)
    if (!ped.bHasJustLeftCar) {
        if (!ped.IsEntityInRange(closestVeh, closestVeh->IsTrain() ? 10.f : 5.f)) {
            return;
        }   
    }

    // Now, a more accuracte check
    float intersectionMag{};
    if (CPedGeometryAnalyser::GetIsLineOfSightClear(
        ped,
        pedGoToTask->GetTargetPt(),
        *closestVeh,
        intersectionMag
    )) {
        if (intersectionMag <= 0.5f) {
            return;
        }
    }

    // Yeah def gonna walk into that shit, let the world know the ped is dumb af
    ped.GetIntelligence()->GetEventGroup().Add(CEventPotentialWalkIntoVehicle{ closestVeh, pedGoToTask->GetMoveState() });
}

// @addr unk
void CVehiclePotentialCollisionScanner::ResetTimer() {
    m_timer.SetAsOutOfTime();
}
