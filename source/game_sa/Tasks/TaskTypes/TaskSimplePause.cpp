#include "StdInc.h"

#include "TaskSimplePause.h"

void CTaskSimplePause::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimplePause, 0x85A278, 9);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x48E750);
    RH_ScopedVMTInstall(ProcessPed, 0x48E830);
    RH_ScopedVMTInstall(MakeAbortable, 0x48E810);
}

// 0x48E750
CTaskSimplePause::CTaskSimplePause(int32 time) {
    m_nTime = time;
}

CTaskSimplePause* CTaskSimplePause::Constructor(int32 time) {
    this->CTaskSimplePause::CTaskSimplePause(time);
    return this;
}

CTask* CTaskSimplePause::Clone() const {
    return plugin::CallMethodAndReturn<CTask*, 0x48E780, const CTask*>(this);
}

// 0x48E810
bool CTaskSimplePause::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    m_timer.m_nStartTime = CTimer::GetTimeInMS();
    m_timer.m_nInterval = -1;
    m_timer.m_bStarted = true;
    return true;
}

// 0x48E830
bool CTaskSimplePause::ProcessPed(CPed* ped) {
    if (!m_timer.m_bStarted && !m_timer.Start(m_nTime)) {
        return false;
    }
    m_timer.Reset();
    return m_timer.IsOutOfTime();
}