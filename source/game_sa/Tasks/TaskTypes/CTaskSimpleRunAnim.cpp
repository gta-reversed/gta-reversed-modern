#include "StdInc.h"

CTaskSimpleRunAnim* CTaskSimpleRunAnim::Constructor(unsigned int animGroup, unsigned int animID, float fBlendDelta, bool bHoldLastFrame)
{
    return plugin::CallMethodAndReturn<CTaskSimpleRunAnim*, 0x61A8B0, CTaskSimpleRunAnim*, unsigned int, unsigned int, float, bool>
        (this, animGroup, animID, fBlendDelta, bHoldLastFrame);
}