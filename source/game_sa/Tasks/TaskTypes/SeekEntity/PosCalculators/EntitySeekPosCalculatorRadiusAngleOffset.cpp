#include "StdInc.h"

#include "EntitySeekPosCalculatorRadiusAngleOffset.h"

void CEntitySeekPosCalculatorRadiusAngleOffset::InjectHooks() {
    RH_ScopedClass(CEntitySeekPosCalculatorRadiusAngleOffset);
    RH_ScopedCategory("Tasks/TaskTypes/SeekPosCalculators");

    // RH_ScopedVirtualInstall2(ComputeEntitySeekPos, 0x6946f0);
}

void CEntitySeekPosCalculatorRadiusAngleOffset::ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) {
    return plugin::CallMethod<0x6946f0, CEntitySeekPosCalculatorRadiusAngleOffset*, const CPed&, const CEntity&, CVector&>(this, seeker, target, outPos);
}
