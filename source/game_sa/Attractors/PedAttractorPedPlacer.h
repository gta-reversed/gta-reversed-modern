#pragma once

#include "2dEffect.h"

class CPed;
class CEntity;

class CPedAttractorPedPlacer {
public:
    static void InjectHooks();

    static void PlacePedAtEffect(C2dEffectPedAttractor const& effect, CEntity* entity, CPed* ped, float forwardOffsetMultiplier);
};
