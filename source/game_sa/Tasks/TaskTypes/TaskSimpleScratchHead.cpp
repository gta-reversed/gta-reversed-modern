#include "StdInc.h"

#include "CTaskSimpleScratchHead.h"

CTaskSimpleScratchHead* CTaskSimpleScratchHead::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskSimpleScratchHead*, 0x48DF30, CTaskSimpleScratchHead*> (this);
}