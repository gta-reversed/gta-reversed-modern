#pragma once
#include "CTaskSimpleGoTo.h"

class CTaskSimpleGoToPointFine : public CTaskSimpleGoTo 
{
    float field_20;
};

VALIDATE_SIZE(CTaskSimpleGoToPointFine, 0x24);