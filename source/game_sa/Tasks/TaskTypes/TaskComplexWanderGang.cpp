#include "StdInc.h"

#include "TaskComplexWanderGang.h"

// 0x66F5C0
CTaskComplexWanderGang::CTaskComplexWanderGang(eMoveState moveState, uint8 dir, int a4, bool bWanderSensibly, float fTargetRadius)
    : CTaskComplexWander(moveState, dir, bWanderSensibly, fTargetRadius)
{
    m_nTime = 0;
    // dword2C = 0; V519 The 'dword2C' variable is assigned values twice successively. Perhaps this is a mistake.
    byte30 = 0;
    byte31 = 0;
    dword34 = a4;
    dword2C = a4;
    m_nTime = CTimer::GetTimeInMS();
    byte30 = 1;
}

// 0x66F640
void CTaskComplexWanderGang::ScanForStuff(CPed* ped) {
    // NOP
}
