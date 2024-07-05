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

    bool BroadcastArrival(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& array);
    bool BroadcastArrival(CPed* ped, CPedAttractor* attractor);

    bool BroadcastDeparture(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& array);
    bool BroadcastDeparture(CPed* ped, CPedAttractor* attractor);

    bool DeRegisterPed(CPed* ped, CPedAttractor* attractor, SArray<CPedAttractor*>& array);
    bool DeRegisterPed(CPed* ped, CPedAttractor* attractor);

    bool RemoveEffect(const C2dEffect* effect, const SArray<CPedAttractor*>& array);
    bool RemoveEffect(const C2dEffect* effect);

    bool IsPedRegistered(CPed* ped, const SArray<CPedAttractor*>& array);
    bool IsPedRegisteredWithEffect(CPed* ped);
    bool IsPedRegisteredWithEffect(CPed* ped, const C2dEffect* effect, const CEntity* entity);
    bool IsPedRegisteredWithEffect(CPed* ped, const C2dEffect* effect, const CEntity* entity, const SArray<CPedAttractor*>& array);

    CPedAttractor* FindAssociatedAttractor(const C2dEffect* effect, const CEntity* entity, const SArray<CPedAttractor*>& array);
    bool HasQueueTailArrivedAtSlot(const C2dEffect* effect, const CEntity* entity);
    bool HasEmptySlot(const C2dEffect* effect, const CEntity* entity);

    CPed* GetPedUsingEffect(const C2dEffect* effect, const CEntity* entity, const SArray<CPedAttractor*>& array);
    CPed* GetPedUsingEffect(const C2dEffect* effect, const CEntity* entity = nullptr);

    const CPedAttractor* GetRelevantAttractor(const CPed* ped, const C2dEffect* effect, const CEntity* entity, const SArray<CPedAttractor*>& array);
    const CPedAttractor* GetRelevantAttractor(const CPed* ped, const C2dEffectBase* effect, const CEntity* entity);

    static void ComputeEffectPos(const C2dEffect* effect, const CMatrix& mat, CVector& vec);
    static void ComputeEffectUseDir(const C2dEffect* effect, const CMatrix& mat, CVector& vec);
    static void ComputeEffectQueueDir(const C2dEffect* effect, const CMatrix& mat, CVector& vec);
    static void ComputeEffectForwardDir(const C2dEffect* effect, const CMatrix& mat, CVector& vec);

    void RegisterPed(CPed* ped, C2dEffect*, CEntity*, int32, SArray<CPedAttractor*>& array);
    CPedAttractor* RegisterPedWithAttractor(CPed* ped, C2dEffectBase* fx, CEntity* entity, eMoveState ms);

    static bool IsApproachable(C2dEffect* effect, const CMatrix& mat, int32 unused, CPed* ped);
private:
    auto& GetArrayOfType(ePedAttractorType t);
};
VALIDATE_SIZE(CPedAttractorManager, 0xA0);

CPedAttractorManager* GetPedAttractorManager();
