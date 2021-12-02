/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Object.h"

class CProjectile : public CObject {
public:
    CProjectile(int32 dwModelId);
};

VALIDATE_SIZE(CProjectile, 0x17C);
