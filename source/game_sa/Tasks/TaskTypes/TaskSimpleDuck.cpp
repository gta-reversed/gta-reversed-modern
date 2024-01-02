#include "StdInc.h"
#include "TaskSimpleDuck.h"
#include "AnimBlendAssociation.h"
#include "TaskSimpleUseGun.h"

void CTaskSimpleDuck::InjectHooks() {
    RH_ScopedClass(CTaskSimpleDuck);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x691FC0);
    RH_ScopedInstall(Destructor, 0x692030);

    RH_ScopedGlobalInstall(DeleteDuckAnimCB, 0x692550);
    RH_ScopedGlobalInstall(CanPedDuck, 0x692610);

    RH_ScopedInstall(IsTaskInUseByOtherTasks, 0x61C3D0);
    RH_ScopedInstall(AbortBecauseOfOtherDuck, 0x692340);
    RH_ScopedInstall(RestartTask, 0x692390);
    RH_ScopedInstall(ControlDuckMove, 0x6923F0);
    // RH_ScopedInstall(SetMoveAnim, 0x6939F0);

    RH_ScopedInstall(Clone_Reversed, 0x692CF0);
    RH_ScopedInstall(GetTaskType_Reversed, 0x692020);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x692100);
    // RH_ScopedInstall(ProcessPed_Reversed, 0x694390);
}

// 0x691FC0
CTaskSimpleDuck::CTaskSimpleDuck(eDuckControlType duckControlType, uint16 lengthOfDuck, int16 shotWhizzingCounter) :
    m_nDuckControlType{duckControlType},
    m_nLengthOfDuck{lengthOfDuck},
    m_nShotWhizzingCounter{shotWhizzingCounter},
    m_nStartTime{CTimer::GetTimeInMS()}
{
    // Rest set in the header!
}

CTaskSimpleDuck::CTaskSimpleDuck(const CTaskSimpleDuck& o) :
    CTaskSimpleDuck{o.m_nDuckControlType, o.m_nLengthOfDuck, o.m_nShotWhizzingCounter}
{
}

