#include "StdInc.h"

#include "IKChainManager_c.h"
#include "TaskSimpleUseGun.h"
#include "TaskSimpleGetUp.h"

void CTaskSimpleUseGun::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleUseGun, 0x86D724, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    //RH_ScopedInstall(Constructor, 0x61DE60);
    //RH_ScopedInstall(Destructor, 0x61DF30);

    RH_ScopedGlobalInstall(RequirePistolWhip, 0x61E200);
    RH_ScopedInstall(Reset, 0x624DC0, { .reversed = false });
    //RH_ScopedInstall(AimGun, 0x61ED10, { .reversed = false });
    //RH_ScopedInstall(FireGun, 0x61EB10, { .reversed = false });
    //RH_ScopedInstall(StartCountDown, 0x61E160, { .reversed = false });
    RH_ScopedInstall(ClearAnim, 0x61E190);
    RH_ScopedInstall(PlayerPassiveControlGun, 0x61E0A0);
    RH_ScopedInstall(ControlGun, 0x61E040);
    RH_ScopedInstall(SkipAim, 0x61DFA0);
    RH_ScopedInstall(ControlGunMove, 0x61E0C0);
    RH_ScopedInstall(RemoveStanceAnims, 0x61E8E0);
    RH_ScopedVMTInstall(Clone, 0x622F20);
    RH_ScopedVMTInstall(GetTaskType, 0x61DF20, { .reversed = false });
    RH_ScopedVMTInstall(MakeAbortable, 0x624E30);
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

// 0x61E8E0
void CTaskSimpleUseGun::RemoveStanceAnims(CPed* ped, float x) {
    plugin::CallMethod<0x61E8E0>(this, ped, x);
}

// 0x61E200
bool CTaskSimpleUseGun::RequirePistolWhip(CPed* ped, CEntity* targetEntity) {
    if (const auto tUseGun = ped->GetIntelligence()->GetTaskUseGun()) {
        if (tUseGun->GetLastGunCommand() == eGunCommand::PISTOLWHIP) {
            return false;
        }
    }
    const auto IsPistolWhipRequiredForPed = [
        &,
        &pedPos = ped->GetPosition()
    ](CPed& otherPed) {
        if (!otherPed.IsAlive()) { // Ped is dead :D
            return false;
        }
        const auto forPedHeadPos = otherPed.GetBonePosition(BONE_HEAD);
        if (pedPos.z >= forPedHeadPos.z || pedPos.z + 1.5f <= forPedHeadPos.z) { // Ped is below/above us
            return false;
        }
        if (otherPed.bFallenDown && !CTask::DynCast<CTaskSimpleGetUp>(ped->GetTaskManager().GetSimplestActiveTask())) { // Fell, but hasn't got up yet?
            return false;
        }
        const auto pedToOther = otherPed.GetPosition() - ped->GetPosition();
        if (pedToOther.SquaredMagnitude2D() >= 1.f) {
            return false;
        }
        const auto pedToOtherDot = ped->GetForward().Dot(pedToOther);
        if (pedToOtherDot <= 0.f) { // Is behind?
            return false;
        }
        if (std::abs(ped->GetRight().Dot(pedToOther)) / pedToOtherDot >= 1.f / SQRT_3) { // 1/sqrt3 = 0.57730001
            return false;
        }
        return true;
    };
    return targetEntity && targetEntity->IsPed()
        ? IsPistolWhipRequiredForPed(*targetEntity->AsPed())
        : rng::any_of(ped->GetIntelligence()->GetPedScanner().GetEntities<CPed>(), IsPistolWhipRequiredForPed);
}

// 0x61E040
bool CTaskSimpleUseGun::ControlGun(CPed* ped, CEntity* target, eGunCommand cmd) {
    m_IsInControl = true;
    if (target != m_TargetEntity) { // New target?
        m_TargetEntity  = target;
        m_IsArmIKInUse  = false;
        m_IsLookIKInUse = false;
    }
    m_NextCmd = std::max(cmd, m_NextCmd);
    return true;
}

// 0x61DFA0
void CTaskSimpleUseGun::SkipAim(CPed* ped) {
    if (m_IsArmIKInUse) {
        for (int32 armN = 0; armN < 2; armN++) {
            g_ikChainMan.AbortPointArm(armN, ped); // No need to call IsArmPointing, as AbortPointArm does checks too...
        }
        m_IsArmIKInUse = false;
    }
    if (m_IsLookIKInUse) {
        g_ikChainMan.AbortLookAt(ped); // No need to check `IsLooking` here either
        m_IsLookIKInUse = false;
    }
    ped->m_pedIK.bUnk = false;
}

// 0x61E190
void CTaskSimpleUseGun::ClearAnim(CPed* ped) {
    if (m_Anim) {
        if (m_Anim->GetBlendAmount() > 0.f && m_Anim->GetBlendDelta() >= 0.f) {
            m_Anim->SetBlendDelta(-8.f);
        }
        m_Anim->SetDefaultDeleteCallback();
        m_Anim = nullptr;
    }
    if (m_LastCmd != eGunCommand::END_NOW) {
        m_LastCmd = eGunCommand::NONE;
    }
    SkipAim(ped);
}

// 0x624E30
bool CTaskSimpleUseGun::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (priority == ABORT_PRIORITY_LEISURE) {
        m_NextCmd = eGunCommand::END_LEISURE;
        return false;
    }
    RemoveStanceAnims(ped, -4.f);
    if (priority == ABORT_PRIORITY_IMMEDIATE) {
        CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 1000.f);
    }
    if (m_Anim) {
        if (priority == ABORT_PRIORITY_IMMEDIATE) {
            m_Anim->SetBlendDelta(-1000.f);
        }
        m_Anim->SetDefaultDeleteCallback();
        m_Anim = nullptr;
    }
    m_IsFinished = true;
    SkipAim(ped);
    if (const auto pd = ped->m_pPlayerData) {
        pd->m_fAttackButtonCounter = 0.f;
    }
    return true;
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
