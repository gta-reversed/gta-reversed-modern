#pragma once
#include "CTaskComplexWander.h"

class CTaskComplexWanderProstitute : public CTaskComplexWander
{
public:
    CTaskComplexWanderProstitute* Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly);
};