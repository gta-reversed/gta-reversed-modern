#include "StdInc.h"

#include "TaskSimpleBikeJacked.h"
#include "TaskUtilityLineUpPedWithCar.h"

void CTaskSimpleBikeJacked::InjectHooks() {
    RH_ScopedClass(CTaskSimpleBikeJacked);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x648B90);
    RH_ScopedInstall(Destructor, 0x648C40);
    RH_ScopedGlobalInstall(FinishAnimBikeHitCB, 0x648D30);
    RH_ScopedVirtualInstall2(Clone, 0x64A200);
    RH_ScopedVirtualInstall2(GetTaskType, 0x648C30);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x648CE0);
    RH_ScopedVirtualInstall2(ProcessPed, 0x64C970);
    RH_ScopedVirtualInstall2(SetPedPosition, 0x648D00);
}

// 0x648B90
CTaskSimpleBikeJacked::CTaskSimpleBikeJacked(CVehicle* targetVehicle, int32 targetDoor, int32 downTime, CPed* draggingPed, bool bWasDriver) :
    CTaskSimple(),
    m_TargetVehicle{ targetVehicle },
    m_TargetDoor{ targetDoor },
    m_DownTime{ downTime },
    m_DraggingPed{ draggingPed },
    m_bWasDriver{ bWasDriver },
    m_bIsFinished{ false },
    m_Anim{ nullptr },
    m_nFinishAnim{ ANIM_ID_NO_ANIMATION_SET },
    m_Utility{ nullptr }
{
    CEntity::SafeRegisterRef(m_TargetVehicle);
    CEntity::SafeRegisterRef(m_DraggingPed);
}

// 0x648C40
CTaskSimpleBikeJacked::~CTaskSimpleBikeJacked() {
    CEntity::SafeCleanUpRef(m_TargetVehicle);
    CEntity::SafeCleanUpRef(m_DraggingPed);
    delete m_Utility;
    if (m_Anim) {
        m_Anim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x648CE0
bool CTaskSimpleBikeJacked::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE: {
        if (m_Anim) {
            m_Anim->m_fBlendDelta = -1000.f;
        }
        return true;
    }
    default:
        return false;
    }
}

// 0x648D30
void CTaskSimpleBikeJacked::FinishAnimBikeHitCB(CAnimBlendAssociation* anim, void* data) {
    auto self = static_cast<CTaskSimpleBikeJacked*>(data);
    self->m_Anim = nullptr;
    self->m_bIsFinished = true;
    self->m_nFinishAnim = [&self] {
        switch (self->m_TargetDoor) {
        case 8:
        case 10:
            return ANIM_ID_BIKE_FALL_OFF;
        default:
            return ANIM_ID_BIKE_FALLR;
        }
    }();
}

// 0x64C970
bool CTaskSimpleBikeJacked::ProcessPed(CPed* ped) {
    if (!m_TargetVehicle) {
        return true;
    }

    if (!ped->bInVehicle && !m_Anim) {
        return true;
    }

    if (!m_bIsFinished) {
        if (!ped->IsPlayer() && m_TargetVehicle->IsDriver(ped)) {
            ped->SetRadioStation();
        }
        if (ped->IsPlayer()) {
            m_TargetVehicle->m_vehicleAudio.PlayerAboutToExitVehicleAsDriver();
        }

        const auto FinishProcess = [&]() {
            if (!m_Utility) {
                m_Utility = new CTaskUtilityLineUpPedWithCar({}, 0, 0, m_TargetDoor);
            }
            return false;
        };

        if (m_Anim)
            return FinishProcess();

        CAnimBlendAssociation* assoc = nullptr;
        if (m_DraggingPed) {
            for (const auto& anim : { ANIM_ID_CAR_PULLOUT_RHS, ANIM_ID_CAR_PULLOUT_LHS, ANIM_ID_CAR_GETIN_BIKE_FRONT }) {
                assoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, anim);
                if (assoc) {
                    break;
                }
            }
        }

        if (m_DraggingPed) {
            if (assoc && assoc->m_fCurrentTime <= 0.3f) {
                return FinishProcess();
            }

            if (CGeneral::DoCoinFlip()) { // Originally: rand() % 1024 <= 512
                if (!SayJacking(m_DraggingPed, ped, m_TargetVehicle)) {
                    SayJacked(ped, m_TargetVehicle);
                }
            } else if (!SayJacked(ped, m_TargetVehicle)) {
                SayJacking(m_DraggingPed, ped, m_TargetVehicle);
            }
        }

        // Play animation and some sound effect
        m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_TargetVehicle->GetRideAnimData()->m_nAnimGroup, ANIM_ID_BIKE_HIT);
        m_Anim->SetFinishCallback(FinishAnimBikeHitCB, this);
        ped->m_pedAudio.AddAudioEvent(AE_PED_JACKED_BIKE);

        return FinishProcess();
    }

    if (m_nFinishAnim == ANIM_ID_NO_ANIMATION_SET) {
        return true;
    }

    CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, m_nFinishAnim, 100.0f);

    CEventKnockOffBike event(
        m_TargetVehicle,
        &m_TargetVehicle->GetMoveSpeed(),
        &m_TargetVehicle->m_vecLastCollisionImpactVelocity,
        0.0f, 0.0f, 55u, 0u,
        m_DownTime, m_DraggingPed,
        m_bWasDriver, true
    );
    ped->GetEventGroup().Add(event, true);

    m_nFinishAnim = ANIM_ID_NO_ANIMATION_SET;

    return false;
}

// 0x648D00
bool CTaskSimpleBikeJacked::SetPedPosition(CPed* ped) {
    if (ped->IsInVehicle()) {
        ped->SetPedPositionInCar();
    }
    return true;
}
