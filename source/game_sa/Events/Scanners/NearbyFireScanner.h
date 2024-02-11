#pragma once

#include "Ped.h"
#include "TaskTimer.h"

class CNearbyFireScanner {
public:
    static void InjectHooks();

    void ScanForNearbyFires(const CPed& a2);

private:
    CTaskTimer m_timer{};
};
VALIDATE_SIZE(CNearbyFireScanner, 0xC);
