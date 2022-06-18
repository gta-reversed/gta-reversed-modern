#include "StdInc.h"

#include "EventDeath.h"

// 0x4ADE50, `time` should be int32
CEventDeath::CEventDeath(bool bDrowning, uint32 deathTimeInMs) : CEvent() {
    m_bDrowning = bDrowning;
    m_deathTimeInMs = deathTimeInMs;
}

// 0x4ADDF0
CEventDeath::CEventDeath(bool bDrowning) : CEvent() {
    m_bDrowning = bDrowning;
    m_deathTimeInMs = CTimer::GetTimeInMS();
}

// 0x4B6E30
CEvent* CEventDeath::Clone() {
    return new CEventDeath(m_bDrowning, m_deathTimeInMs);
}
