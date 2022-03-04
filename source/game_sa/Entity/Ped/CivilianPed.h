/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Ped.h"

class CCivilianPed : public CPed {
public:
    CCivilianPed(ePedType pedType, uint32 modelIndex);
};

VALIDATE_SIZE(CCivilianPed, 0x79C);