#include "StdInc.h"

#include "TaskComplexWanderMedic.h"

// 0x658770
CTaskComplexWanderMedic::CTaskComplexWanderMedic(int32 MoveState, uint8 Dir, bool bWanderSensibly) : CTaskComplexWander(MoveState, Dir, bWanderSensibly) { }

// 0x6587A0
CTask* CTaskComplexWanderMedic::Clone() {
    return new CTaskComplexWanderMedic(m_nMoveState, m_nDir, m_bWanderSensibly);
}
