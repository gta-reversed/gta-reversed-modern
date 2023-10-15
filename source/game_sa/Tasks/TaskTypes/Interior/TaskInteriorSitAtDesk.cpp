#include "StdInc.h"

#include "TaskInteriorSitAtDesk.h"

#include "Interior/InteriorManager_c.h"

void CTaskInteriorSitAtDesk::InjectHooks() {
    RH_ScopedVirtualClass(CTaskInteriorSitAtDesk, 0x87035c, 9);
    RH_ScopedCategory("Tasks/TaskTypes/Interior");

    RH_ScopedInstall(Constructor, 0x676010);
    RH_ScopedInstall(Destructor, 0x676080);

    RH_ScopedInstall(FinishAnimCB, 0x676190);
    RH_ScopedInstall(StartRandomLoopAnim, 0x677780);
    RH_ScopedInstall(StartRandomOneOffAnim, 0x677880);

    RH_ScopedVMTInstall(Clone, 0x6760E0);
    RH_ScopedVMTInstall(GetTaskType, 0x676070);
    RH_ScopedVMTInstall(MakeAbortable, 0x676150);
    RH_ScopedVMTInstall(ProcessPed, 0x677920, { .reversed = false });
}

// 0x676010
CTaskInteriorSitAtDesk::CTaskInteriorSitAtDesk(int32 duration, InteriorInfo_t* interiorInfo, bool bDoInstantly) :
    m_Duration{ duration },
    m_InteriorInfo{ interiorInfo },
    m_bDoInstantly{ bDoInstantly }
{    
}

// 0x6760E0
CTaskInteriorSitAtDesk::CTaskInteriorSitAtDesk(const CTaskInteriorSitAtDesk& o) :
    CTaskInteriorSitAtDesk{ o.m_Duration, o.m_InteriorInfo, m_bDoInstantly }
{
}

// 0x676080
CTaskInteriorSitAtDesk::~CTaskInteriorSitAtDesk() {
    if (m_Anim) {
        m_Anim->SetDefaultFinishCallback();
    }
}

// 0x676190
void CTaskInteriorSitAtDesk::FinishAnimCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = CTask::Cast<CTaskInteriorSitAtDesk>(static_cast<CTask*>(data));
    assert(self->m_Anim == anim);

    self->m_PrevAnimId = anim->GetId();
    if (anim->GetId() == ANIM_ID_OFF_SIT_2IDLE_180 || self->m_bTaskAborting && anim->GetId() == ANIM_ID_OFF_SIT_IN) {
        anim->SetBlendDelta(-1000.f);
        self->m_bTaskFinished = true;
    }
    self->m_Anim = nullptr;
}

// 0x677780
void CTaskInteriorSitAtDesk::StartRandomLoopAnim(CPed* ped, float blendDelta) {
    if (m_Anim) {
        m_Anim->SetDefaultFinishCallback();
    }

    const auto [animId, interval] = []() -> std::tuple<AnimationId, uint32> {
        using CGeneral::GetRandomNumberInRange;
        const auto chance = GetRandomNumberInRange(0, 100);
        if (chance > 40) {
            return { ANIM_ID_OFF_SIT_TYPE_LOOP, GetRandomNumberInRange<uint32>(7000, 12000) };
        }
        return { chance <= 10 ? ANIM_ID_OFF_SIT_BORED_LOOP : ANIM_ID_OFF_SIT_IDLE_LOOP, GetRandomNumberInRange<uint32>(2000, 5000) };
    }();
    m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_INT_OFFICE, animId, blendDelta);
    m_Anim->SetFinishCallback(FinishAnimCB, this);

    m_AnimTimer.Start(interval);
}

// 0x677880
void CTaskInteriorSitAtDesk::StartRandomOneOffAnim(CPed* ped) {
    if (m_Anim) {
        m_Anim->SetDefaultFinishCallback();
    }

    const auto animId = []{
        const auto chance = CGeneral::GetRandomNumberInRange(0, 100);
        if (chance > 60) {
            return ANIM_ID_OFF_SIT_READ;
        }
        if (chance > 35) {
            return ANIM_ID_OFF_SIT_DRINK;
        }
        if (chance > 10) {
            return ANIM_ID_OFF_SIT_WATCH;
        }
        return ANIM_ID_OFF_SIT_CRASH;
    }();
    m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_INT_OFFICE, animId, 4.f);
    m_Anim->SetFinishCallback(FinishAnimCB, this);
}

// 0x676150
bool CTaskInteriorSitAtDesk::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    if (priority == ABORT_PRIORITY_IMMEDIATE) {
        if (m_Anim) {
            m_Anim->SetBlendDelta(-1000.f);
            m_Anim->SetDefaultFinishCallback();
            m_Anim = nullptr;
        }
        return true;
    } else {
        m_bTaskAborting = true;
        return false;
    }
}

// 0x677920
bool CTaskInteriorSitAtDesk::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x677920, CTaskInteriorSitAtDesk*, CPed *>(this, ped);
    /* Code is so far good, but needs to be finished...
    const auto currAnimId = m_Anim
        ? (AnimationId)m_Anim->m_nAnimId
        : ANIM_ID_UNDEFINED;

    if (m_bTaskFinished && !RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_OFF_SIT_2IDLE_180)) {
        ped->m_fAimingRotation = ped->m_fCurrentRotation = CGeneral::LimitRadianAngle(ped->m_fCurrentRotation + PI);
        ped->SetHeading(ped->m_fCurrentRotation);
        return true;
    }

    if (m_bTaskAborting) {
        if (!InteriorManager_c::AreAnimsLoaded(2)) {
            return true;
        }
        switch (currAnimId) {
        case ANIM_ID_OFF_SIT_IN:
            m_Anim->SetBlendDelta(-8.f);
            break;
        case ANIM_ID_OFF_SIT_2IDLE_180:
            m_Anim->m_fSpeed = 2.f;
            break;
        case ANIM_ID_OFF_SIT_IDLE_LOOP:
        case ANIM_ID_OFF_SIT_TYPE_LOOP:
        case ANIM_ID_OFF_SIT_BORED_LOOP:
        case ANIM_ID_OFF_SIT_CRASH:
        case ANIM_ID_OFF_SIT_DRINK:
        case ANIM_ID_OFF_SIT_READ:
        case ANIM_ID_OFF_SIT_WATCH: {
            if (!m_bUpdatePedPos) {
                m_Anim->SetDefaultFinishCallback();
                m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_INT_OFFICE, ANIM_ID_OFF_SIT_2IDLE_180, 1000.f);
                m_Anim->SetFinishCallback(FinishAnimCB, this);
                m_bUpdatePedPos = true;
                return false;
            }
            break;
        }
        }
    }

    if (m_Anim) {
        if (!m_bUpdatePedPos) {
            // 0x677B3A - I don't have the will to do this dude, fuck this
        }
    }
    */
}
