#pragma once

#include "TaskComplexWander.h"

class CTaskComplexWanderMedic : public CTaskComplexWander {
public:
    static constexpr auto Type = TASK_COMPLEX_WANDER_MEDIC;

    CTaskComplexWanderMedic(int32 MoveState, uint8 Dir, bool bWanderSensibly = true);
    CTask* Clone() override;
    eWanderType GetWanderType() override { return WANDER_TYPE_COP; } // 0x658810
    void ScanForStuff(CPed* ped) override {} // 0x658820
};
