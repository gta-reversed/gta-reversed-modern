#include "StdInc.h"
#include "TaskSimpleBeHit.h"
#include "TaskSimpleFight.h"

void CTaskSimpleBeHit::InjectHooks() {
    RH_ScopedClass(CTaskSimpleBeHit);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x620780);
    RH_ScopedInstall(Destructor, 0x620810);

    RH_ScopedGlobalInstall(FinishAnimBeHitCB, 0x620900);

    RH_ScopedInstall(StartAnim, 0x620910);

    RH_ScopedVirtualInstall2(Clone, 0x623290);
    RH_ScopedVirtualInstall2(GetTaskType, 0x620800);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x620890);
    RH_ScopedVirtualInstall2(ProcessPed, 0x620A20);
}

/*!
* @addr 0x620780
* @param [opt] attacker  The ped that hit us 
* @param       pieceType The piece we got hit at
* @param       dmgArmor  
* @param       dmgHealth The amount of damage to our health
*/
CTaskSimpleBeHit::CTaskSimpleBeHit(CPed* attacker, ePedPieceTypes pieceType, int32 dmgArmor, int32 dmgHealth) :
    m_attacker{attacker},
    m_dmgArmor{dmgArmor},
    m_dmgHealth{dmgHealth},
    m_pedPiece{pieceType}
{
    CEntity::SafeRegisterRef(attacker);
}

// NOTSA
CTaskSimpleBeHit::CTaskSimpleBeHit(const CTaskSimpleBeHit& o) :
    CTaskSimpleBeHit{ o.m_attacker, o.m_pedPiece, o.m_dmgArmor, o.m_dmgHealth }
{
    m_hasBlendedAnim = m_hasBlendedAnim;
    m_animId     = m_animId;
    m_nAnimGroup = m_nAnimGroup;
}

/*!
* @addr 0x620810
*/
CTaskSimpleBeHit::~CTaskSimpleBeHit() {}

/*!
* @addr 0x620900
* @brief The finish callback of `m_anim`
*/
void CTaskSimpleBeHit::FinishAnimBeHitCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = static_cast<CTaskSimpleBeHit*>(data);
    self->m_anim = nullptr;
    self->m_finishedOrAborted = true;
}

/*!
* @addr 0x620910
* @brief Start the animation / handle check if it's still running. If not `m_finishedOrAborted` is set.
* 
* @param ped The ped to who this task belongs to
*/
void CTaskSimpleBeHit::StartAnim(CPed* ped) {
    // If no animId is set yet, calculate it
    if (m_animId == ANIM_ID_NO_ANIMATION_SET) {
        std::tie(m_nAnimGroup, m_animId) = [this]() -> std::tuple<AssocGroupId, AnimationId> {
            if (!m_dmgArmor && m_attacker) {
                const auto fighting = m_attacker->GetIntelligence()->GetTaskFighting();
                if (fighting && fighting->m_nComboSet >= 4 && fighting->m_nCurrentMove <= 2) {
                    return {
                        (AssocGroupId)fighting->m_aComboData[fighting->m_nComboSet - 4].m_nAnimGroup,
                        (AnimationId)(fighting->m_nCurrentMove + (int)ANIM_ID_FIGHT_HIT_1),
                    };
                }
            }

            return {
                m_nAnimGroup,
                [this] {
                    if (m_pedPiece == PED_PIECE_TORSO) {
                         return ANIM_ID_HIT_FRONT;
                    }

                    switch (m_dmgArmor) {
                    case 1:
                        return ANIM_ID_HIT_L;
                    case 2:
                        return ANIM_ID_HIT_BACK;
                    case 3:
                        return ANIM_ID_HIT_R;
                    default:
                        return m_dmgArmor <= 5 ? ANIM_ID_HIT_FRONT : ANIM_ID_HIT_WALK;
                    }
                }()
            };
        }();
    }

    // Check if anim exists/create it
    if (m_hasBlendedAnim) { // Inverted
        m_anim = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_animId);
        if (!m_anim) {
            m_finishedOrAborted = true;
            return;
        }
    } else {
        m_anim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_nAnimGroup, m_animId, 8.f);
        m_anim->SetCurrentTime(0.f);
        m_hasBlendedAnim = true;
    }
    m_anim->SetFinishCallback(FinishAnimBeHitCB, this);
}

/*!
* @addr 0x620890
* @brief Try aborting the task
* 
* @param       ped      The ped to who this task belongs to
* @param       priority The abort priority
* @param [opt] event    The event that caused the abortion
* 
* @return If it was aborted
*/
bool CTaskSimpleBeHit::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    switch (priority) {
    case ABORT_PRIORITY_LEISURE: {
        if (m_anim) {
            if (!(m_anim->m_nFlags & ANIMATION_STARTED)) {
                m_anim->m_nFlags |= ANIMATION_FREEZE_LAST_FRAME;
                m_anim->m_fBlendDelta = -4.f;
            }
        }
        return false;
    }
    case ABORT_PRIORITY_URGENT:
    case ABORT_PRIORITY_IMMEDIATE: {
        if (event && event->GetEventPriority() < 62) {
            return false;
        }

        if (m_anim) {
            m_anim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_anim = nullptr;
        }

        m_finishedOrAborted = true;

        return true;
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

/*!
* @addr 0x620A20
* @brief Process the ped
* 
* @param ped The ped to who this task belongs to
*/
bool CTaskSimpleBeHit::ProcessPed(CPed* ped) {
    if (m_finishedOrAborted) {
        return true;
    }

    if (!m_dmgArmor && m_attacker && !m_attacker->IsPlayer()) {
        // TODO: Add a function for this to CVector/CVector2D
        const auto dir = m_attacker->GetPosition() - ped->GetPosition();
        ped->m_fAimingRotation = std::atan2(-dir.x, dir.y);
    }

    if (!m_anim) {
        const auto ResetAndSay = [ped] {
            ped->DisablePedSpeech(true);
            ped->EnablePedSpeech();
            return ped->Say(16, 1000) >= 0;
        };
        if (!m_attacker || !m_attacker->IsPlayer() || m_attacker->m_nPedType == PED_TYPE_GANG2 || !ResetAndSay()) {
            ped->Say(345);
        }
        StartAnim(ped);
    }

    return false;
}
