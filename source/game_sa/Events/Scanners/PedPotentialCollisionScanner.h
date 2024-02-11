#pragma once

#include "Ped.h"

class CPed;

class CPedPotentialCollisionScanner {
public:
    static void InjectHooks();

    static void __stdcall ScanForPedPotentialCollisionEvents(const CPed& ped, CPed* closestPed);
};
