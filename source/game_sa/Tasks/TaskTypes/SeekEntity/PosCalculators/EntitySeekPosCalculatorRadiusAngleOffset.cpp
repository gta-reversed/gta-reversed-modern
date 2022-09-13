#include "StdInc.h"

#include "EntitySeekPosCalculatorRadiusAngleOffset.h"

void CEntitySeekPosCalculatorRadiusAngleOffset::InjectHooks() {
    RH_ScopedClass(CEntitySeekPosCalculatorRadiusAngleOffset);
    RH_ScopedCategory("Tasks/TaskTypes/SeekPosCalculators");

    RH_ScopedVirtualInstall2(ComputeEntitySeekPos, 0x6946f0, { .reversed = false });
}

CEntitySeekPosCalculatorRadiusAngleOffset::CEntitySeekPosCalculatorRadiusAngleOffset(float radius, float angle) :
    m_radius{ radius },
    m_angle{ angle }
{
}

void CEntitySeekPosCalculatorRadiusAngleOffset::ComputeEntitySeekPos(const CPed& seeker, const CEntity& target, CVector& outPos) {
    return plugin::CallMethod<0x6946f0, CEntitySeekPosCalculatorRadiusAngleOffset*, const CPed&, const CEntity&, CVector&>(this, seeker, target, outPos);
}
