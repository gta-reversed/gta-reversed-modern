#pragma once

#include "TaskTimer.h"

class CPed;
class CEntity;

/*!
 * @brief Emits `CEventPotentialWalkIntoVehicle` whenever there's a chance that an AI ped would walk into a close-by vehicle.
 */
class CVehiclePotentialCollisionScanner {
public:
    static void InjectHooks();

    void ScanForVehiclePotentialCollisionEvents(const CPed& ped, CEntity** entities, size_t count);
    void ResetTimer();

private:
    CTaskTimer m_timer;
};
VALIDATE_SIZE(CVehiclePotentialCollisionScanner, 0xC);
