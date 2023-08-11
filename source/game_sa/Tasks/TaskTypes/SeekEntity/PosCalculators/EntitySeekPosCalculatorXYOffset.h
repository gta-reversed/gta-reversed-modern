#pragma once

#include "Base.h"
#include "Vector.h"
#include "EntitySeekPosCalculator.h"

class CEntity;

class CEntitySeekPosCalculatorXYOffset : public CEntitySeekPosCalculator {
    CVector m_offsetXY{};
public:
    static void InjectHooks();

    CEntitySeekPosCalculatorXYOffset() = default;

    CEntitySeekPosCalculatorXYOffset(const CVector& offset) :
        m_offsetXY{ offset }
    {
    }

    void ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) override;
    void SetOffset(CVector offset) { m_offsetXY = offset; }
};
VALIDATE_SIZE(CEntitySeekPosCalculatorXYOffset, 0x10);
