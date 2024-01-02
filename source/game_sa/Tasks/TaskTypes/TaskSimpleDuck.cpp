#include "StdInc.h"
#include "TaskSimpleDuck.h"
#include "AnimBlendAssociation.h"
#include "TaskSimpleUseGun.h"

void CTaskSimpleDuck::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleDuck, 0x870bc4, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x691FC0);
    RH_ScopedInstall(Destructor, 0x692030);

    RH_ScopedGlobalInstall(DeleteDuckAnimCB, 0x692550);
    RH_ScopedGlobalInstall(CanPedDuck, 0x692610);

    RH_ScopedInstall(IsTaskInUseByOtherTasks, 0x61C3D0);
    RH_ScopedInstall(RestartTask, 0x692390);
    RH_ScopedInstall(ControlDuckMove, 0x6923F0);
    RH_ScopedInstall(SetMoveAnim, 0x6939F0, {.reversed = false});
    RH_ScopedInstall(ForceStopMove, 0x6924B0);
    RH_ScopedInstall(SetDuckTimer, 0x692530);
    
    RH_ScopedVMTInstall(Clone, 0x692CF0);
    RH_ScopedVMTInstall(GetTaskType, 0x692020);
    RH_ScopedVMTInstall(MakeAbortable, 0x692100);
    RH_ScopedVMTInstall(ProcessPed, 0x694390, {.reversed = false});
}

// 0x691FC0
CTaskSimpleDuck::CTaskSimpleDuck(eDuckControlType duckControlType, uint16 lengthOfDuck, int16 shotWhizzingCounter) :
    m_DuckControlType{duckControlType},
    m_LengthOfDuck{lengthOfDuck},
    m_ShotWhizzingCounter{shotWhizzingCounter},
    m_StartTime{CTimer::GetTimeInMS()}
{
    // Rest set in the header!
}

CTaskSimpleDuck::CTaskSimpleDuck(const CTaskSimpleDuck& o) :
    CTaskSimpleDuck{o.m_DuckControlType, o.m_LengthOfDuck, o.m_ShotWhizzingCounter}
{
}

// 0x692030
CTaskSimpleDuck::~CTaskSimpleDuck() {
    if (m_DuckAnim) {
        m_DuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
        if (m_DuckAnim->m_fBlendAmount > 0.f && m_DuckAnim->m_fBlendDelta >= 0.f && (m_DuckAnim->m_nFlags & ANIMATION_PARTIAL)) {
            m_DuckAnim->m_fBlendDelta = -8.f;
        }
    }

    if (m_MoveAnim) {
        m_MoveAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
        if (m_MoveAnim->m_fBlendAmount > 0.f && m_MoveAnim->m_fBlendDelta >= 0.f) {
            m_MoveAnim->m_fBlendDelta = -8.f;
        }
    }
}

// 0x692550
void CTaskSimpleDuck::DeleteDuckAnimCB(CAnimBlendAssociation* assoc, void* data) {
    const auto self = static_cast<CTaskSimpleDuck*>(data); // aka `this`
    if (!self) {
        return;
    }

    if (!assoc) {
        return;
    }

    switch (assoc->m_nAnimId) {
    case ANIM_ID_WEAPON_CROUCH:
    case ANIM_ID_DUCK_COWER: {
        if (!self->m_MoveAnim || !self->m_bIsAborting) {
            self->m_bIsFinished = true;
        }
        self->m_MoveAnim = nullptr; // Moved below `if`
        break;
    }
    case ANIM_ID_CROUCH_ROLL_L:
    case ANIM_ID_CROUCH_ROLL_R: {
        self->m_MoveCmd.x = 0.0;
        [[fallthrough]];
    }
    case ANIM_ID_GUNCROUCHFWD:
    case ANIM_ID_GUNCROUCHBWD: {
        if (self->m_bIsAborting) {
            self->m_bIsFinished = 1;
        }
        self->m_MoveAnim = nullptr; // Moved below `if`
        break;
    }
    }
}

// 0x692610
bool CTaskSimpleDuck::CanPedDuck(CPed* ped) {
    if (ped->IsPlayer()) {
        switch (ped->m_nMoveState) {
        case PEDMOVE_RUN:
        case PEDMOVE_SPRINT:
            return false;
        }
    }

    const auto& activeWep = ped->GetActiveWeapon();
    const auto& pedActiveWepWI = activeWep.GetWeaponInfo(ped);

    switch (pedActiveWepWI.m_nWeaponFire) {
    case eWeaponFire::WEAPON_FIRE_MELEE:
    case eWeaponFire::WEAPON_FIRE_USE:
        return true;
    }

    if (activeWep.GetType() == WEAPON_SPRAYCAN) {
        return true;
    }

    if (pedActiveWepWI.flags.bCrouchFire) {
        return true;
    }

    return false;
}

// 0x61C3D0
bool CTaskSimpleDuck::IsTaskInUseByOtherTasks() const {
    if (m_MoveCmd.IsZero()) {
        if (m_DuckAnim) {
            if (m_DuckAnim->m_fBlendAmount >= 1.f && !m_bIsAborting && m_ShotWhizzingCounter <= 0) {
                return false;
            }
        }
    }
    return true;
}

// 0x692340
void CTaskSimpleDuck::AbortBecauseOfOtherDuck(CPed* ped) {
    if (m_DuckAnim) {
        m_DuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
        m_DuckAnim = nullptr;
    }

    if (m_MoveAnim) {
        m_MoveAnim->m_fBlendDelta = -8.0;
        m_DuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
        m_MoveAnim = nullptr;
    }

    m_bNeedToSetDuckFlag = true;
    m_bIsFinished = true;
}

