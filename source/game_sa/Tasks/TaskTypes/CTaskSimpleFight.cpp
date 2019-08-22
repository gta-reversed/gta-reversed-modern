#include "StdInc.h"

bool CTaskSimpleFight::ControlFight(CEntity* pEntity, unsigned char command)
{
    return plugin::CallMethodAndReturn<bool, 0x61C5E0, CTaskSimpleFight*, CEntity*, unsigned char>(this, pEntity, command);
}