#pragma once

#include "EntityScanner.h"

class CPed;

class CVehicleScanner : public CEntityScanner {
public:
    void ScanForVehiclesInRange(CPed* ped);
};
