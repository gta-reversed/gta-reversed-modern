#include "StdInc.h"

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