// 0x692030
CTaskSimpleDuck::~CTaskSimpleDuck() {
    if (m_pDuckAnim) {
        m_pDuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
        if (m_pDuckAnim->m_fBlendAmount > 0.f && m_pDuckAnim->m_fBlendDelta >= 0.f && (m_pDuckAnim->m_nFlags & ANIM_FLAG_PARTIAL)) {
            m_pDuckAnim->m_fBlendDelta = -8.f;
        }
    }

    if (m_pMoveAnim) {
        m_pMoveAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
        if (m_pMoveAnim->m_fBlendAmount > 0.f && m_pMoveAnim->m_fBlendDelta >= 0.f) {
            m_pMoveAnim->m_fBlendDelta = -8.f;
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
        if (!self->m_pMoveAnim || !self->m_bIsAborting) {
            self->m_bIsFinished = true;
        }
        self->m_pMoveAnim = nullptr; // Moved below `if`
        break;
    }
    case ANIM_ID_CROUCH_ROLL_L:
    case ANIM_ID_CROUCH_ROLL_R: {
        self->m_vecMoveCommand.x = 0.0;
        [[fallthrough]];
    }
    case ANIM_ID_GUNCROUCHFWD:
    case ANIM_ID_GUNCROUCHBWD: {
        if (self->m_bIsAborting) {
            self->m_bIsFinished = 1;
        }
        self->m_pMoveAnim = nullptr; // Moved below `if`
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
    const auto& pedActiveWepInf = activeWep.GetWeaponInfo(ped);

    switch (pedActiveWepInf.m_nWeaponFire) {
    case eWeaponFire::WEAPON_FIRE_MELEE:
    case eWeaponFire::WEAPON_FIRE_USE:
        return true;
    }

    if (activeWep.m_nType == WEAPON_SPRAYCAN) {
        return true;
    }

    if (pedActiveWepInf.flags.bCrouchFire) {
        return true;
    }

    return false;
}

// 0x61C3D0
bool CTaskSimpleDuck::IsTaskInUseByOtherTasks() {
    if (m_vecMoveCommand.IsZero()) {
        if (m_pDuckAnim) {
            if (m_pDuckAnim->m_fBlendAmount >= 1.f && !m_bIsAborting && m_nShotWhizzingCounter <= 0) {
                return false;
            }
        }
    }
    return true;
}

// 0x692340
void CTaskSimpleDuck::AbortBecauseOfOtherDuck(CPed* ped) {
    if (m_pDuckAnim) {
        m_pDuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
        m_pDuckAnim = nullptr;
    }

    if (m_pMoveAnim) {
        m_pMoveAnim->m_fBlendDelta = -8.0;
        m_pDuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
        m_pMoveAnim = nullptr;
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

    if (m_nShotWhizzingCounter >= 0) {
        m_nShotWhizzingCounter = CGeneral::GetRandomNumberInRange(1000, 2500);
    }
}

// 0x6923F0
// `CVector2D` the desired move dir. The `y` axis being fwd/bwd, and `x` being left/right.
void CTaskSimpleDuck::ControlDuckMove(CVector2D moveDir) {
    m_bIsInControl = true;

    // If going full fwd/bwd ignore left/right commmands
    if (std::abs(m_vecMoveCommand.x) == 1.f) { // Originally checked if either -1 or 1 (this achieves the same thing)
        return;
    }

    // Change direction, but limit maximum change to `maxUnits`
    const auto maxUnits = CTimer::GetTimeStep() * 0.07f;
    const auto moveDeltaY = moveDir.y - m_vecMoveCommand.y; 
    if (moveDeltaY <= maxUnits) {
        if (moveDeltaY >= -maxUnits) {
            m_vecMoveCommand.y = moveDir.y;
        } else {
            m_vecMoveCommand.y -= maxUnits;
        }
    } else {
        m_vecMoveCommand.y += maxUnits;
    }

    if (std::abs(moveDir.y) < 0.1f && std::abs(moveDir.x) >= 0.9f) {
        m_vecMoveCommand.y = 0.f;
        m_vecMoveCommand.x = moveDir.x <= 0.f ? -1.f : 1.f;
    }
}

// 0x6939F0
void CTaskSimpleDuck::SetMoveAnim(CPed* ped) {
    plugin::CallMethod<0x6939F0, CTaskSimpleDuck*, CPed*>(this, ped);
}

// 0x692100
bool CTaskSimpleDuck::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE: { // 0x69210C
        // Replace/blend duck anim with idle anim
        if (m_pDuckAnim) {
            if (m_pDuckAnim->m_nFlags & ANIM_FLAG_PARTIAL) {
                m_pDuckAnim->m_fBlendDelta = -1000.f;
            } else {
                CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 1000.f);
            }
            m_pDuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
            m_pDuckAnim = nullptr;
        }

        if (m_pMoveAnim) {
            m_pMoveAnim->m_fBlendDelta = -1000.f;
            m_pMoveAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
            m_pMoveAnim = nullptr;
        }
        ped->bIsDucking = false;
        m_bNeedToSetDuckFlag = 1;
        return true;
    }
    case ABORT_PRIORITY_URGENT: { // 0x69219B
        if (m_nShotWhizzingCounter >= 0) { // Originally > -1
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

    if (m_pMoveAnim) { // 0x6921E5
        switch (m_pMoveAnim->m_nAnimId) {
        case ANIM_ID_CROUCH_ROLL_L:
        case ANIM_ID_CROUCH_ROLL_R:
            return false;
        }
    }

    const auto blendDelta = (priority == ABORT_PRIORITY_URGENT) ? -8.f : -4.f;

    if (m_pDuckAnim) {
        if (m_pDuckAnim->m_fBlendAmount > 0.f && m_pDuckAnim->m_fBlendDelta >= 0.f) {
            if (m_pDuckAnim->m_nFlags & ANIM_FLAG_PARTIAL) {
                m_pDuckAnim->m_fBlendDelta = blendDelta;
            }
            CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, blendDelta);
            ped->m_nSwimmingMoveState = eMoveState::PEDMOVE_STILL;
        }

        if (priority == ABORT_PRIORITY_URGENT) {
            m_pDuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
            m_pDuckAnim = nullptr;
        }
    }

    if (m_pMoveAnim) {
        if (m_pMoveAnim->m_fBlendAmount > 0.f && m_pMoveAnim->m_fBlendDelta >= 0.f) {
            switch (m_pMoveAnim->m_nAnimId) {
            default: {
                if (priority != ABORT_PRIORITY_URGENT) {
                    break;
                }
                [[fallthrough]];
            }
            case ANIM_ID_GUNCROUCHFWD:
            case ANIM_ID_GUNCROUCHBWD:
                m_pMoveAnim->m_fBlendDelta = blendDelta;
                m_pMoveAnim->m_nFlags &= ANIM_FLAG_STARTED;
            }
                
        }

        if (priority == ABORT_PRIORITY_URGENT) {
            m_pMoveAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB);
            m_pMoveAnim = nullptr;
        }
    }

    if (const auto task = ped->GetIntelligence()->GetTaskUseGun()) {
        task->ClearAnim(ped);
    }

    if (priority == ABORT_PRIORITY_URGENT) {
        m_bIsFinished = true;
        ped->bIsDucking = false;
        m_bNeedToSetDuckFlag = 1;
        return true;
    }

    m_bIsAborting = true;

    return false;
}

// 0x694390
bool CTaskSimpleDuck::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x694390, CTaskSimpleDuck*, CPed*>(this, ped);
}
