#include "StdInc.h"

CTaskSimpleStealthKill* CTaskSimpleStealthKill::Constructor(bool bKeepTargetAlive, CPed* pTarget, int nAssocGroupId)
{
    return plugin::CallMethodAndReturn<CTaskSimpleStealthKill*, 0x6225F0, CTaskSimpleStealthKill*, bool, CPed*, int>(this, bKeepTargetAlive, pTarget, nAssocGroupId);
}