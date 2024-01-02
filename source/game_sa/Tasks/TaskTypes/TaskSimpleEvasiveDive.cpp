#include "StdInc.h"

#include "TaskSimpleEvasiveDive.h"

// 0x653560
CTaskSimpleEvasiveDive::CTaskSimpleEvasiveDive(CVehicle* vehicle) : CTaskSimple() {
    m_Vehicle = vehicle;
    m_bFinished = false;
    m_Assoc = nullptr;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x6535D0
CTaskSimpleEvasiveDive::~CTaskSimpleEvasiveDive() {
    CEntity::SafeCleanUpRef(m_Vehicle);
    if (m_Assoc) {
        m_Assoc->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x653640
bool CTaskSimpleEvasiveDive::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x653640, CTaskSimpleEvasiveDive*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

// 0x657AC0
bool CTaskSimpleEvasiveDive::ProcessPed(CPed* ped) {
    if (m_bFinished) {
        return true;
    }
    if (!m_Assoc) {
        StartAnim(ped);
    }
    return false;
}

// 0x655F20
void CTaskSimpleEvasiveDive::StartAnim(CPed* ped) {
    ped->Say(74u);
    m_Assoc = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_EV_DIVE, 8.0f);
    m_Assoc->SetFinishCallback(FinishAnimEvasiveDiveCB, this);
    if (!m_Vehicle || ped->m_nPedType != PED_TYPE_COP)
        return;

    if (m_Vehicle->m_pDriver && m_Vehicle->m_pDriver->IsPlayer()) {
        const auto& pedPos = ped->GetPosition();
        auto wanted = FindPlayerWanted();
        wanted->RegisterCrime_Immediately(CRIME_VEHICLE_DAMAGE, pedPos, ped, 0);
        wanted->RegisterCrime_Immediately(CRIME_TYPE_9, pedPos, ped, 0);
    }
}

// 0x6536A0
void CTaskSimpleEvasiveDive::FinishAnimEvasiveDiveCB(CAnimBlendAssociation* assoc, void* data) {
    static_cast<CTaskSimpleEvasiveDive*>(data)->m_bFinished = true;
    static_cast<CTaskSimpleEvasiveDive*>(data)->m_Assoc = nullptr;
}
