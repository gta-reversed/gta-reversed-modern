#pragma once

#include "TaskTimer.h"

class CPed;
class CEntity;

class CVehiclePotentialCollisionScanner {
public:

    void ScanForVehiclePotentialCollisionEvents(const CPed& ped, CEntity** entities, size_t count);
    void ResetTimer();

private:
    CTaskTimer m_timer;
};
VALIDATE_SIZE(CVehiclePotentialCollisionScanner, 0xC);