// 0x692390
void CTaskSimpleDuck::RestartTask(CPed* ped) {
    if (m_bNeedToSetDuckFlag) {
        ped->bIsDucking = true;
        m_bNeedToSetDuckFlag = false;
    }

    if (m_ShotWhizzingCounter >= 0) {
        m_ShotWhizzingCounter = CGeneral::GetRandomNumberInRange(1000, 2500);
    }
}

// 0x6923F0
// @arg moveDir The desired move direction. The `y` axis being fwd/bwd, and `x` being left/right.
void CTaskSimpleDuck::ControlDuckMove(CVector2D moveDir) {
    m_bIsInControl = true;

    // If going full fwd/bwd ignore left/right commmands
    if (std::abs(m_MoveCmd.x) == 1.f) { // Originally checked if either -1 or 1 (this achieves the same thing)
        return;
    }

    // Change direction, but limit maximum change to `maxUnits`
    const auto maxUnits = CTimer::GetTimeStep() * 0.07f;
    const auto moveDeltaY = moveDir.y - m_MoveCmd.y; 
    if (moveDeltaY <= maxUnits) {
        if (moveDeltaY >= -maxUnits) {
            m_MoveCmd.y = moveDir.y;
        } else {
            m_MoveCmd.y -= maxUnits;
        }
    } else {
        m_MoveCmd.y += maxUnits;
    }

    if (std::abs(moveDir.y) < 0.1f && std::abs(moveDir.x) >= 0.9f) {
        m_MoveCmd.y = 0.f;
        m_MoveCmd.x = moveDir.x <= 0.f ? -1.f : 1.f;
    }
}

// 0x6939F0
void CTaskSimpleDuck::SetMoveAnim(CPed* ped) {
    plugin::CallMethod<0x6939F0, CTaskSimpleDuck*, CPed*>(this, ped);
}

// 0x6924B0
void CTaskSimpleDuck::ForceStopMove() {
    m_bIsInControl = true;
    m_MoveCmd.y = 0.f;
}

// 0x692530
void CTaskSimpleDuck::SetDuckTimer(uint16 time) {
    if (m_DuckControlType != DUCK_SCRIPT_CONTROLLED) {
        m_LengthOfDuck = time;
    }
}

// 0x692100
bool CTaskSimpleDuck::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE: { // 0x69210C
        // Replace/blend duck anim with idle anim
        if (m_DuckAnim) {
            if (m_DuckAnim->m_nFlags & ANIMATION_PARTIAL) {
                m_DuckAnim->m_fBlendDelta = -1000.f;
            } else {
                CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 1000.f);
            }
            m_DuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
            m_DuckAnim = nullptr;
        }

        if (m_MoveAnim) {
            m_MoveAnim->m_fBlendDelta = -1000.f;
            m_MoveAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
            m_MoveAnim = nullptr;
        }
        ped->bIsDucking = false;
        m_bNeedToSetDuckFlag = 1;
        return true;
    }
    case ABORT_PRIORITY_URGENT: { // 0x69219B
        if (m_ShotWhizzingCounter >= 0) { // Originally > -1
            if (event) {
                if (event->GetEventType() == EVENT_SHOT_FIRED_WHIZZED_BY) {
                    if (static_cast<const CEventGunShotWhizzedBy*>(event)->m_taskId == TASK_SIMPLE_DUCK_WHILE_SHOTS_WHIZZING) {
                        if (event->GetSourceEntity()) {
                            ped->bIsDucking = false;
                            m_bNeedToSetDuckFlag = 1;
                            return true;
                        }
                    }
                }
            }
        }
        break;
    }
    }

    if (m_MoveAnim) { // 0x6921E5
        switch (m_MoveAnim->m_nAnimId) {
        case ANIM_ID_CROUCH_ROLL_L:
        case ANIM_ID_CROUCH_ROLL_R:
            return false;
        }
    }

    const auto blendDelta = (priority == ABORT_PRIORITY_URGENT) ? -8.f : -4.f;

    if (m_DuckAnim) {
        if (m_DuckAnim->m_fBlendAmount > 0.f && m_DuckAnim->m_fBlendDelta >= 0.f) {
            if (m_DuckAnim->m_nFlags & ANIMATION_PARTIAL) {
                m_DuckAnim->m_fBlendDelta = blendDelta;
            }
            CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, blendDelta);
            ped->m_nSwimmingMoveState = eMoveState::PEDMOVE_STILL;
        }

        if (priority == ABORT_PRIORITY_URGENT) {
            m_DuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
            m_DuckAnim = nullptr;
        }
    }

    if (m_MoveAnim) {
        if (m_MoveAnim->m_fBlendAmount > 0.f && m_MoveAnim->m_fBlendDelta >= 0.f) {
            switch (m_MoveAnim->m_nAnimId) {
            default: {
                if (priority != ABORT_PRIORITY_URGENT) {
                    break;
                }
                [[fallthrough]];
            }
            case ANIM_ID_GUNCROUCHFWD:
            case ANIM_ID_GUNCROUCHBWD:
                m_MoveAnim->m_fBlendDelta = blendDelta;
                m_MoveAnim->m_nFlags &= ANIMATION_STARTED;
            }
                
        }

        if (priority == ABORT_PRIORITY_URGENT) {
            m_MoveAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
            m_MoveAnim = nullptr;
        }
    }

    if (const auto tUseGun = ped->GetIntelligence()->GetTaskUseGun()) {
        tUseGun->ClearAnim(ped);
    }

    if (priority == ABORT_PRIORITY_URGENT) {
        m_bIsFinished = true;
        ped->bIsDucking = false;
        m_bNeedToSetDuckFlag = true;
        return true;
    }

    m_bIsAborting = true;

    return false;
}

// 0x694390
bool CTaskSimpleDuck::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x694390, CTaskSimpleDuck*, CPed*>(this, ped);
}
