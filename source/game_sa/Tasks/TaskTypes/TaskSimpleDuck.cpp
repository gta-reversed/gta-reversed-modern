#include "StdInc.h"
#include "TaskSimpleDuck.h"
#include "AnimBlendAssociation.h"

void CTaskSimpleDuck::InjectHooks() {
    RH_ScopedClass(CTaskSimpleDuck);
    RH_ScopedCategory(); // TODO: Change this to the appropriate category!

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
    // RH_ScopedInstall(GetTaskType_Reversed, 0x692020);
    // RH_ScopedInstall(MakeAbortable_Reversed, 0x692100);
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
void CTaskSimpleDuck::ControlDuckMove(CVector2D moveSpeed) {
    m_bIsInControl = true;

    if (std::abs(m_vecMoveCommand.x) == 1.f) { // Originally checked if either -1 or 1 (this achieves the same thing)
        return;
    }

    const auto timerStep = CTimer::GetTimeStep() * 0.07f;
    if (const auto moveDeltaY = moveSpeed.y - m_vecMoveCommand.y; moveDeltaY <= timerStep) {
        if (moveDeltaY >= -timerStep) {
            m_vecMoveCommand.y = moveSpeed.y;
        } else {
            m_vecMoveCommand.y -= moveSpeed.y;
        }
    } else {
        m_vecMoveCommand.y += moveSpeed.y;
    }

    if (std::abs(m_vecMoveCommand.y) < 0.1f && std::abs(m_vecMoveCommand.y) >= 0.9f) {
        m_vecMoveCommand.y = 0.f;
        m_vecMoveCommand.x = m_vecMoveCommand.x <= 0.f ? -1.f : 1.f;
    }
}

// 0x6939F0
void CTaskSimpleDuck::SetMoveAnim(CPed* ped) {
    plugin::CallMethod<0x6939F0, CTaskSimpleDuck*, CPed*>(this, ped);
}

// 0x692100
bool CTaskSimpleDuck::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x692100, CTaskSimpleDuck*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x694390
bool CTaskSimpleDuck::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x694390, CTaskSimpleDuck*, CPed*>(this, ped);
}
