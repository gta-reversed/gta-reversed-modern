#pragma once

#include "CTaskSimpleGoTo.h"

class CTaskSimpleGoToPoint : public CTaskSimpleGoTo
{
public:
    CVector field_24;
};

VALIDATE_SIZE(CTaskSimpleGoToPoint, 0x30);