#pragma once
#include "PluginBase.h"

class CPedAttractorManager {
    unsigned char ucPad[120];

public:
    bool HasEmptySlot(C2dEffect const* pEffect, CEntity const* pEntity);
};

VALIDATE_SIZE(CPedAttractorManager, 0x78);

CPedAttractorManager* GetPedAttractorManager();
