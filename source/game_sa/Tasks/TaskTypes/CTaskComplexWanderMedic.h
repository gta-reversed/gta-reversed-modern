#pragma once
#include "CTaskComplexWander.h"

class CTaskComplexWanderMedic : public CTaskComplexWander
{
public:
    CTaskComplexWanderMedic* Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly);
    CTaskComplexWanderMedic(int MoveState, unsigned char Dir, bool bWanderSensibly);
    int GetWanderType() override { return 2; }
    void ScanForStuff(CPed* ped) override {}
    CTask* Clone() override;
};
