#pragma once

#include "Ped.h"
#include "TaskTimer.h"

class CNearbyFireScanner {
public:
    static void InjectHooks();

    void ScanForNearbyFires(const CPed& ped);

private:
    CTaskTimer m_timer = {};
};
