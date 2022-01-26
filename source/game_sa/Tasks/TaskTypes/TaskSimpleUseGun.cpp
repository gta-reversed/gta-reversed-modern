#include "StdInc.h"

#include "TaskSimpleUseGun.h"

// 0x61DE60
CTaskSimpleUseGun::CTaskSimpleUseGun(CEntity* targetEntity, CVector vecTarget, uint8 nCommand, uint16 nBurstLength, bool bAimImmediate) : CTaskSimple() {
    plugin::CallMethodAndReturn<CTaskSimpleUseGun*, 0x61DE60, CTaskSimpleUseGun*, CEntity*, CVector, uint8, uint16, bool>(this, targetEntity, vecTarget, nCommand, nBurstLength, bAimImmediate);
}

// 0x61DF30
CTaskSimpleUseGun::~CTaskSimpleUseGun() {
    if (m_pTarget)
        m_pTarget->CleanUpOldReference(&m_pTarget);

    if (m_pAnim)
        m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
}

bool CTaskSimpleUseGun::ControlGunMove(CVector2D* moveSpeed) {
    return plugin::CallMethodAndReturn<bool, 0x61E0C0, CTaskSimpleUseGun*, CVector2D*>(this, moveSpeed);
}

bool CTaskSimpleUseGun::PlayerPassiveControlGun() {
    return plugin::CallMethodAndReturn<bool, 0x61E0A0, CTaskSimpleUseGun*>(this);
}

bool CTaskSimpleUseGun::RequirePistolWhip(CPed* ped, CEntity* targetEntity) {
    return plugin::CallAndReturn<bool, 0x61E200, CPed*, CEntity*>(ped, targetEntity);
}

bool CTaskSimpleUseGun::ControlGun(CPed* ped, CEntity* target, int8 nCount) {
    return plugin::CallMethodAndReturn<bool, 0x61E040, CTaskSimpleUseGun*, CPed*, CEntity*, int8>(this, ped, target, nCount);
}

int32 CTaskSimpleUseGun::SkipAim(CPed* ped) {
    return plugin::CallMethodAndReturn<int32, 0x61DFA0, CTaskSimpleUseGun*, CPed*>(this, ped);
}

int32 CTaskSimpleUseGun::ClearAnim(CPed* ped) {
    return plugin::CallMethodAndReturn<int32, 0x61E190, CTaskSimpleUseGun*, CPed*>(this, ped);
}

// 0x624E30
bool CTaskSimpleUseGun::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x624E30, CTaskSimpleUseGun*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

// 0x62A380
bool CTaskSimpleUseGun::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x62A380, CTaskSimpleUseGun*, CPed*>(this, ped);
}

// 0x624ED0
bool CTaskSimpleUseGun::SetPedPosition(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x624ED0, CTaskSimpleUseGun*, CPed*>(this, ped);
}

void CTaskSimpleUseGun::InjectHooks() {
    RH_ScopedClass(CTaskSimpleUseGun);
    RH_ScopedCategory("Task/TaskTypes");
    using namespace ReversibleHooks;
}

CTaskSimpleUseGun* CTaskSimpleUseGun::Constructor(CEntity* targetEntity, CVector vecTarget, uint8 nCommand, uint16 nBurstLength, bool bAimImmediate) {
    this->CTaskSimpleUseGun::CTaskSimpleUseGun(targetEntity, vecTarget, nCommand, nBurstLength, bAimImmediate);
    return this;
}
