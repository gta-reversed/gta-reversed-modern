#pragma once

#include "Base.h"

#include "Vector.h"

struct C2dEffectInterior;
class  CEntity;

struct InteriorEffectInfo_t {
    CEntity*           Entity;
    size_t             NumFx;
    C2dEffectInterior* Effects[8];
    int32              FxIds[8];
    float              DistSq; ///< Min dist. sq. to camera from any of the effects (in the `Effects` array)
    bool               IsCulled;
};
VALIDATE_SIZE(InteriorEffectInfo_t, 0x50);
