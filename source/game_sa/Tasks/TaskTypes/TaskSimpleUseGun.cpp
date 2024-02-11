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
    RH_ScopedInstall(Reset, 0x624DC0);
    //RH_ScopedInstall(AimGun, 0x61ED10, { .reversed = false });
    RH_ScopedInstall(FireGun, 0x61EB10);
    //RH_ScopedInstall(StartCountDown, 0x61E160, { .reversed = false });
    RH_ScopedInstall(ClearAnim, 0x61E190);
    RH_ScopedInstall(PlayerPassiveControlGun, 0x61E0A0);
    RH_ScopedInstall(ControlGun, 0x61E040);
    RH_ScopedInstall(AbortIK, 0x61DFA0);
    RH_ScopedInstall(ControlGunMove, 0x61E0C0);
    RH_ScopedInstall(RemoveStanceAnims, 0x61E8E0);
    RH_ScopedVMTInstall(Clone, 0x622F20);
    RH_ScopedVMTInstall(GetTaskType, 0x61DF20);
    RH_ScopedVMTInstall(MakeAbortable, 0x624E30);
    RH_ScopedVMTInstall(ProcessPed, 0x62A380, { .reversed = false });
    RH_ScopedVMTInstall(SetPedPosition, 0x624ED0);
}

// 0x61DE60
CTaskSimpleUseGun::CTaskSimpleUseGun(CEntity* targetEntity, CVector vecTarget, eGunCommand firstCmd, uint16 burstLength, bool isAimImmediate) :
    m_NextCmd{ firstCmd },
    m_TargetPos{ vecTarget },
    m_TargetEntity{ targetEntity },
    m_BurstShots{ burstLength },
    m_IsAimImmediate{ isAimImmediate } {
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

// 0x61EB10
void CTaskSimpleUseGun::FireGun(CPed* ped, bool isLeftHand) {
    const auto DoFireGun = [&](CVector origin, CVector gunBarrelOffset) {
        ped->GetActiveWeapon().Fire(
            ped,
            &origin,
            &gunBarrelOffset,
            m_TargetEntity,
            m_TargetPos.x != 0.f && m_TargetPos.y != 0.f ? &m_TargetPos : nullptr,
            nullptr
        );
    };

    if (ped->bCalledPreRender) { // If pre-render was called, the bone positions are up-to-date
        const auto& gunBarrelOffset = m_WeaponInfo->m_vecFireOffset;
        const auto handBoneId = isLeftHand ? BONE_L_HAND : BONE_R_HAND;
        CVector origin = ped->GetBonePosition(handBoneId);
        origin.z += gunBarrelOffset.z + 0.15f;
        ped->GetTransformedBonePosition(origin, handBoneId);
        if (!ped->m_pedIK.bUseArm) {
            ped->m_pedIK.bGunReachedTarget = g_ikChainMan.IsFacingTarget(ped, isLeftHand ? 2 : 1);
        }
        DoFireGun(origin, gunBarrelOffset);
    } else { // Otherwise ped is probably not on screen anways, so just do something good enough
        CVector origin = ped->GetPosition();
        origin.z += 0.7f;
        DoFireGun(origin, origin);
    }

    if (ped->GetActiveWeapon().GetState() == WEAPONSTATE_FIRING) {
        ped->DoGunFlash(250, isLeftHand);
    }
}

// 0x61E0A0
bool CTaskSimpleUseGun::PlayerPassiveControlGun() {
    m_IsInControl               = true;
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
    const auto IsPistolWhipRequiredForPed = [&,
                                             &pedPos = ped->GetPosition()](CPed& otherPed) {
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
void CTaskSimpleUseGun::AbortIK(CPed* ped) {
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
    if (m_LastCmd < eGunCommand::END_LEISURE) {
        m_LastCmd = eGunCommand::NONE;
    }
    AbortIK(ped);
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
    AbortIK(ped);
    if (const auto pd = ped->m_pPlayerData) {
        pd->m_fAttackButtonCounter = 0.f;
    }
    return true;
}

// 0x62A380
bool CTaskSimpleUseGun::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x62A380>(this, ped);
    /*
    * Code so far (should be) good, but has to be finished...
    * 
    m_IsLookIKInUse    = m_IsLookIKInUse && g_ikChainMan.IsLooking(ped);
    m_IsArmIKInUse     = m_IsArmIKInUse && g_ikChainMan.IsArmPointing(0, ped);
    m_FireGunThisFrame = false;

    if (m_WeaponInfo) { // Inverted
        if (m_WeaponInfo != &ped->GetActiveWeapon().GetWeaponInfo(ped)) {
            MakeAbortable(ped);
        }
    } else {
        if (const auto pd = ped->m_pPlayerData) {
            if (pd->m_nChosenWeapon != ped->m_nActiveWeaponSlot) {
                return false;
            }
        }
        m_WeaponInfo = &ped->GetActiveWeapon().GetWeaponInfo(ped);
        if (m_WeaponInfo->m_nWeaponFire == 0 || m_WeaponInfo->flags.bThrow) {
            m_IsFinished = true;
            m_WeaponInfo = nullptr;

            AbortIK(ped);
            if (const auto pd = ped->m_pPlayerData) {
                pd->m_fAttackButtonCounter = 0.f;
            }
            return true;
        }
        m_MoveCmd = { 0.f, 0.f };
    }

    if (!m_WeaponInfo->flags.b1stPerson || !ped->m_pPlayerData) {
        ped->bTestForBlockedPositions = true;
    }

    if (!m_IsFinished) {
        if (const auto pd = ped->m_pPlayerData) {
            pd->m_fAttackButtonCounter *= std::pow(0.96f, CTimer::GetTimeStep());
        }
        if (m_IsInControl) {
            m_CountDownFrames = -1;
            if (ped->bDuckRightArmBlocked && (ped->bGetUpAnimStarted || !m_WeaponInfo->flags.bAimWithArm)) {
                if (m_LastCmd != eGunCommand::PISTOLWHIP && (m_NextCmd != eGunCommand::PISTOLWHIP || m_Anim)) { // 0x62A532
                    if (m_Anim) {
                        m_Anim->SetBlendDelta(-4.f);
                        m_Anim->SetFlag(ANIMATION_STARTED, false);
                        m_Anim->SetFlag(ANIMATION_FREEZE_LAST_FRAME, true);
                    } else if (notsa::contains({ eGunCommand::AIM, eGunCommand::FIRE, eGunCommand::FIREBURST }, m_NextCmd)) { // 0x62A63B - Inverted
                        AbortIK(ped);
                        m_IsLOSBlocked = true;
                        if (m_LastCmd == eGunCommand::FIREBURST) {
                            m_LastCmd = eGunCommand::AIM;
                        }

                    SET_MOVE_ANIM_AND_COMMAND_RET_0: // 0x62A586
                        if (m_WeaponInfo->flags.bAimWithArm || ped->bIsDucking || m_HasMoveControl) {
                            SetMoveAnim(ped);
                        }
                        if (m_NextCmd < eGunCommand::END_LEISURE) {
                            if (m_NextCmd != eGunCommand::RELOAD || notsa::contains({ eGunCommand::FIRE, eGunCommand::FIREBURST }, m_LastCmd)) {
                                m_NextCmd = eGunCommand::NONE;
                            }
                        }
                        m_IsInControl = false;
                        return false;
                    }
                }
            } else if (m_NextCmd == eGunCommand::PISTOLWHIP && m_LastCmd <= eGunCommand::FIREBURST) { // 0x62A5E4
                if (m_Anim) {
                    m_Anim->SetDefaultDeleteCallback();
                    m_Anim = nullptr;
                }
                AbortIK(ped);
            }

            if (!m_Anim) { // 0x62A55B
                StartAnim(ped);
                if (!m_Anim) {
                    AbortIK(ped);
                }
                goto SET_MOVE_ANIM_AND_COMMAND_RET_0;
            }

            if (m_LastCmd == eGunCommand::RELOAD) { // 0x62A65A
                if (notsa::contains({ ANIM_ID_RELOAD, ANIM_ID_CROUCHRELOAD }, m_Anim->GetAnimId())) {
                    if (m_Anim->GetBlendDelta() >= 0.f) {
                        m_Anim->SetBlendDelta(-4.f);
                    }
                }
                m_SkipAim = false;
                if (ped->m_pedIK.bUseArm) { // 0x62ACB7
                    bool isAimTargetPedDead;
                    const auto aimTargetPos = GetAimTargetPosition(ped, isAimTargetPedDead);
                    if (aimTargetPos.x != 0.f || aimTargetPos.y != 0.f) {
                        const auto aimDir = (aimTargetPos - ped->GetPosition()).Normalized(); // 0x62ADF0
                        const auto targetAngleToUs = CGeneral::LimitRadianAngle(aimDir.Heading() - ped->m_fCurrentRotation);
                        m_SkipAim = [&, this]{
                            if (isAimTargetPedDead) {
                                if (RWDEG2RAD(115.f - 40.f) < targetAngleToUs || targetAngleToUs < -RWDEG2RAD(130.f - 40.f)) {
                                    return true;
                                }
                                if (aimDir.Dot(ped->GetUpVector()) < -0.8f) { // 0x62AE84
                                    return true;
                                }
                            } else {
                                if (RWDEG2RAD(115.f) < targetAngleToUs || targetAngleToUs < -RWDEG2RAD(130.f)) {
                                    return true;
                                }
                            }
                            return m_SkipAim;
                        }();
                    }
                    m_SkipAim |= ped->bIsDucking && ped->bDuckRightArmBlocked; // 0x62AEB6
                }
            }
        }
    }
    */
}

// 0x624ED0
bool CTaskSimpleUseGun::SetPedPosition(CPed* ped) {
    if (m_WeaponInfo == &ped->GetActiveWeapon().GetWeaponInfo(ped)) {
        if (m_IsFiringGunRightHandThisFrame) { // Right hand
            FireGun(ped, false);
            m_IsFiringGunRightHandThisFrame = false;
        }
        if (m_IsFiringGunLeftHandThisFrame) { // Left hand
            FireGun(ped, true);
            m_IsFiringGunLeftHandThisFrame = false;
        }
    }
    return false;
}

// notsa
CVector CTaskSimpleUseGun::GetAimTargetPosition(CPed* ped, bool& outIsTargetPedDead) const {
    if (m_TargetEntity) {
        if (m_TargetEntity->IsPed()) {
            outIsTargetPedDead = m_TargetEntity->AsPed()->m_fHealth <= 0.f;
            return m_TargetEntity->AsPed()->GetBonePosition(BONE_SPINE1);
        }
        return m_TargetEntity->GetPosition();
    }
    if (ped->IsPlayer() && TheCamera.m_aCams[0].m_nMode == MODE_AIMWEAPON) {
        CVector src, target;
        TheCamera.Find3rdPersonCamTargetVector(20.f, ped->GetPosition() + CVector{0.f, 0.f, 0.7f}, src, target);
        return target;
    }
    return m_TargetPos;
}

// 0x624DC0
void CTaskSimpleUseGun::Reset(CPed* ped, CEntity* targetEntity, CVector targetPos, eGunCommand, int16 burstLength) {
    AbortIK(ped);

    m_TargetPos       = targetPos;
    m_BurstLength     = burstLength;
    m_BurstShots      = 0;
    m_CountDownFrames = -1;
    m_IsLOSBlocked    = false;
    m_IsArmIKInUse    = false;
    m_IsLookIKInUse   = false;
    m_TargetEntity    = targetEntity;
}
