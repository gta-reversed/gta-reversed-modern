#include "StdInc.h"

CMeleeInfo* CTaskSimpleFight::m_aComboData = (CMeleeInfo*)0xC170D0;

CTaskSimpleFight* CTaskSimpleFight::Constructor(CEntity* pTargetEntity, int nCommand, unsigned int nIdlePeriod) {
    return plugin::CallMethodAndReturn<CTaskSimpleFight*, 0x61C470, CTaskSimpleFight*, CEntity*, int, unsigned int>
        (this, pTargetEntity, nCommand, nIdlePeriod);
}

bool CTaskSimpleFight::ControlFight(CEntity* pEntity, unsigned char command) {
    return plugin::CallMethodAndReturn<bool, 0x61C5E0, CTaskSimpleFight*, CEntity*, unsigned char>(this, pEntity, command);
}

bool CTaskSimpleFight::IsComboSet() {
    return plugin::CallMethodAndReturn<bool, 0x4ABDC0, CTaskSimpleFight*>(this);
}

bool CTaskSimpleFight::IsHitComboSet() {
    return plugin::CallMethodAndReturn<bool, 0x4ABDF0, CTaskSimpleFight*>(this);
}

int CTaskSimpleFight::GetComboAnimGroupID() {
    return plugin::CallMethodAndReturn<int, 0x4ABDA0, CTaskSimpleFight*>(this);
}