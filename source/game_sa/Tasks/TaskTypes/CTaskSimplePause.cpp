#include "StdInc.h"

void CTaskSimplePause::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimplePause", "CTaskSimplePause", 0x48E750, &CTaskSimplePause::Constructor);
    ReversibleHooks::Install("CTaskSimplePause", "ProcessPed", 0x48E830, &CTaskSimplePause::ProcessPed_Reversed);
    ReversibleHooks::Install("CTaskSimplePause", "MakeAbortable", 0x48E810, &CTaskSimplePause::MakeAbortable_Reversed);
}

CTaskSimplePause::CTaskSimplePause(int32 time)
{
    m_timer.m_nStartTime = 0;
    m_timer.m_nInterval = 0;
    m_timer.m_bStarted = false;
    m_timer.m_bStopped = false;
    m_nTime = time;
}

CTaskSimplePause::~CTaskSimplePause()
{
    // nothing here
}

CTaskSimplePause* CTaskSimplePause::Constructor(int32 time)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTaskSimplePause*, 0x48E750, CTask*, int32>(this, time);
#else
    this->CTaskSimplePause::CTaskSimplePause(time);
    return this;
#endif
}

CTask* CTaskSimplePause::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x48E780, CTask*>(this);
}

bool CTaskSimplePause::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    m_timer.m_nStartTime = CTimer::m_snTimeInMilliseconds;
    m_timer.m_nInterval = -1;
    m_timer.m_bStarted = true;
    return true;
}

bool CTaskSimplePause::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x48E810, CTask*, CPed*, int32, const CEvent*>(this, ped, priority, event);
#else
    return CTaskSimplePause::MakeAbortable_Reversed(ped, priority, event);
#endif
}

bool CTaskSimplePause::ProcessPed_Reversed(CPed* ped)
{
    if (!m_timer.m_bStarted && !m_timer.Start(m_nTime)) {
        return false;
    }
    m_timer.Reset();
    return m_timer.IsOutOfTime();
}

bool CTaskSimplePause::ProcessPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x48E830, CTaskSimplePause*, CPed*>(this, ped);
#else
    return CTaskSimplePause::ProcessPed_Reversed(ped);
#endif
}
