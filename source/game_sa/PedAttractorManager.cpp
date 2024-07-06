#include "StdInc.h"

#include "PedAttractorManager.h"
#include <TaskTypes/TaskComplexUseAttractor.h>
#include <TaskTypes/TaskComplexWaitAtAttractor.h>

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
    RH_ScopedOverloadedInstall(RemoveEffect, "Internal", 0x5EB5F0, bool(CPedAttractorManager::*)(const C2dEffectPedAttractor* fx, const SArray<CPedAttractor*>& attractors));
    RH_ScopedOverloadedInstall(RemoveEffect, "", 0x5EBA30, bool(CPedAttractorManager::*)(const C2dEffectPedAttractor* fx));
    RH_ScopedInstall(IsPedRegistered, 0x5EB640);
    RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "Ped", 0x5EBCB0, bool(CPedAttractorManager::*)(CPed*));
    RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "Effect", 0x5EBD70, bool(CPedAttractorManager::*)(CPed*, const C2dEffectPedAttractor*, const CEntity*));
    RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "Internal", 0x5EB690, bool(CPedAttractorManager::*)(CPed*, const C2dEffectPedAttractor*, const CEntity*, const SArray<CPedAttractor*>&));
    RH_ScopedInstall(FindAssociatedAttractor, 0x5EB6F0);
    RH_ScopedInstall(HasQueueTailArrivedAtSlot, 0x5EBBA0);
    RH_ScopedInstall(HasEmptySlot, 0x5EBB00);
    RH_ScopedOverloadedInstall(GetPedUsingEffect, "Internal", 0x5EB740, CPed*(CPedAttractorManager::*)(const C2dEffectPedAttractor*, const CEntity*, const SArray<CPedAttractor*>&));
    RH_ScopedOverloadedInstall(GetPedUsingEffect, "", 0x5EBE50, CPed*(CPedAttractorManager::*)(const C2dEffectPedAttractor*, const CEntity*));
    RH_ScopedOverloadedInstall(GetRelevantAttractor, "Internal", 0x5EB7B0, const CPedAttractor*(CPedAttractorManager::*)(const CPed*, const C2dEffectPedAttractor*, const CEntity*, const SArray<CPedAttractor*>&));
    RH_ScopedOverloadedInstall(GetRelevantAttractor, "", 0x5EBF50, const CPedAttractor*(CPedAttractorManager::*)(const CPed*, const C2dEffectPedAttractor*, const CEntity*));
    RH_ScopedInstall(ComputeEffectPos, 0x5E96C0);
    RH_ScopedInstall(ComputeEffectUseDir, 0x5E96E0);
    RH_ScopedInstall(ComputeEffectQueueDir, 0x5E9730);
    RH_ScopedInstall(ComputeEffectForwardDir, 0x5E9780);
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
auto& CPedAttractorManager::GetAttractorsOfType(ePedAttractorType t) {
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
        && BroadcastArrival(ped, attractor, GetAttractorsOfType(attractor->GetType()));
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
        && BroadcastDeparture(ped, attractor, GetAttractorsOfType(attractor->GetType()));
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
        && DeRegisterPed(ped, attractor, GetAttractorsOfType(attractor->GetType()));
}

// 0x5EB5F0
// all xrefs are dead functions
bool CPedAttractorManager::RemoveEffect(const C2dEffectPedAttractor* fx, const SArray<CPedAttractor*>& attractors) {
    for (auto* const a : attractors) {
        if (a->GetEffect() == fx) {
            a->AbortPedTasks();
        }
    }
    return false;
}

// 0x5EBA30
// all xrefs are dead functions
bool CPedAttractorManager::RemoveEffect(const C2dEffectPedAttractor* fx) {
    return RemoveEffect(fx, GetAttractorsOfType(fx->m_nAttractorType));
}

// 0x5EB640
bool CPedAttractorManager::IsPedRegistered(CPed* ped, const SArray<CPedAttractor*>& attractors) {
    return rng::any_of(attractors, [ped](CPedAttractor* a) {
        return a->IsRegisteredWithPed(ped);
    });
}

