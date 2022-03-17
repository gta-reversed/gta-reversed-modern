#include "StdInc.h"

#include "VehicleScanner.h"

// 0x5FFE60
void CVehicleScanner::ScanForVehiclesInRange(const CPed& ped) {
    if (!ped.IsAlive())
        return;

    if (ped.m_pVehicle && ped.bInVehicle) {
        if (ped.m_nCreatedBy == PED_MISSION)
            CEntityScanner::ScanForEntitiesInRange(REPEATSECTOR_VEHICLES, ped);

        if (m_pClosestEntityInRange)
            m_pClosestEntityInRange->CleanUpOldReference(reinterpret_cast<CEntity**>(m_pClosestEntityInRange));

        m_pClosestEntityInRange = ped.m_pVehicle;
        if (ped.m_pVehicle) {
            ped.m_pVehicle->RegisterReference(reinterpret_cast<CEntity**>(m_pClosestEntityInRange));
        }
    } else {
        CEntityScanner::ScanForEntitiesInRange(REPEATSECTOR_VEHICLES, ped);
    }
}

CVehicle* CVehicleScanner::GetClosestVehicleInRange() const {
    return static_cast<CVehicle*>(m_pClosestEntityInRange);
}
