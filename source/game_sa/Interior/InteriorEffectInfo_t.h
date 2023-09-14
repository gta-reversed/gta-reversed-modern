#pragma once

#include "Base.h"

#include "Vector.h"

struct C2dEffectInterior;
class  CEntity;

struct InteriorEffectInfo_t {
    CEntity*           entity;
    size_t             numFx;
    C2dEffectInterior* fxs[8];
    int32              fxIds[8];
    float              distSq;
    bool8              culled;
};
VALIDATE_SIZE(InteriorEffectInfo_t, 0x50);
