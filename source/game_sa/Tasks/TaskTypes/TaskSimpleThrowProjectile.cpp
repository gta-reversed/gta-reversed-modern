#include "StdInc.h"

#include "TaskSimpleThrowProjectile.h"

// 0x61F660
CTaskSimpleThrowProjectile::CTaskSimpleThrowProjectile(CEntity* target, CVector posn) : CTaskSimple() {
    plugin::CallMethod<0x61F660, CTaskSimpleThrowProjectile*, CEntity*, CVector>(this, target, posn);
}

CTaskSimpleThrowProjectile::~CTaskSimpleThrowProjectile() {
    if (m_pAnim) {
        m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        m_pAnim = nullptr;
    }
    CEntity::SafeCleanUpRef(m_pTarget);
}


// 0x61F810
bool CTaskSimpleThrowProjectile::ControlThrow(bool bUpdateStartTime, CEntity* entity, CVector* entity2) {
    return plugin::CallMethodAndReturn<bool, 0x61F810, CTaskSimpleThrowProjectile*, bool, CEntity*, CVector*>(this, bUpdateStartTime, entity, entity2);
}

// 0x61F780
bool CTaskSimpleThrowProjectile::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x61F780, CTaskSimpleThrowProjectile*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);

    // untested
    if (priority == ABORT_PRIORITY_URGENT) {
        if (m_pAnim) {
            m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_pAnim->m_fBlendDelta = -1000.0f;
            m_pAnim = nullptr;
            return true;
        }
    } else if (event && event->GetEventType() == EVENT_DAMAGE) {
        const auto* eventDamage = static_cast<const CEventDamage*>(event);
        if (eventDamage->m_damageResponse.m_bHealthZero && eventDamage->m_bAddToEventGroup || eventDamage->m_bFallDown) {
            if (m_pAnim) {
                m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
                m_pAnim->m_fBlendDelta = -4.0f;
                m_pAnim = nullptr;
            }
            m_bIsAborting = true;
        }
    }
    return true;
}

// 0x62AF50
bool CTaskSimpleThrowProjectile::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x62AF50, CTaskSimpleThrowProjectile*, CPed*>(this, ped);
}

void CTaskSimpleThrowProjectile::InjectHooks() {
    RH_ScopedClass(CTaskSimpleThrowProjectile);
    RH_ScopedCategory("Tasks/TaskTypes");
    using namespace ReversibleHooks;
}

// 0x61F660
CTaskSimpleThrowProjectile* CTaskSimpleThrowProjectile::Constructor(CEntity* pTarget, CVector Posn) {
    return plugin::CallMethodAndReturn<CTaskSimpleThrowProjectile*, 0x61F660, CTaskSimpleThrowProjectile*, CEntity*, CVector>(this, pTarget, Posn);
}
