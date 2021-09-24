#pragma once
#include "CTaskComplexWander.h"

class CTaskComplexWanderProstitute : public CTaskComplexWander
{
public:
    CTaskComplexWanderProstitute* Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly);
};