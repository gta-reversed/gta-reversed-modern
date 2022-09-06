#pragma once

#include "EntitySeekPosCalculator.h"
#include "Vector2D.h"

class CEntitySeekPosCalculatorRadiusAngleOffset : public CEntitySeekPosCalculator {
    CVector2D m_offset{};
public:
    static void InjectHooks();
    void ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) override;
};
VALIDATE_SIZE(CEntitySeekPosCalculatorRadiusAngleOffset, 0xC);
