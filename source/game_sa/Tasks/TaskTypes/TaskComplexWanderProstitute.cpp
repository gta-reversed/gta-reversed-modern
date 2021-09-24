#include "StdInc.h"

#include "TaskComplexWanderProstitute.h"

CTaskComplexWanderProstitute* CTaskComplexWanderProstitute::Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn<CTaskComplexWanderProstitute*, 0x672690, CTaskComplexWanderProstitute*, int32, uint8, bool>
        (this, MoveState, Dir, bWanderSensibly);
}