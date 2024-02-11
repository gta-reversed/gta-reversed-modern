#pragma once

#include "Ped.h"
#include "TaskTimer.h"

class CEntity;

class CSexyPedScanner {
public:
    static void InjectHooks();

    void ScanForSexyPedEvents(const CPed& ped, CPed** nearbyPeds, size_t numNearbyPeds);

private:
    CTaskTimer m_timer;
};
