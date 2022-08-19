#include "StdInc.h"

#include "EntitySeekPosCalculatorXYOffset.h"

void CEntitySeekPosCalculatorXYOffset::InjectHooks() {
    RH_ScopedClass(CEntitySeekPosCalculatorXYOffset);
    RH_ScopedCategory("Tasks/TaskTypes/SeekPosCalculators");

    RH_ScopedVirtualInstall2(ComputeEntitySeekPos, 0x6946a0, { .reversed = false });
}

void CEntitySeekPosCalculatorXYOffset::ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) {
    return plugin::CallMethod<0x6946a0, CEntitySeekPosCalculatorXYOffset*, const CPed&, const CEntity&, CVector&>(this, seeker, target, outPos);
}
