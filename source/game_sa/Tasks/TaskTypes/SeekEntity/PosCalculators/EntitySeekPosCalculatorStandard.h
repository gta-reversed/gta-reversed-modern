#pragma once

#include "EntitySeekPosCalculator.h"

class CEntitySeekPosCalculatorStandard : public CEntitySeekPosCalculator {
public:
    //CEntitySeekPosCalculatorStandard(CEntity* entity, int32 time, int32 a3, float radius, float a5, float a6, bool a7, bool a8);
    static void InjectHooks();

    void ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) override;
};
VALIDATE_SIZE(CEntitySeekPosCalculatorStandard, 0x4);
