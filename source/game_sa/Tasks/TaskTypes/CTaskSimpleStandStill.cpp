#include "StdInc.h"

CTaskSimpleStandStill* CTaskSimpleStandStill::Constructor(int nTime, bool Looped, bool bUseAnimIdleStance, float fBlendData)
{
    return plugin::CallMethodAndReturn<CTaskSimpleStandStill*,0x62F310, CTaskSimpleStandStill*, int, bool, bool, float>
        (this, nTime, Looped, bUseAnimIdleStance, fBlendData);
}