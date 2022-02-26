#include "StdInc.h"
#include "TaskSimpleIKLookAt.h"

void CTaskSimpleIKLookAt::BlendOut(uint32 blendOutTime) {
    if (!m_bIsBlendingOut) {
        if (m_nTime == -1) {
            m_nTime = 0;
        }
        m_nEndTime = CTimer::GetTimeInMS() + blendOutTime;
        m_bIsBlendingOut = true;
    }
}
