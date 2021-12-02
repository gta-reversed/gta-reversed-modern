#include "StdInc.h"

#include "TaskComplexWanderStandard.h"

CTaskComplexWanderStandard* CTaskComplexWanderStandard::Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn <CTaskComplexWanderStandard*, 0x48E4F0, CTaskComplexWanderStandard*, int32, uint8, bool>
        (this, MoveState, Dir, bWanderSensibly);
}