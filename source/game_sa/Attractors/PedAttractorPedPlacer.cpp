#include "StdInc.h"
#include "PedAttractorPedPlacer.h"

void CPedAttractorPedPlacer::InjectHooks() {
    RH_ScopedClass(CPedAttractorPedPlacer);
    RH_ScopedCategory("Attractors");

    RH_ScopedGlobalInstall(PlacePedAtEffect, 0x5EA390, {.reversed = false});
}

// 0x5EA390
void CPedAttractorPedPlacer::PlacePedAtEffect(C2dEffectPedAttractor const& effect, CEntity* entity, CPed* ped, float forwardOffsetMultiplier) {
    return plugin::CallAndReturn<void, 0x5EA390, C2dEffectPedAttractor const&, CEntity*, CPed*, float>(effect, entity, ped, forwardOffsetMultiplier);
}
