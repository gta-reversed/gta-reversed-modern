#pragma once
#include "CTaskComplexWanderCop.h"

class CTaskComplexBeCop : public CTaskComplexWanderCop
{
    eTaskType GetId() override;
};

VALIDATE_SIZE(CTaskComplexBeCop, 0x50);
