#include "StdInc.h"

void CTaskSimplePause::InjectHooks()
{
    HookInstall(0x48E750, &CTaskSimplePause::Constructor, 7);
}

CTaskSimplePause::CTaskSimplePause(int time)
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

CTaskSimplePause* CTaskSimplePause::Constructor(int time)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTaskSimplePause*, 0x48E750, CTask*, int>(this, time);
#else
    this->CTaskSimplePause::CTaskSimplePause(time);
    return this;
#endif
}

CTask* CTaskSimplePause::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x48E780, CTask*>(this);
}

bool CTaskSimplePause::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return plugin::CallMethodAndReturn<bool, 0x48E810, CTask*, CPed*, int, CEvent*>(this, ped, priority, _event);
}

bool CTaskSimplePause::ProcessPed(CPed* ped)
{ 
    return plugin::CallMethodAndReturn<bool, 0x48E830, CTask*, CPed*>(this, ped);
}
