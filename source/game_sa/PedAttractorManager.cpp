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
    RH_ScopedOverloadedInstall(BroadcastArrival, "array", 0x5EF920, void(CPedAttractorManager::*)(CPed*, CPedAttractor*, SArray<CPedAttractor*>&));
    RH_ScopedOverloadedInstall(BroadcastArrival, "", 0x5EFE20, void(CPedAttractorManager::*)(CPed*, CPedAttractor*));
    RH_ScopedOverloadedInstall(BroadcastDeparture, "array", 0x5EC660, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*, SArray<CPedAttractor*>&));
    RH_ScopedOverloadedInstall(BroadcastDeparture, "", 0x5EC980, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*));
    RH_ScopedOverloadedInstall(DeRegisterPed, "array", 0x5EC740, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*, SArray<CPedAttractor*>&));
    RH_ScopedOverloadedInstall(DeRegisterPed, "", 0x5EC850, bool(CPedAttractorManager::*)(CPed*, CPedAttractor*));
    // RH_ScopedOverloadedInstall(RemoveEffect, "array", 0x5EB5F0, void(CPedAttractorManager::*)(const C2dEffect* effect, const SArray<CPedAttractor*>& array));
    // RH_ScopedOverloadedInstall(RemoveEffect, "", 0x5EBA30, void(CPedAttractorManager::*)(const C2dEffect* effect));
    RH_ScopedInstall(IsPedRegistered, 0x5EB640, { .reversed = false });
    RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "ped", 0x5EBCB0, bool(CPedAttractorManager::*)(CPed*));
    RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "+effect", 0x5EBD70, bool(CPedAttractorManager::*)(CPed*, const C2dEffect*, const CEntity*));
    // RH_ScopedOverloadedInstall(IsPedRegisteredWithEffect, "+array", 0x5EB690, bool(CPedAttractorManager::*)(CPed*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&));
    RH_ScopedInstall(FindAssociatedAttractor, 0x5EB6F0, { .reversed = false });
    RH_ScopedInstall(HasQueueTailArrivedAtSlot, 0x5EBBA0, { .reversed = false });
    RH_ScopedInstall(HasEmptySlot, 0x5EBB00, { .reversed = false });
    // RH_ScopedOverloadedInstall(GetPedUsingEffect, "array", 0x5EB740, void*(CPedAttractorManager::*)(const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&));
    // RH_ScopedOverloadedInstall(GetPedUsingEffect, "", 0x5EBE50, void*(CPedAttractorManager::*)(const C2dEffect*, const CEntity*));
    // RH_ScopedOverloadedInstall(GetRelevantAttractor, "array", 0x5EB7B0, void*(CPedAttractorManager::*)(const CPed*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&));
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

// 0x? 0x5EF710 ?
void CPedAttractorManager::RestoreStuffFromMem() {
    NOTSA_UNREACHABLE("Unused function");
}

// 0x5EF920
void CPedAttractorManager::BroadcastArrival(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& array) {
    if (!attractor) {
        return;
    }
    if (!rng::contains(array, attractor)) {
        return;
    }
    attractor->BroadcastArrival(ped);
}

// 0x5EFE20
void CPedAttractorManager::BroadcastArrival(CPed* ped, CPedAttractor* attractor) {
    if (!attractor) {
        return;
    }
    if (!IsPedRegisteredWithEffect(ped)) {
        return;
    }
    switch (attractor->GetType()) {
    case PED_ATTRACTOR_ATM:            return BroadcastArrival(ped, attractor, m_ATMs);
    case PED_ATTRACTOR_SEAT:           return BroadcastArrival(ped, attractor, m_Seats); // ?
    case PED_ATTRACTOR_STOP:           return BroadcastArrival(ped, attractor, m_Stops);
    case PED_ATTRACTOR_PIZZA:          return BroadcastArrival(ped, attractor, m_Pizzas);
    case PED_ATTRACTOR_SHELTER:        return BroadcastArrival(ped, attractor, m_Shelters);
    case PED_ATTRACTOR_TRIGGER_SCRIPT: return BroadcastArrival(ped, attractor, m_TriggerScripts);
    case PED_ATTRACTOR_LOOK_AT:        return BroadcastArrival(ped, attractor, m_LookAts);
    case PED_ATTRACTOR_SCRIPTED:       return BroadcastArrival(ped, attractor, m_Scripted);
    case PED_ATTRACTOR_PARK:           return BroadcastArrival(ped, attractor, m_Parks);
    case PED_ATTRACTOR_STEP:           return BroadcastArrival(ped, attractor, m_Steps);
    default:                           NOTSA_UNREACHABLE();
    }
}

