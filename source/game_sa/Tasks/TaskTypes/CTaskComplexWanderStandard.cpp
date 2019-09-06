#include "StdInc.h"

CTaskComplexWanderStandard* CTaskComplexWanderStandard::Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn <CTaskComplexWanderStandard*, 0x48E4F0, CTaskComplexWanderStandard*, int, unsigned char, bool>
        (this, MoveState, Dir, bWanderSensibly);
}