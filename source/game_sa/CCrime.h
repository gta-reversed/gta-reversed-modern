#pragma once

#include "eCrimeType.h"

class CPed;

class CCrime {
public:
    static void ReportCrime(eCrimeType crimeType, CPed* ped1, CPed* ped2);
};