// 0x5EC660
bool CPedAttractorManager::BroadcastDeparture(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& array) {
    if (!attractor) {
        return false;
    }
    const auto it = rng::find(array, attractor);
    if (it == array.end()) {
        return false;
    }
    attractor->BroadcastDeparture(ped);
    if (!attractor->GetNoOfRegisteredPeds()) {
        array.erase(it);
    }
    return true;
}

// 0x5EC980
bool CPedAttractorManager::BroadcastDeparture(CPed* ped, CPedAttractor* attractor) {
    if (!attractor) {
        return false;
    }
    if (!IsPedRegisteredWithEffect(ped)) {
        return false;
    }
    switch (attractor->GetType()) {
    case PED_ATTRACTOR_ATM:            return BroadcastDeparture(ped, attractor, m_ATMs);
    case PED_ATTRACTOR_SEAT:           return BroadcastDeparture(ped, attractor, m_Seats);
    case PED_ATTRACTOR_STOP:           return BroadcastDeparture(ped, attractor, m_Stops);
    case PED_ATTRACTOR_PIZZA:          return BroadcastDeparture(ped, attractor, m_Pizzas);
    case PED_ATTRACTOR_SHELTER:        return BroadcastDeparture(ped, attractor, m_Shelters);
    case PED_ATTRACTOR_TRIGGER_SCRIPT: return BroadcastDeparture(ped, attractor, m_TriggerScripts);
    case PED_ATTRACTOR_LOOK_AT:        return BroadcastDeparture(ped, attractor, m_LookAts);
    case PED_ATTRACTOR_SCRIPTED:       return BroadcastDeparture(ped, attractor, m_Scripted);
    case PED_ATTRACTOR_PARK:           return BroadcastDeparture(ped, attractor, m_Parks);
    case PED_ATTRACTOR_STEP:           return BroadcastDeparture(ped, attractor, m_Steps);
    default:                           NOTSA_UNREACHABLE();
    }
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
    if (!attractor) {
        return false;
    }

    if (!IsPedRegisteredWithEffect(ped)) {
        return false;
    }

    switch (attractor->GetType()) {
    case PED_ATTRACTOR_ATM:            return DeRegisterPed(ped, attractor, m_ATMs);
    case PED_ATTRACTOR_SEAT:           return DeRegisterPed(ped, attractor, m_Seats);
    case PED_ATTRACTOR_STOP:           return DeRegisterPed(ped, attractor, m_Stops);
    case PED_ATTRACTOR_PIZZA:          return DeRegisterPed(ped, attractor, m_Pizzas);
    case PED_ATTRACTOR_SHELTER:        return DeRegisterPed(ped, attractor, m_Shelters);
    case PED_ATTRACTOR_TRIGGER_SCRIPT: return DeRegisterPed(ped, attractor, m_TriggerScripts);
    case PED_ATTRACTOR_LOOK_AT:        return DeRegisterPed(ped, attractor, m_LookAts);
    case PED_ATTRACTOR_SCRIPTED:       return DeRegisterPed(ped, attractor, m_Scripted);
    case PED_ATTRACTOR_PARK:           return DeRegisterPed(ped, attractor, m_Parks);
    case PED_ATTRACTOR_STEP:           return DeRegisterPed(ped, attractor, m_Steps);
    default:                           NOTSA_UNREACHABLE();
    }
}

// 0x5EB5F0
void CPedAttractorManager::RemoveEffect(const C2dEffect* effect, const SArray<CPedAttractor*>& array) {
    plugin::CallMethod<0x5EB5F0, CPedAttractorManager*, const C2dEffect*, const SArray<CPedAttractor*>&>(this, effect, array);
}

// 0x5EBA30
void CPedAttractorManager::RemoveEffect(const C2dEffect* effect) {
    plugin::CallMethod<0x5EBA30, CPedAttractorManager*, const C2dEffect*>(this, effect);
}

// 0x5EB640
bool CPedAttractorManager::IsPedRegistered(CPed* ped, const SArray<CPedAttractor*>& array) {
    return plugin::CallMethodAndReturn<bool, 0x5EB640, CPedAttractorManager*, CPed*, const SArray<CPedAttractor*>&>(this, ped, array);
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
bool CPedAttractorManager::IsPedRegisteredWithEffect(CPed* ped, const C2dEffect* effect, const CEntity* entity) {
    return IsPedRegisteredWithEffect(ped, effect, entity, m_Seats)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_ATMs)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_Stops)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_Pizzas)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_Shelters)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_TriggerScripts)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_LookAts)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_Scripted)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_Parks)
        || IsPedRegisteredWithEffect(ped, effect, entity, m_Steps) != 0;
}

