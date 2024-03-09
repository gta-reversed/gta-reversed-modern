#include "StdInc.h"

#include "TaskSimpleUseGun.h"

// 0x61DE60
CTaskSimpleUseGun::CTaskSimpleUseGun(CEntity* targetEntity, CVector vecTarget, eGunCommand nCommand, uint16 nBurstLength, bool bAimImmediate) : CTaskSimple() {
    plugin::CallMethodAndReturn<CTaskSimpleUseGun*, 0x61DE60, CTaskSimpleUseGun*, CEntity*, CVector, eGunCommand, uint16, bool>(this, targetEntity, vecTarget, nCommand, nBurstLength, bAimImmediate);
}

// 0x61DF30
CTaskSimpleUseGun::~CTaskSimpleUseGun() {
    CEntity::SafeCleanUpRef(m_pTarget);

    if (m_pAnim)
        m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
}

bool CTaskSimpleUseGun::ControlGunMove(const CVector2D& moveSpeed) {
    return plugin::CallMethodAndReturn<bool, 0x61E0C0, CTaskSimpleUseGun*>(this, &moveSpeed);
}

bool CTaskSimpleUseGun::PlayerPassiveControlGun() {
    return plugin::CallMethodAndReturn<bool, 0x61E0A0, CTaskSimpleUseGun*>(this);
}

bool CTaskSimpleUseGun::RequirePistolWhip(CPed* ped, CEntity* targetEntity) {
    return plugin::CallAndReturn<bool, 0x61E200, CPed*, CEntity*>(ped, targetEntity);
}

bool CTaskSimpleUseGun::ControlGun(CPed* ped, CEntity* target, eGunCommand cmd) {
    return plugin::CallMethodAndReturn<bool, 0x61E040, CTaskSimpleUseGun*, CPed*, CEntity*, eGunCommand>(this, ped, target, cmd);
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
    RH_ScopedVirtualClass(CTaskSimpleUseGun, 0x86D724, 9);
    RH_ScopedCategory("Tasks/TaskTypes");
    using namespace ReversibleHooks;
}

CTaskSimpleUseGun* CTaskSimpleUseGun::Constructor(CEntity* targetEntity, CVector vecTarget, eGunCommand nCommand, uint16 nBurstLength, bool bAimImmediate) {
    this->CTaskSimpleUseGun::CTaskSimpleUseGun(targetEntity, vecTarget, nCommand, nBurstLength, bAimImmediate);
    return this;
}

void CTaskSimpleUseGun::Reset(CPed* ped, CEntity* entity, CVector posn, int8 unused, int16 burstAmmoCnt) {
    plugin::CallMethod<0x624DC0>(this, ped, entity, posn, unused, burstAmmoCnt);
}
