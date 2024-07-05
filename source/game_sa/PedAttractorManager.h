#pragma once

#include "SArray.h"

class CPedAttractor;
class C2dEffect;
class CEntity;
class CPed;

class CPedAttractorManager {
    SArray<CPedAttractor*> m_Seats; // These 2 are swapped (in contrast to the enum).... All others follow the order of `ePedAttractorType`!
    SArray<CPedAttractor*> m_ATMs;  //
    SArray<CPedAttractor*> m_Stops;
    SArray<CPedAttractor*> m_Pizzas;
    SArray<CPedAttractor*> m_Shelters;
    SArray<CPedAttractor*> m_TriggerScripts;
    SArray<CPedAttractor*> m_LookAts;
    SArray<CPedAttractor*> m_Scripted;
    SArray<CPedAttractor*> m_Parks;
    SArray<CPedAttractor*> m_Steps;

public:
    static void InjectHooks();

    CPedAttractorManager() = default; // 0x5EDF10

    void RestoreStuffFromMem();

    bool BroadcastArrival(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& attractors);
    bool BroadcastArrival(CPed* ped, CPedAttractor* attractor);

    bool BroadcastDeparture(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& attractors);
    bool BroadcastDeparture(CPed* ped, CPedAttractor* attractor);

    bool DeRegisterPed(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& attractors);
    bool DeRegisterPed(CPed* ped, CPedAttractor* attractor);

    bool RemoveEffect(const C2dEffectPedAttractor* fx, const SArray<CPedAttractor*>& attractors);
    bool RemoveEffect(const C2dEffectPedAttractor* fx);

    bool IsPedRegistered(CPed* ped, const SArray<CPedAttractor*>& attractors);
    bool IsPedRegisteredWithEffect(CPed* ped);
    bool IsPedRegisteredWithEffect(CPed* ped, const C2dEffectPedAttractor* fx, const CEntity* entity);
    bool IsPedRegisteredWithEffect(CPed* ped, const C2dEffectPedAttractor* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors);

    CPedAttractor* FindAssociatedAttractor(const C2dEffectPedAttractor* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors);
    bool HasQueueTailArrivedAtSlot(const C2dEffectBase* fx, const CEntity* entity);
    bool HasEmptySlot(const C2dEffectBase* baseFx, const CEntity* entity);

    CPed* GetPedUsingEffect(const C2dEffectPedAttractor* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors);
    CPed* GetPedUsingEffect(const C2dEffectPedAttractor* fx, const CEntity* entity = nullptr);

    const CPedAttractor* GetRelevantAttractor(const CPed* ped, const C2dEffectPedAttractor* fx, const CEntity* entity, const SArray<CPedAttractor*>& attractors);
    const CPedAttractor* GetRelevantAttractor(const CPed* ped, const C2dEffectBase* fx, const CEntity* entity);

    static void ComputeEffectPos(const C2dEffectPedAttractor* fx, const CMatrix& mat, CVector& vec);
    static void ComputeEffectUseDir(const C2dEffectPedAttractor* fx, const CMatrix& mat, CVector& vec);
    static void ComputeEffectQueueDir(const C2dEffectPedAttractor* fx, const CMatrix& mat, CVector& vec);
    static void ComputeEffectForwardDir(const C2dEffectPedAttractor* fx, const CMatrix& mat, CVector& vec);

    void RegisterPed(CPed* ped, C2dEffectPedAttractor*, CEntity*, int32, SArray<CPedAttractor*>& attractors);
    CPedAttractor* RegisterPedWithAttractor(CPed* ped, C2dEffectBase* fx, CEntity* entity, eMoveState ms);

    static bool IsApproachable(C2dEffectPedAttractor* fx, const CMatrix& mat, int32 unused, CPed* ped);
private:
    auto& GetAttractorsOfType(ePedAttractorType t);
};
VALIDATE_SIZE(CPedAttractorManager, 0xA0);

CPedAttractorManager* GetPedAttractorManager();
