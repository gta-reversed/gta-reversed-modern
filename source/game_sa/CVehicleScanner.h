#pragma once
#include "CEntityScanner.h"

class CPed;

class CVehicleScanner : public CEntityScanner
{
public:
    void ScanForVehiclesInRange(CPed* pPed);
};