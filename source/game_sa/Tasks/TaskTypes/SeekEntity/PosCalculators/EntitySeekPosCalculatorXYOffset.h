#pragma once

#include "Base.h"
#include "EntitySeekPosCalculator.h"

class CEntity;

class CEntitySeekPosCalculatorXYOffset : public CEntitySeekPosCalculator {
    CVector m_offsetXY;
public:
    static void InjectHooks();

    void ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) override;
};
VALIDATE_SIZE(CEntitySeekPosCalculatorXYOffset, 0x10);
