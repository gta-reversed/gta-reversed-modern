#include "StdInc.h"
#include "TaskComplexEnterAnyCarAsDriver.h"
#include "TaskComplexEnterCarAsDriver.h"
#include "TaskSimpleNone.h"

void CTaskComplexEnterAnyCarAsDriver::InjectHooks() {
    RH_ScopedClass(CTaskComplexEnterAnyCarAsDriver);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedVirtualInstall(Clone, 0x63DE60);
    RH_ScopedVirtualInstall(GetTaskType, 0x63D0F0);
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x63D110);
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x643510);
    RH_ScopedVirtualInstall(ControlSubTask, 0x63D120);
}

// 0x643510
CTask* CTaskComplexEnterAnyCarAsDriver::CreateFirstSubTask(CPed* ped) {
    // Try entering the closest vehicle (If it's stealable)
    if (const auto closestVeh = ped->GetIntelligence()->GetVehicleScanner().GetClosestVehicleInRange()) {
        if (CCarEnterExit::IsVehicleStealable(closestVeh, ped)) {
            return new CTaskComplexEnterCarAsDriver{ closestVeh };
        }
    }

    // Otherwise just enter the closest vehicle (Not sure why they didn't use `GetClosestVehicleInRange`?)
    auto closestDistSq = FLT_MAX;
    CVehicle* closest{};
    for (auto vehicle : ped->GetIntelligence()->GetVehicleScanner().m_apEntities) {
        if (vehicle) {
            const auto distSq = (vehicle->GetPosition() - ped->GetPosition()).SquaredMagnitude();
            if (distSq < closestDistSq) {
                closestDistSq = distSq;
                closest = vehicle->AsVehicle();
            }
        }
    }

    if (closest) {
        return new CTaskComplexEnterCarAsDriver{ closest };
    }
    return new CTaskSimpleNone{};
}
