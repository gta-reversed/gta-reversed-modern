#include "StdInc.h"

#include "TaskComplexWanderMedic.h"

CTaskComplexWanderMedic* CTaskComplexWanderMedic::Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn<CTaskComplexWanderMedic*, 0x658770, CTaskComplexWanderMedic*, int32, uint8, bool>
        (this, MoveState, Dir, bWanderSensibly);
}

CTaskComplexWanderMedic::CTaskComplexWanderMedic(int32 MoveState, uint8 Dir, bool bWanderSensibly) : CTaskComplexWander(plugin::dummy)
{
    Constructor(MoveState, Dir, bWanderSensibly);
}

CTask* CTaskComplexWanderMedic::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x6587A0, CTaskComplexWanderMedic*>(this);
}

