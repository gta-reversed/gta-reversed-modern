#pragma once

class CEntity;
class CVector;
class CPed;

class CEntitySeekPosCalculator {
public:
    static void InjectHooks() {}

    virtual ~CEntitySeekPosCalculator() = default;

    virtual void ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) = 0;
};
