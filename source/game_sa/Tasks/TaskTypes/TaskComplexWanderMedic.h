#pragma once

#include "TaskComplexWander.h"

class CTaskComplexWanderMedic : public CTaskComplexWander {
public:
    static constexpr auto Type = TASK_COMPLEX_WANDER_MEDIC;

    CTaskComplexWanderMedic* Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly);
    CTaskComplexWanderMedic(int32 MoveState, uint8 Dir, bool bWanderSensibly);
    int32 GetWanderType() override { return TASK_COMPLEX_WANDER_MEDIC; }
    void ScanForStuff(CPed* ped) override {}
    CTask* Clone() override;
};
