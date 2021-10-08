#pragma once
#include "TaskComplexWanderCop.h"

class CTaskComplexBeCop : public CTaskComplexWanderCop
{
    eTaskType GetTaskType() override;

    eTaskType GetId_Reversed();
};

VALIDATE_SIZE(CTaskComplexBeCop, 0x50);
