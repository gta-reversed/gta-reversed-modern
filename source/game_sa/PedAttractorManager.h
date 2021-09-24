#pragma once

class CPedAttractorManager {
    uint8 ucPad[120];

public:
    bool HasEmptySlot(C2dEffect const* pEffect, CEntity const* pEntity);
};

VALIDATE_SIZE(CPedAttractorManager, 0x78);

CPedAttractorManager* GetPedAttractorManager();
