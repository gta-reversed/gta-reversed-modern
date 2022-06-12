#include "StdInc.h"

#include "TaskComplexWanderStandard.h"

// 0x48E4F0
CTaskComplexWanderStandard::CTaskComplexWanderStandard(int32 MoveState, uint8 Dir, bool bWanderSensibly) : CTaskComplexWander(MoveState, Dir, bWanderSensibly) {
    m_nMinNextScanTime = 0;
}

// 0x672600
void CTaskComplexWanderStandard::ScanForStuff(CPed* ped) {
    if (!m_TaskTimer.m_bStarted) {
        m_TaskTimer.m_nStartTime = CTimer::GetTimeInMS();
        m_TaskTimer.m_nInterval = 50;
        m_TaskTimer.m_bStarted = true;
    }

    auto startTime = CTimer::GetTimeInMS();
    if (CTimer::GetTimeInMS() >= m_nMinNextScanTime) {
        if (m_TaskTimer.m_bStarted) {
            if (m_TaskTimer.m_bStopped) {
                m_TaskTimer.m_nStartTime = CTimer::GetTimeInMS();
                m_TaskTimer.m_bStopped = false;
                startTime = CTimer::GetTimeInMS();
            }

            if (startTime >= m_TaskTimer.m_nStartTime + m_TaskTimer.m_nInterval) {
                m_TaskTimer.m_nInterval = 50;
                m_TaskTimer.m_nStartTime = startTime;
                m_TaskTimer.m_bStarted = true;
                if (!LookForGangMembers(ped) && !LookForChatPartners(ped)) {
                    CTaskComplexWanderStandard::LookForSexyCars(ped);
                }
            }
        }
    }
}

// 0x66AED0
bool CTaskComplexWanderStandard::WillChat(const CPed& first, const CPed& second) {
    return plugin::CallMethodAndReturn<bool, 0x66AED0, CTaskComplexWanderStandard*, const CPed&, const CPed&>(this, first, second);
}

// 0x66AF60
void CTaskComplexWanderStandard::SetNextMinScanTime(CPed* ped) {
    plugin::CallMethod<0x66AF60, CTaskComplexWanderStandard*, CPed*>(this, ped);
}

// 0x66AFD0
bool CTaskComplexWanderStandard::LookForSexyCars(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x66AFD0, CTaskComplexWanderStandard*, CPed*>(this, ped);
}

// 0x66FDA0
bool CTaskComplexWanderStandard::LookForChatPartners(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x66FDA0, CTaskComplexWanderStandard*, CPed*>(this, ped);
}

// 0x670100
bool CTaskComplexWanderStandard::LookForGangMembers(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x670100, CTaskComplexWanderStandard*, CPed*>(this, ped);
}
