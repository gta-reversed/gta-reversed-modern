#pragma once
#include "CTaskComplexWander.h"

class CTaskComplexWanderMedic : public CTaskComplexWander
{
public:
    CTaskComplexWanderMedic* Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly);
};