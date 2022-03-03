#pragma once

#include "EntityScanner.h"
#include "Vehicle.h"

class CPed;

class CVehicleScanner : public CEntityScanner {
public:
    void ScanForVehiclesInRange(CPed* ped);
    auto GetClosestVehicleInRange() const { return m_pClosestEntityInRange->AsVehicle(); }
};
