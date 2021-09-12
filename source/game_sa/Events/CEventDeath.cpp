#include "StdInc.h"

void CEventDeath::InjectHooks()
{
    ReversibleHooks::Install("CEventDeath", "Constructor", 0x4ADDF0, &CEventDeath::Constructor);
    ReversibleHooks::Install("CEventDeath", "Clone_Reversed", 0x4B6E30, &CEventDeath::Clone_Reversed);
}

CEventDeath::CEventDeath(bool bDrowning, uint32 deathTimeInMs)
{
    m_bDrowning = bDrowning;
    m_deathTimeInMs = deathTimeInMs;
}

CEventDeath::CEventDeath(bool bDrowning)
{
    m_bDrowning = bDrowning;
    m_deathTimeInMs = CTimer::m_snTimeInMilliseconds;
}

CEventDeath::~CEventDeath()
{
    // nothing here
}

CEventDeath* CEventDeath::Constructor(bool bDrowning)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventDeath*, 0x4ADDF0, CEvent*, bool>(this, bDrowning);
#else
    this->CEventDeath::CEventDeath(bDrowning);
    return this;
#endif
}

CEvent* CEventDeath::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4B6E30, CEvent*>(this);
#else
    return CEventDeath::Clone_Reversed();
#endif
}


CEvent* CEventDeath::Clone_Reversed()
{
    return new CEventDeath(m_bDrowning, m_deathTimeInMs);
}
