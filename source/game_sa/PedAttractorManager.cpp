#include "StdInc.h"

#include "PedAttractorManager.h"

#include "PedAttractor.h"

#include "PedAtmAttractor.h"
#include "PedSeatAttractor.h"
#include "PedStopAttractor.h"
#include "PedPizzaAttractor.h"
#include "PedShelterAttractor.h"
#include "PedTriggerScriptAttractor.h"
#include "PedLookAtAttractor.h"
#include "PedScriptedAttractor.h"
#include "PedParkAttractor.h"
#include "PedStepAttractor.h"

void CPedAttractorManager::InjectHooks() {
    RH_ScopedClass(CPedAttractorManager);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(RestoreStuffFromMem, 0x5EF710);
    RH_ScopedOverloadedInstall(BroadcastArrival, "Internal", 0x5EF920, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*, SArray<CPedAttractor*>&));
    RH_ScopedOverloadedInstall(BroadcastArrival, "", 0x5EFE20, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*));
    RH_ScopedOverloadedInstall(BroadcastDeparture, "Internal", 0x5EC660, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*, SArray<CPedAttractor*>&));
    RH_ScopedOverloadedInstall(BroadcastDeparture, "", 0x5EC980, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*));
    RH_ScopedOverloadedInstall(DeRegisterPed, "Internal", 0x5EC740, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*, SArray<CPedAttractor*>&));
    RH_ScopedOverloadedInstall(DeRegisterPed, "", 0x5EC850, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*));
    RH_ScopedOverloadedInstall(RemoveEffect, "Internal", 0x5EB5F0, bool(CPedAttractorManager::*)(const C2dEffect* fx, const SArray<CPedAttractor*>& attractors));
    RH_ScopedOverloadedInstall(RemoveEffect, "", 0x5EBA30, bool(CPedAttractorManager::*)(const C2dEffect* fx));
    RH_ScopedInstall(IsPedRegistered, 0x5EB640);
    RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "Ped", 0x5EBCB0, bool(CPedAttractorManager::*)(CPed*));
    RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "Effect", 0x5EBD70, bool(CPedAttractorManager::*)(CPed*, const C2dEffect*, const CEntity*));
    // RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "Internal", 0x5EB690, bool(CPedAttractorManager::*)(CPed*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&));
    RH_ScopedInstall(FindAssociatedAttractor, 0x5EB6F0, { .reversed = false });
    RH_ScopedInstall(HasQueueTailArrivedAtSlot, 0x5EBBA0, { .reversed = false });
    RH_ScopedInstall(HasEmptySlot, 0x5EBB00, { .reversed = false });
    // RH_ScopedOverloadedInstall(GetPedUsingEffect, "Internal", 0x5EB740, void*(CPedAttractorManager::*)(const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&));
    // RH_ScopedOverloadedInstall(GetPedUsingEffect, "", 0x5EBE50, void*(CPedAttractorManager::*)(const C2dEffect*, const CEntity*));
    // RH_ScopedOverloadedInstall(GetRelevantAttractor, "Internal", 0x5EB7B0, void*(CPedAttractorManager::*)(const CPed*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&));
    // RH_ScopedOverloadedInstall(GetRelevantAttractor, "", 0x5EBF50, void*(CPedAttractorManager::*)(const CPed*, const C2dEffect*, const CEntity*));
    RH_ScopedInstall(ComputeEffectPos, 0x5E96C0);
    RH_ScopedInstall(ComputeEffectUseDir, 0x5E96E0, { .reversed = false });
    RH_ScopedInstall(ComputeEffectQueueDir, 0x5E9730, { .reversed = false });
    RH_ScopedInstall(ComputeEffectForwardDir, 0x5E9780, { .reversed = false });
    RH_ScopedInstall(RegisterPed, 0x5EF980, { .reversed = false });
    RH_ScopedInstall(RegisterPedWithAttractor, 0x5EFCA0, { .reversed = false });
    RH_ScopedInstall(IsApproachable, 0x5EA220, { .reversed = false });
    RH_ScopedGlobalInstall(GetPedAttractorManager, 0x5EE190);
}

CPedAttractorManager* GetPedAttractorManager() {
    static CPedAttractorManager p; // NOTSA: They used `new`.. Uh, and also (BUG): they never freed the pointer originally xD
    return &p;
}

