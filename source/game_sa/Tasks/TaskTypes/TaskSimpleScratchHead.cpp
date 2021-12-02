#include "StdInc.h"

#include "TaskSimpleScratchHead.h"

CTaskSimpleScratchHead* CTaskSimpleScratchHead::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskSimpleScratchHead*, 0x48DF30, CTaskSimpleScratchHead*> (this);
}