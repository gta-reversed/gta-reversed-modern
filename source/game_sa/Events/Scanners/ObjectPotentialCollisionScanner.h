#pragma once

#include "TaskTimer.h"

class CObjectPotentialCollisionScanner {
public:
    static void InjectHooks();

    void ScanForObjectPotentialCollisionEvents(const CPed& ped);

private:
    CTaskTimer m_timer;
};
VALIDATE_SIZE(CObjectPotentialCollisionScanner, 0xC);
