#include "StdInc.h"

CTaskSimpleStandStill::CTaskSimpleStandStill(int nTime, bool Looped, bool bUseAnimIdleStance, float fBlendData)
{
    m_nTime = nTime;
    m_timer.m_nStartTime = 0;
    m_timer.m_nInterval = 0;
    m_timer.m_bStarted = false;
    m_timer.m_bStopped = false;
    m_fBlendData = fBlendData;
    m_bLooped = Looped;
    m_bUseAnimIdleStance = bUseAnimIdleStance;
}

CTaskSimpleStandStill::~CTaskSimpleStandStill()
{
    // nothing here
}

CTaskSimpleStandStill* CTaskSimpleStandStill::Constructor(int nTime, bool Looped, bool bUseAnimIdleStance, float fBlendData)
{
    return plugin::CallMethodAndReturn<CTaskSimpleStandStill*,0x62F310, CTaskSimpleStandStill*, int, bool, bool, float>
        (this, nTime, Looped, bUseAnimIdleStance, fBlendData);
}

CTask* CTaskSimpleStandStill::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x635CF0, CTask*>(this);
}

bool CTaskSimpleStandStill::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return plugin::CallMethodAndReturn<bool, 0x4B8690, CTask*, CPed*, int, CEvent*>(this, ped, priority, _event);
}

bool CTaskSimpleStandStill::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x62F370, CTask*, CPed*>(this, ped);
}