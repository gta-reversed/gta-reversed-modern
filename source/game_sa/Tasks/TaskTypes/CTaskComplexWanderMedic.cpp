#include "StdInc.h"

CTaskComplexWanderMedic* CTaskComplexWanderMedic::Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn<CTaskComplexWanderMedic*, 0x658770, CTaskComplexWanderMedic*, int, unsigned char, bool>
        (this, MoveState, Dir, bWanderSensibly);
}
