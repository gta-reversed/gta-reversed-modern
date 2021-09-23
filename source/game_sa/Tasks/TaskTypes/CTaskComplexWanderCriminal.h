#pragma once
#include "CTaskComplexWander.h"

class CTaskComplexWanderCriminal : public CTaskComplexWander
{
public:
    CTaskComplexWanderCriminal* Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly);
};