// notsa
auto& CPedAttractorManager::GetArrayOfType(ePedAttractorType t) {
    switch (t) {
    case PED_ATTRACTOR_ATM:            return m_ATMs;
    case PED_ATTRACTOR_SEAT:           return m_Seats;
    case PED_ATTRACTOR_STOP:           return m_Stops;
    case PED_ATTRACTOR_PIZZA:          return m_Pizzas;
    case PED_ATTRACTOR_SHELTER:        return m_Shelters;
    case PED_ATTRACTOR_TRIGGER_SCRIPT: return m_TriggerScripts;
    case PED_ATTRACTOR_LOOK_AT:        return m_LookAts;
    case PED_ATTRACTOR_SCRIPTED:       return m_Scripted;
    case PED_ATTRACTOR_PARK:           return m_Parks;
    case PED_ATTRACTOR_STEP:           return m_Steps;
    default:                           NOTSA_UNREACHABLE();
    }    
}

// 0x? 0x5EF710 ?
void CPedAttractorManager::RestoreStuffFromMem() {
    NOTSA_UNREACHABLE("Unused function");
}

// 0x5EF920
bool CPedAttractorManager::BroadcastArrival(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& attractors) {
    return attractor
        && rng::contains(attractors, attractor)
        && attractor->BroadcastArrival(ped);
}

// 0x5EFE20
bool CPedAttractorManager::BroadcastArrival(CPed* ped, CPedAttractor* attractor) {
    return attractor
        && IsPedRegisteredWithEffect(ped)
        && BroadcastArrival(ped, attractor, GetArrayOfType(attractor->GetType()));
}

// 0x5EC660
bool CPedAttractorManager::BroadcastDeparture(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& attractors) {
    if (!attractor) {
        return false;
    }
    const auto it = rng::find(attractors, attractor);
    if (it == attractors.end()) {
        return false;
    }
    attractor->BroadcastDeparture(ped);
    if (!attractor->GetNoOfRegisteredPeds()) {
        attractors.erase(it);
    }
    return true;
}

// 0x5EC980
bool CPedAttractorManager::BroadcastDeparture(CPed* ped, CPedAttractor* attractor) {
    return attractor
        && IsPedRegisteredWithEffect(ped)
        && BroadcastDeparture(ped, attractor, GetArrayOfType(attractor->GetType()));
}

// 0x5EC740
bool CPedAttractorManager::DeRegisterPed(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& attractors) {
    if (!attractor) {
        return false;
    }
    const auto it = rng::find(attractors, attractor);
    if (it == attractors.end()) {
        return false;
    }
    attractor->DeRegisterPed(ped);
    if (!attractor->GetNoOfRegisteredPeds()) {
        attractors.erase(it);
    }
    return true;
}

// 0x5EC850
bool CPedAttractorManager::DeRegisterPed(CPed* ped, CPedAttractor* attractor) {
    return attractor
        && IsPedRegisteredWithEffect(ped)
        && DeRegisterPed(ped, attractor, GetArrayOfType(attractor->GetType()));
}

// 0x5EB5F0
// all xrefs are dead functions
bool CPedAttractorManager::RemoveEffect(const C2dEffectPedAttractor* fx, const SArray<CPedAttractor*>& attractors) {
    for (auto& a : attractors) {
        if (a->GetEffect() == fx) {
            a->AbortPedTasks();
        }
    }
    return false;
}

// 0x5EBA30
// all xrefs are dead functions
bool CPedAttractorManager::RemoveEffect(const C2dEffectPedAttractor* fx) {
    return RemoveEffect(fx, GetArrayOfType(fx->m_nAttractorType));
}

// 0x5EB640
bool CPedAttractorManager::IsPedRegistered(CPed* ped, const SArray<CPedAttractor*>& attractors) {
    return rng::any_of(attractors, [ped](CPedAttractor* a) {
        return a->IsRegisteredWithPed(ped);
    });
}

// 0x5EBCB0
bool CPedAttractorManager::IsPedRegisteredWithEffect(CPed* ped) {
    return IsPedRegistered(ped, m_Seats)
        || IsPedRegistered(ped, m_ATMs)
        || IsPedRegistered(ped, m_Stops)
        || IsPedRegistered(ped, m_Pizzas)
        || IsPedRegistered(ped, m_Shelters)
        || IsPedRegistered(ped, m_TriggerScripts)
        || IsPedRegistered(ped, m_LookAts)
        || IsPedRegistered(ped, m_Scripted)
        || IsPedRegistered(ped, m_Parks)
        || IsPedRegistered(ped, m_Steps);
}

