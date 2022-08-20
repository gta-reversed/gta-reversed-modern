#pragma once

#include "PedAttractor.h"

class NOTSA_EXPORT_VTABLE CPedStopAttractor : public CPedAttractor {
public:
    // 0x5EE610
    CPedStopAttractor(C2dEffect* effect, CEntity* entity, int a4)
        : CPedAttractor(effect, entity, a4, 5, 1.0f, 30000.0f, 3000.0f, 0.2f, 0.1f, 0.1f, 0.1f, 0) {
    }

    // 0x5EE670
    ePedAttractorType GetType() const override { return PED_ATTRACTOR_STOP; }
};