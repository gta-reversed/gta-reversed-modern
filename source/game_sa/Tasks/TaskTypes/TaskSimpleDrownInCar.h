#pragma once

#include "TaskSimple.h"

class CTaskSimpleDrownInCar : public CTaskSimple {
public:
    CTaskSimpleDrownInCar() = default;  // 0x62FF20
    ~CTaskSimpleDrownInCar() override = default; // 0x62FF60, 0x6378F0

    eTaskType GetTaskType() override { return TASK_SIMPLE_DROWN_IN_CAR; }; // 0x62FF40
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return false; } // 0x62FF50
    CTask* Clone() override { return new CTaskSimpleDrownInCar(); } // 0x636010
    bool ProcessPed(CPed* ped) override;
};
