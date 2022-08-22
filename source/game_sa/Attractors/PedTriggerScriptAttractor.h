#pragma once

#include "PedAttractor.h"

class NOTSA_EXPORT_VTABLE CPedTriggerScriptAttractor : public CPedAttractor {
public:
    // 0x5EE890
    CPedTriggerScriptAttractor(C2dEffect* effect, CEntity* entity, int a4)
        : CPedAttractor(effect, entity, a4, 5, 1, 1.0f, 30000.0f, 3000.0f, 0.125f, 0.1f, 0.1f, 0.1f) {
    }

    // 0x5EE8F0
    ePedAttractorType GetType() const override { return PED_ATTRACTOR_STOP; }
};
