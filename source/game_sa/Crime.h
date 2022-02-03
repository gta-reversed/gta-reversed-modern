#pragma once

#include "eCrimeType.h"

class CPed;

class CCrime {
public:
    static void ReportCrime(eCrimeType crimeType, CEntity* entity, CPed* ped2);
};
