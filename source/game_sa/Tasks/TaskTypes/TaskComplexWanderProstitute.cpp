#include "StdInc.h"

#include "TaskComplexWanderProstitute.h"

// 0x672690
CTaskComplexWanderProstitute::CTaskComplexWanderProstitute(int32 MoveState, uint8 Dir, bool bWanderSensibly) : CTaskComplexWanderStandard(MoveState, Dir, bWanderSensibly) {
    m_nStartTimeInMs = 0;
}

// 0x6726C0
CTask* CTaskComplexWanderProstitute::Clone() {
    return new CTaskComplexWanderProstitute(m_nMoveState, m_nDir, m_bWanderSensibly);
}

// 0x674920
CTask* CTaskComplexWanderProstitute::CreateFirstSubTask(CPed* ped) {
    return CTaskComplexWander::CreateFirstSubTask(ped);
}

// 0x672700
void CTaskComplexWanderProstitute::ScanForStuff(CPed* ped) {
    plugin::CallMethod<0x672700, CTaskComplexWanderProstitute*, CPed*>(this, ped);
}
