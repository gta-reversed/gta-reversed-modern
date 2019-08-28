#include "StdInc.h"

CTaskSimpleFight* CTaskSimpleFight::Constructor(CEntity* pTargetEntity, int nCommand, unsigned int nIdlePeriod)
{
    return plugin::CallMethodAndReturn<CTaskSimpleFight*, 0x61C470, CTaskSimpleFight*, CEntity*, int, unsigned int>
        (this, pTargetEntity, nCommand, nIdlePeriod);
}

bool CTaskSimpleFight::ControlFight(CEntity* pEntity, unsigned char command)
{
    return plugin::CallMethodAndReturn<bool, 0x61C5E0, CTaskSimpleFight*, CEntity*, unsigned char>(this, pEntity, command);
}