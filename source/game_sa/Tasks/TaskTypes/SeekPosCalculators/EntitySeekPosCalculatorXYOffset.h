#pragma once

#include "EntitySeekPosCalculator.h"

class CEntitySeekPosCalculatorXYOffset : public CEntitySeekPosCalculator {
public:
    static void InjectHooks();

    void ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) override;
};