// 0x5EBD70
bool CPedAttractorManager::IsPedRegisteredWithEffect(CPed* ped, const C2dEffect* fx, const CEntity* entity) {
    return IsPedRegisteredWithEffect(ped, fx, entity, m_Seats)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_ATMs)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_Stops)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_Pizzas)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_Shelters)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_TriggerScripts)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_LookAts)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_Scripted)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_Parks)
        || IsPedRegisteredWithEffect(ped, fx, entity, m_Steps);
}

// 0x5EB690
bool CPedAttractorManager::IsPedRegisteredWithEffect(CPed* ped, const C2dEffect* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors) {
    return plugin::CallMethodAndReturn<bool, 0x5EB690, CPedAttractorManager*, CPed*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&>(this, ped, fx, entity, attractors);
}

// 0x5EB6F0
CPedAttractor* CPedAttractorManager::FindAssociatedAttractor(const C2dEffect* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors) {
    return plugin::CallMethodAndReturn<CPedAttractor*, 0x5EB6F0>(this, fx, entity, &attractors);
}

// 0x5EBBA0
bool CPedAttractorManager::HasQueueTailArrivedAtSlot(const C2dEffect* fx, const CEntity* entity) {
    return plugin::CallMethodAndReturn<bool, 0x5EBBA0, CPedAttractorManager*, const C2dEffect*, const CEntity*>(this, fx, entity);
}

// 0x5EBB00
bool CPedAttractorManager::HasEmptySlot(const C2dEffect* fx, const CEntity* entity) {
    return plugin::CallMethodAndReturn<bool, 0x5EBB00, CPedAttractorManager*, const C2dEffect*, const CEntity*>(this, fx, entity);
}

// 0x5EB740
CPed* CPedAttractorManager::GetPedUsingEffect(const C2dEffect* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors) {
    return plugin::CallMethodAndReturn<CPed*, 0x5EB740, CPedAttractorManager*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&>(this, fx, entity, attractors);
}

// 0x5EBE50
CPed* CPedAttractorManager::GetPedUsingEffect(const C2dEffect* fx, const CEntity* entity) {
    return plugin::CallMethodAndReturn<CPed*, 0x5EBE50, CPedAttractorManager*, const C2dEffect*, const CEntity*>(this, fx, entity);
}

// 0x5EB7B0
const CPedAttractor* CPedAttractorManager::GetRelevantAttractor(const CPed* ped, const C2dEffect* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors) {
    return plugin::CallMethodAndReturn<const CPedAttractor*, 0x5EB7B0, CPedAttractorManager*, const CPed*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&>(this, ped, fx, entity, attractors);
}

// 0x5EBF50
const CPedAttractor* CPedAttractorManager::GetRelevantAttractor(const CPed* ped, const C2dEffectBase* fx, const CEntity* entity) {
    return plugin::CallMethodAndReturn<const CPedAttractor*, 0x5EBF50, CPedAttractorManager*, const CPed*, const C2dEffectBase*, const CEntity*>(this, ped, fx, entity);
}

// 0x5E96C0
void CPedAttractorManager::ComputeEffectPos(const C2dEffect* fx, const CMatrix& mat, CVector& vec) {
    vec.FromMultiply(mat, &fx->m_pos);
}

// 0x5E96E0
void CPedAttractorManager::ComputeEffectUseDir(const C2dEffect* fx, const CMatrix& mat, CVector& vec) {
    assert(false);
}

// 0x5E9730
void CPedAttractorManager::ComputeEffectQueueDir(const C2dEffect* fx, const CMatrix& mat, CVector& vec) {
    assert(false);
}

// 0x5E9780
void CPedAttractorManager::ComputeEffectForwardDir(const C2dEffect* fx, const CMatrix& mat, CVector& vec) {
    assert(false);
}

// 0x5EF980
void CPedAttractorManager::RegisterPed(CPed* ped, C2dEffect*, CEntity*, int32, SArray<CPedAttractor*>& attractors) {
    assert(false);
}

// 0x5EFCA0
CPedAttractor* CPedAttractorManager::RegisterPedWithAttractor(CPed* ped, C2dEffectBase* fx, CEntity* entity, eMoveState ms) {
    return plugin::CallMethodAndReturn<CPedAttractor*, 0x5EFCA0>(this, ped, fx, entity, ms);
}

// 0x5EA220
bool CPedAttractorManager::IsApproachable(C2dEffect* fx, const CMatrix& mat, int32 unused, CPed* ped) {
    return plugin::CallAndReturn<bool, 0x5EA220, C2dEffect*, const CMatrix&, int32, CPed*>(fx, mat, unused, ped);
}
