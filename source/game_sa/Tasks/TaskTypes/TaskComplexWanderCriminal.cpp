#include "StdInc.h"

#include "TaskComplexWanderCriminal.h"

CTaskComplexWanderCriminal* CTaskComplexWanderCriminal::Constructor(int32 MoveState, uint8 Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn<CTaskComplexWanderCriminal*, 0x48E610, CTaskComplexWanderCriminal*, int32, uint8, bool>
        (this, MoveState, Dir, bWanderSensibly);
}