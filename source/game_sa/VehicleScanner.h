#pragma once

#include "EntityScanner.h"

class CPed;
class CVehicle;

class CVehicleScanner : public CEntityScanner {
public:
    void ScanForVehiclesInRange(const CPed& ped);
    CVehicle* GetClosestVehicleInRange() const;
};
