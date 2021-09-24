#include "StdInc.h"

#include "TaskSimpleDuck.h"

CTaskSimpleDuck* CTaskSimpleDuck::Constructor(eDuckControlTypes DuckControlType, uint16 nLengthOfDuck, int16 nUseShotsWhizzingEvents)
{
    return plugin::CallMethodAndReturn<CTaskSimpleDuck*, 0x691FC0, CTaskSimpleDuck*, eDuckControlTypes, uint16, int16>
        (this, DuckControlType, nLengthOfDuck, nUseShotsWhizzingEvents);
}

bool CTaskSimpleDuck::CanPedDuck(CPed* pPed)
{
    return plugin::CallAndReturn<bool, 0x692610, CPed*>(pPed);
}

bool CTaskSimpleDuck::ControlDuckMove(float moveSpeedX, float moveSpeedY)
{
    return plugin::CallMethodAndReturn<bool, 0x6923F0, CTaskSimpleDuck*, float, float>(this, moveSpeedX, moveSpeedY);
}

bool CTaskSimpleDuck::IsTaskInUseByOtherTasks()
{
    return plugin::CallMethodAndReturn<bool, 0x61C3D0, CTaskSimpleDuck*>(this);
}