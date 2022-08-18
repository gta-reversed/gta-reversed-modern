#include "StdInc.h"
#include "TaskSimpleBeKickedOnGround.h"

void CTaskSimpleBeKickedOnGround::InjectHooks() {
    RH_ScopedClass(CTaskSimpleBeKickedOnGround);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x61FC20);
    RH_ScopedInstall(Destructor, 0x61FC50);

    RH_ScopedInstall(StartAnim, 0x61FD20);
    RH_ScopedGlobalInstall(FinishAnimBeKickedOnGroundCB, 0x61FD10);

    RH_ScopedVirtualInstall2(Clone, 0x623120);
    RH_ScopedVirtualInstall2(GetTaskType, 0x61FC40);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x61FCC0);
    RH_ScopedVirtualInstall2(ProcessPed, 0x61FE00);
}

// 0x61FC20
CTaskSimpleBeKickedOnGround::CTaskSimpleBeKickedOnGround() {
    /* Done in header */

    assert(false); // Pirulax: This task doesn't seem to be constructed anywhere, LMK if it was.
}

// 0x61FC50
CTaskSimpleBeKickedOnGround::~CTaskSimpleBeKickedOnGround() {
    if (m_anim) {
        m_anim->m_fBlendDelta = -4.f;
        m_anim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x61FD10
void CTaskSimpleBeKickedOnGround::FinishAnimBeKickedOnGroundCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = static_cast<CTaskSimpleBeKickedOnGround*>(data);
    self->m_anim = nullptr;
    self->m_animHasFinished = true;
}

// 0x61FD20
void CTaskSimpleBeKickedOnGround::StartAnim(CPed* ped) {
    if (CLocalisation::KickingWhenDown()) {
        m_anim = CAnimManager::BlendAnimation(
            ped->m_pRwClump,
            ANIM_GROUP_DEFAULT,
            RpAnimBlendClumpGetFirstAssociation(ped->m_pRwClump, ANIMATION_800) ? ANIM_ID_FLOOR_HIT_F : ANIM_ID_FLOOR_HIT,
            8.f
        );
        m_anim->Start();
        m_anim->m_nFlags &= ~ANIMATION_UNLOCK_LAST_FRAME;

        /*
        * Code below is dead,it gets a bone's position, and does nothing with it.
        if (CLocalisation::KickingWhenDown()) { // TODO: Inlined?
            // Dead code 
        }
        */

        m_anim->SetFinishCallback(FinishAnimBeKickedOnGroundCB, this);
    } else {
        m_animHasFinished = true;
    }
}

// 0x61FCC0
bool CTaskSimpleBeKickedOnGround::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    switch (priority) {
    case ABORT_PRIORITY_URGENT:
    case ABORT_PRIORITY_IMMEDIATE: {
        if (m_anim) {
            m_anim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_anim = nullptr;
        }
        return true;
    }
    case ABORT_PRIORITY_LEISURE: {
        if (m_anim) {
            m_anim->m_nFlags |= ANIMATION_FREEZE_LAST_FRAME;
            m_anim->m_fBlendDelta = -4.f;
        }
        return false;
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x61FE00
bool CTaskSimpleBeKickedOnGround::ProcessPed(CPed* ped) {
    if (!m_animHasFinished) {
        return true;
    }
    if (!m_anim) {
        StartAnim(ped);
    }
    return false;
}
