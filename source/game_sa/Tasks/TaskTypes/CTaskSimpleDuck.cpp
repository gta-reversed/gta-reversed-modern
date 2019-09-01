#include "StdInc.h"

CTaskSimpleDuck* CTaskSimpleDuck::Constructor(eDuckControlTypes DuckControlType, unsigned short nLengthOfDuck, short nUseShotsWhizzingEvents)
{
    return plugin::CallMethodAndReturn<CTaskSimpleDuck*, 0x691FC0, CTaskSimpleDuck*, eDuckControlTypes, unsigned short, short>
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