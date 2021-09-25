#pragma once

class CPedAttractor;
class C2dEffect;
class CEntity;
class CPed;

class CPedAttractorManager {
    uint8 ucPad[120];

public:
    bool HasEmptySlot(const C2dEffect* effect, const CEntity* entity);
    CPedAttractor* RegisterPed(CPed* ped, C2dEffect* attr, CEntity* entity, int a4, void* attrAry);
};

VALIDATE_SIZE(CPedAttractorManager, 0x78);

CPedAttractorManager* GetPedAttractorManager();
