#include "StdInc.h"

CTaskComplexWanderProstitute* CTaskComplexWanderProstitute::Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn<CTaskComplexWanderProstitute*, 0x672690, CTaskComplexWanderProstitute*, int, unsigned char, bool>
        (this, MoveState, Dir, bWanderSensibly);
}