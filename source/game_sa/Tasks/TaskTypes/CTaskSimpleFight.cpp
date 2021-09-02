#include "StdInc.h"

CMeleeInfo* CTaskSimpleFight::m_aComboData = (CMeleeInfo*)0xC170D0;

CTaskSimpleFight* CTaskSimpleFight::Constructor(CEntity* pTargetEntity, int32 nCommand, uint32 nIdlePeriod) {
    return plugin::CallMethodAndReturn<CTaskSimpleFight*, 0x61C470, CTaskSimpleFight*, CEntity*, int32, uint32>
        (this, pTargetEntity, nCommand, nIdlePeriod);
}

bool CTaskSimpleFight::ControlFight(CEntity* pEntity, uint8 command) {
    return plugin::CallMethodAndReturn<bool, 0x61C5E0, CTaskSimpleFight*, CEntity*, uint8>(this, pEntity, command);
}

bool CTaskSimpleFight::IsComboSet() {
    return plugin::CallMethodAndReturn<bool, 0x4ABDC0, CTaskSimpleFight*>(this);
}

bool CTaskSimpleFight::IsHitComboSet() {
    return plugin::CallMethodAndReturn<bool, 0x4ABDF0, CTaskSimpleFight*>(this);
}

int32 CTaskSimpleFight::GetComboAnimGroupID() {
    return plugin::CallMethodAndReturn<int32, 0x4ABDA0, CTaskSimpleFight*>(this);
}

void CTaskSimpleFight::LoadMeleeData()
{
    plugin::Call<0x5BEDC0>();
}
