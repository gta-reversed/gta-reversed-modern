#include "StdInc.h"

CTaskComplexWanderCriminal* CTaskComplexWanderCriminal::Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn<CTaskComplexWanderCriminal*, 0x48E610, CTaskComplexWanderCriminal*, int, unsigned char, bool>
        (this, MoveState, Dir, bWanderSensibly);
}