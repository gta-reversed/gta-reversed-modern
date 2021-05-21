/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

void CTaskTimer::InjectHooks() {
    ReversibleHooks::Install("CTaskTimer", "IsOutOfTime", 0x420E30, &CTaskTimer::IsOutOfTime);
}

// 0x420E30
bool CTaskTimer::IsOutOfTime() {
    if (!m_bStarted)
        return false;

    if (m_bStopped) {
        m_nStartTime = CTimer::m_snTimeInMilliseconds;
        m_bStopped = false;
    }

    return CTimer::m_snTimeInMilliseconds >= (m_nStartTime + m_nInterval);
}
