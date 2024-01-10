#pragma once

#include "Base.h"
#include "Vector.h"

class CEntity;

struct InteriorInfo_t {
    int8     Type;
    bool     IsInUse;
    CVector  Pos;
    CVector  Dir;
    CEntity* EntityIgnoredCollision;
};
VALIDATE_SIZE(InteriorInfo_t, 0x20);
