#include "StdInc.h"

CTaskComplexWanderMedic* CTaskComplexWanderMedic::Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly)
{
    return plugin::CallMethodAndReturn<CTaskComplexWanderMedic*, 0x658770, CTaskComplexWanderMedic*, int, unsigned char, bool>
        (this, MoveState, Dir, bWanderSensibly);
}

CTaskComplexWanderMedic::CTaskComplexWanderMedic(int MoveState, unsigned char Dir, bool bWanderSensibly) : CTaskComplexWander(plugin::dummy)
{
    Constructor(MoveState, Dir, bWanderSensibly);
}

CTask* CTaskComplexWanderMedic::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x6587A0, CTaskComplexWanderMedic*>(this);
}

