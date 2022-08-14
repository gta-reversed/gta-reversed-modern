#pragma once

#include "EntitySeekPosCalculator.h"

class CEntitySeekPosCalculatorStandard : public CEntitySeekPosCalculator {
public:
    static void InjectHooks();

    virtual void ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos);
};
