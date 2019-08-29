#include "StdInc.h"

CTaskComplexWander* CTaskComplexWander::GetWanderTaskByPedType(CPed* pPed)
{
    return plugin::CallAndReturn<CTaskComplexWander*, 0x673D00, CPed*>(pPed);
}