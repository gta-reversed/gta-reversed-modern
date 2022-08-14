#include "StdInc.h"
#include "EntitySeekPosCalculatorStandard.h"

void CEntitySeekPosCalculatorStandard::InjectHooks() {
    RH_ScopedClass(CEntitySeekPosCalculatorStandard);
    RH_ScopedCategory("Tasks/TaskTypes/SeekPosCalculators");

    // RH_ScopedVirtualInstall2(ComputeEntitySeekPos, 0x46af20);
}

void CEntitySeekPosCalculatorStandard::ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) {
    return plugin::CallMethod<0x46af20, CEntitySeekPosCalculatorStandard*, const CPed&, const CEntity&, CVector&>(this, seeker, target, outPos);
}