// 0x5EB690
bool CPedAttractorManager::IsPedRegisteredWithEffect(CPed* ped, const C2dEffectPedAttractor* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors) {
    return GetRelevantAttractor(ped, fx, entity, attractors) != nullptr; // NOTSA: Using `GetRelevantAttractor` instead of duplicate code
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
bool CPedAttractorManager::IsPedRegisteredWithEffect(CPed* ped, const C2dEffectPedAttractor* fx, const CEntity* entity) {
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

// 0x5EB6F0
CPedAttractor* CPedAttractorManager::FindAssociatedAttractor(const C2dEffectPedAttractor* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors) {
    for (auto* const a : attractors) {
        if (a->GetEffect() == fx && a->GetEntity() == entity) {
            return a;
        }
    }
    return nullptr;
}

// 0x5EBBA0
bool CPedAttractorManager::HasQueueTailArrivedAtSlot(const C2dEffectBase* baseFx, const CEntity* entity) {
    const auto* const fx = C2dEffect::DynCast<const C2dEffectPedAttractor>(baseFx);
    if (!fx) {
        return false;
    }
    const auto* const attractor = FindAssociatedAttractor(fx, entity, GetAttractorsOfType(fx->m_nAttractorType));
    if (!attractor) {
        return true;
    }
    const auto* const pedAtQueueTail = attractor->GetTailOfQueue();
    if (!pedAtQueueTail) {
        return true;
    }
    if (attractor->GetHeadOfQueue() == attractor->GetTailOfQueue()) { // Queue has 1 ped only
        return pedAtQueueTail->GetTaskManager().Find<CTaskComplexUseAttractor>(true) != nullptr;
    }
    const auto* const tWaitAtAttractor = pedAtQueueTail->GetTaskManager().Find<CTaskComplexWaitAtAttractor>(true);
    return tWaitAtAttractor
        && tWaitAtAttractor->m_slot == attractor->GetSizeOfQueue() - 1;
}

// 0x5EBB00
bool CPedAttractorManager::HasEmptySlot(const C2dEffectBase* baseFx, const CEntity* entity) {
    const auto* const fx = C2dEffect::DynCast<const C2dEffectPedAttractor>(baseFx);
    if (!fx) {
        return false;
    }
    const auto* const attractor = FindAssociatedAttractor(fx, entity, GetAttractorsOfType(fx->m_nAttractorType));
    if (!attractor) {
        return true;
    }
    return attractor->HasEmptySlot();
}

// 0x5EB740
CPed* CPedAttractorManager::GetPedUsingEffect(const C2dEffectPedAttractor* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors) {
    for (const auto* const a : attractors) {
        if (a->GetEffect() == fx && a->GetEntity() == entity) {
            return a->GetHeadOfQueue();
        }
    }
    return nullptr;
}

// 0x5EBE50
CPed* CPedAttractorManager::GetPedUsingEffect(const C2dEffectPedAttractor* fx, const CEntity* entity) {
    return GetPedUsingEffect(fx, entity, GetAttractorsOfType(fx->m_nAttractorType));
}

// 0x5EB7B0
const CPedAttractor* CPedAttractorManager::GetRelevantAttractor(const CPed* ped, const C2dEffectPedAttractor* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors) {
    for (const auto* const a : attractors) {
        if (a->GetEffect() == fx && a->GetEntity() == entity && a->IsRegisteredWithPed(ped)) {
            return a;
        }
    }
    return nullptr;
}

// 0x5EBF50
const CPedAttractor* CPedAttractorManager::GetRelevantAttractor(const CPed* ped, const C2dEffectPedAttractor* fx, const CEntity* entity) {
    for (const auto* const attractors : {
        &m_Seats,
        &m_ATMs,
        &m_Stops,
        &m_Pizzas,
        &m_Shelters,
        &m_TriggerScripts,
        &m_LookAts,
        &m_Scripted,
        &m_Parks,
        &m_Steps
    }) {
        if (const auto* const attractor = GetRelevantAttractor(ped, fx, entity, *attractors)) {
            return attractor;
        }
    }
    return nullptr;
}

// 0x5E96C0
void CPedAttractorManager::ComputeEffectPos(const C2dEffectPedAttractor* fx, const CMatrix& mat, CVector& vec) {
    vec = mat.TransformPoint(fx->m_pos);
}

// 0x5E96E0
void CPedAttractorManager::ComputeEffectUseDir(const C2dEffectPedAttractor* fx, const CMatrix& mat, CVector& vec) {
    vec = mat.TransformVector(fx->m_vecUseDir);
}

// 0x5E9730
void CPedAttractorManager::ComputeEffectQueueDir(const C2dEffectPedAttractor* fx, const CMatrix& mat, CVector& vec) {
    vec = mat.TransformVector(fx->m_vecQueueDir);
}

// 0x5E9780
void CPedAttractorManager::ComputeEffectForwardDir(const C2dEffectPedAttractor* fx, const CMatrix& mat, CVector& vec) {
    vec = mat.TransformVector(fx->m_vecForwardDir);
}

// 0x5EF980
void CPedAttractorManager::RegisterPed(CPed* ped, C2dEffectPedAttractor* fx, CEntity* entity, eMoveState moveState, const SArray<CPedAttractor*>& attractors) {
    assert(false);
}

// 0x5EFCA0
CPedAttractor* CPedAttractorManager::RegisterPedWithAttractor(CPed* ped, C2dEffectBase* fx, CEntity* entity, eMoveState ms) {
    return plugin::CallMethodAndReturn<CPedAttractor*, 0x5EFCA0>(this, ped, fx, entity, ms);
}

// 0x5EA220
bool CPedAttractorManager::IsApproachable(C2dEffectPedAttractor* fx, const CMatrix& mat, int32 unused, CPed* ped) {
    return plugin::CallAndReturn<bool, 0x5EA220, C2dEffectPedAttractor*, const CMatrix&, int32, CPed*>(fx, mat, unused, ped);
}
