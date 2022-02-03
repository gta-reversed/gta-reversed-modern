#pragma once

#include "TaskComplexWander.h"

class CTaskComplexWanderMedic : public CTaskComplexWander {
public:
    CTaskComplexWanderMedic* Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly);
    CTaskComplexWanderMedic(int32 MoveState, uint8 Dir, bool bWanderSensibly);
    int32 GetWanderType() override { return 2; }
    void ScanForStuff(CPed* ped) override {}
    CTask* Clone() override;
};
