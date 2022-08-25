#pragma once

#include "Ped.h"

class NOTSA_EXPORT_VTABLE CCivilianPed : public CPed {
public:
    CCivilianPed(ePedType pedType, uint32 modelIndex);
    ~CCivilianPed() override = default; // 0x5DDBE0

    void ProcessControl() override;
};

VALIDATE_SIZE(CCivilianPed, 0x79C);
