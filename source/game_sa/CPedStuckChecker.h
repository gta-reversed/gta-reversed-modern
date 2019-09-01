#pragma once
#include "PluginBase.h"
#include "RenderWare.h"

class CPed;
class CEventGroup;

class CPedStuckChecker
{
public:
    RwV3d field_0;
    short field_C;
    short field_E;

    bool TestPedStuck(CPed* pPed, CEventGroup* pEventGroup);
};

VALIDATE_SIZE(CPedStuckChecker, 0x10);