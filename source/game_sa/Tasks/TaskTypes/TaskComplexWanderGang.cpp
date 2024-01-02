#include "StdInc.h"

#include "TaskComplexWanderGang.h"

// 0x66F5C0
CTaskComplexWanderGang::CTaskComplexWanderGang(eMoveState moveState, uint8 dir, uint32 scanTime, bool bWanderSensibly, float fTargetRadius)
    : CTaskComplexWander(moveState, dir, bWanderSensibly, fTargetRadius)
{
    m_NextScanTime = scanTime;
    m_TaskTimer.m_nInterval = scanTime;
    m_TaskTimer.m_nStartTime = CTimer::GetTimeInMS();
    m_TaskTimer.m_bStarted = true;
}

// 0x66F640
void CTaskComplexWanderGang::ScanForStuff(CPed* ped) {
    // NOP
}
