#include "StdInc.h"

#include "TaskSimpleUseGun.h"

void CTaskSimpleUseGun::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleUseGun, 0x86D724, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    //RH_ScopedInstall(Constructor, 0x61DE60);
    //RH_ScopedInstall(Destructor, 0x61DF30);

    RH_ScopedGlobalInstall(RequirePistolWhip, 0x61E200, { .reversed = false });
    RH_ScopedInstall(Reset, 0x624DC0, { .reversed = false });
    RH_ScopedInstall(AimGun, 0x61ED10, { .reversed = false });
    RH_ScopedInstall(FireGun, 0x61EB10, { .reversed = false });
    RH_ScopedInstall(StartCountDown, 0x61E160, { .reversed = false });
    RH_ScopedInstall(ClearAnim, 0x61E190, { .reversed = false });
    RH_ScopedInstall(PlayerPassiveControlGun, 0x61E0A0);
    RH_ScopedInstall(ControlGun, 0x61E040, { .reversed = false });
    RH_ScopedInstall(SkipAim, 0x61DFA0, { .reversed = false });
    RH_ScopedInstall(ControlGunMove, 0x61E0C0);
    RH_ScopedVMTInstall(Clone, 0x622F20, { .reversed = false });
    RH_ScopedVMTInstall(GetTaskType, 0x61DF20, { .reversed = false });
    RH_ScopedVMTInstall(MakeAbortable, 0x624E30, { .reversed = false });
    RH_ScopedVMTInstall(ProcessPed, 0x62A380, { .reversed = false });
    RH_ScopedVMTInstall(SetPedPosition, 0x624ED0, { .reversed = false });
}

// 0x61DE60
CTaskSimpleUseGun::CTaskSimpleUseGun(CEntity* targetEntity, CVector vecTarget, eGunCommand firstCmd, uint16 burstLength, bool isAimImmediate) :
    m_NextCmd{firstCmd},
    m_TargetPos{vecTarget},
    m_TargetEntity{targetEntity},
    m_BurstShots{burstLength},
    m_IsAimImmediate{isAimImmediate}
{
}

// 0x61DF30
CTaskSimpleUseGun::~CTaskSimpleUseGun() {
    if (m_Anim) {
        m_Anim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x61E0C0
bool CTaskSimpleUseGun::ControlGunMove(const CVector2D& moveDir) {
    const auto maxDelta = CTimer::GetTimeStep() * 0.07f;
    for (size_t i = 0; i < 2; i++) {
        m_MoveCmd[i] = std::clamp(moveDir[i], m_MoveCmd[i] - maxDelta, m_MoveCmd[i] + maxDelta);
    }
    m_HasMoveControl = true;
    return true;
}

// 0x61E0A0
bool CTaskSimpleUseGun::PlayerPassiveControlGun() {
    m_IsInControl = true;
    const auto IsCommandPassive = [](eGunCommand c) {
        return notsa::contains({ eGunCommand::UNKNOWN, eGunCommand::NONE, eGunCommand::AIM }, c);
    };
    if (IsCommandPassive(m_LastCmd) && IsCommandPassive(m_NextCmd)) {
        m_NextCmd = eGunCommand::END_LEISURE;
        return true;
    }
    return false;
}

// 0x61E200
bool CTaskSimpleUseGun::RequirePistolWhip(CPed* ped, CEntity* targetEntity) {
    return plugin::CallAndReturn<bool, 0x61E200, CPed*, CEntity*>(ped, targetEntity);
}

// 0x61E040
bool CTaskSimpleUseGun::ControlGun(CPed* ped, CEntity* target, eGunCommand cmd) {
    return plugin::CallMethodAndReturn<bool, 0x61E040, CTaskSimpleUseGun*, CPed*, CEntity*, eGunCommand>(this, ped, target, cmd);
}

// 0x61DFA0
int32 CTaskSimpleUseGun::SkipAim(CPed* ped) {
    return plugin::CallMethodAndReturn<int32, 0x61DFA0, CTaskSimpleUseGun*, CPed*>(this, ped);
}

// 0x61E190
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

CTaskSimpleUseGun* CTaskSimpleUseGun::Constructor(CEntity* targetEntity, CVector vecTarget, eGunCommand nCommand, uint16 nBurstLength, bool bAimImmediate) {
    this->CTaskSimpleUseGun::CTaskSimpleUseGun(targetEntity, vecTarget, nCommand, nBurstLength, bAimImmediate);
    return this;
}

// 0x624DC0
void CTaskSimpleUseGun::Reset(CPed* ped, CEntity* entity, CVector posn, int8 unused, int16 burstAmmoCnt) {
    plugin::CallMethod<0x624DC0>(this, ped, entity, posn, unused, burstAmmoCnt);
}