// 0x5EB690
bool CPedAttractorManager::IsPedRegisteredWithEffect(CPed* ped, const C2dEffect* effect, const CEntity* entity, const SArray<CPedAttractor*>& array) {
    return plugin::CallMethodAndReturn<bool, 0x5EB690, CPedAttractorManager*, CPed*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&>(this, ped, effect, entity, array);
}

// 0x5EB6F0
void CPedAttractorManager::FindAssociatedAttractor(const C2dEffect* effect, const CEntity* entity, const SArray<CPedAttractor*>& array) {
    assert(false);
}

// 0x5EBBA0
bool CPedAttractorManager::HasQueueTailArrivedAtSlot(const C2dEffect* effect, const CEntity* entity) {
    return plugin::CallMethodAndReturn<bool, 0x5EBBA0, CPedAttractorManager*, const C2dEffect*, const CEntity*>(this, effect, entity);
}

// 0x5EBB00
bool CPedAttractorManager::HasEmptySlot(const C2dEffect* effect, const CEntity* entity) {
    return plugin::CallMethodAndReturn<bool, 0x5EBB00, CPedAttractorManager*, const C2dEffect*, const CEntity*>(this, effect, entity);
}

// 0x5EB740
void* CPedAttractorManager::GetPedUsingEffect(const C2dEffect* effect, const CEntity* entity, const SArray<CPedAttractor*>& array) {
    return plugin::CallMethodAndReturn<void*, 0x5EB740, CPedAttractorManager*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&>(this, effect, entity, array);
}

// 0x5EBE50
CPed* CPedAttractorManager::GetPedUsingEffect(const C2dEffect* effect, const CEntity* entity) {
    return plugin::CallMethodAndReturn<CPed*, 0x5EBE50, CPedAttractorManager*, const C2dEffect*, const CEntity*>(this, effect, entity);
}

// 0x5EB7B0
void* CPedAttractorManager::GetRelevantAttractor(const CPed* ped, const C2dEffect* effect, const CEntity* entity, const SArray<CPedAttractor*>& array) {
    return plugin::CallMethodAndReturn<void*, 0x5EB7B0, CPedAttractorManager*, const CPed*, const C2dEffect*, const CEntity*, const SArray<CPedAttractor*>&>(this, ped, effect, entity, array);
}

// 0x5EBF50
void* CPedAttractorManager::GetRelevantAttractor(const CPed* ped, const C2dEffectBase* effect, const CEntity* entity) {
    return plugin::CallMethodAndReturn<void*, 0x5EBF50, CPedAttractorManager*, const CPed*, const C2dEffectBase*, const CEntity*>(this, ped, effect, entity);
}

// 0x5E96C0
void CPedAttractorManager::ComputeEffectPos(const C2dEffect* effect, const CMatrix& mat, CVector& vec) {
    vec.FromMultiply(mat, &effect->m_pos);
}

// 0x5E96E0
void CPedAttractorManager::ComputeEffectUseDir(const C2dEffect* effect, const CMatrix& mat, CVector& vec) {
    assert(false);
}

// 0x5E9730
void CPedAttractorManager::ComputeEffectQueueDir(const C2dEffect* effect, const CMatrix& mat, CVector& vec) {
    assert(false);
}

// 0x5E9780
void CPedAttractorManager::ComputeEffectForwardDir(const C2dEffect* effect, const CMatrix& mat, CVector& vec) {
    assert(false);
}

// 0x5EF980
void CPedAttractorManager::RegisterPed(CPed* ped, C2dEffect*, CEntity*, int32, SArray<CPedAttractor*>& array) {
    assert(false);
}

// 0x5EFCA0
CPedAttractor* CPedAttractorManager::RegisterPedWithAttractor(CPed* ped, C2dEffectBase* fx, CEntity* entity, eMoveState ms) {
    return plugin::CallMethodAndReturn<CPedAttractor*, 0x5EFCA0>(this, ped, fx, entity, ms);
}

// 0x5EA220
bool CPedAttractorManager::IsApproachable(C2dEffect* effect, const CMatrix& mat, int32 unused, CPed* ped) {
    return plugin::CallAndReturn<bool, 0x5EA220, C2dEffect*, const CMatrix&, int32, CPed*>(effect, mat, unused, ped);
}
