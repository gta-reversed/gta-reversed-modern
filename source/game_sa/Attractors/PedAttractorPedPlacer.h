#pragma once

#include "2dEffect.h"

class CPed;
class CEntity;
class C2dEffect;

class CPedAttractorPedPlacer {
public:
    static void InjectHooks();

    static void PlacePedAtEffect(C2dEffect const& effect, CEntity* entity, CPed* ped, float forwardOffsetMultiplier);
};
