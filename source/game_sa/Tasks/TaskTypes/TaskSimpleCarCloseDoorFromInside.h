#pragma once

#include "TaskSimple.h"

class CAnimBlendAssociation;
class CVehicle;
class CTaskUtilityLineUpPedWithCar;

class NOTSA_EXPORT_VTABLE CTaskSimpleCarCloseDoorFromInside : public CTaskSimple {
public:
    bool m_bIsFinished;
    CAnimBlendAssociation* m_anim;
    CVehicle* m_TargetVehicle;
    uint32 m_nTargetDoor;
    CTaskUtilityLineUpPedWithCar* m_Utility;

public:
    constexpr static auto Type = TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_INSIDE;

    CTaskSimpleCarCloseDoorFromInside(CVehicle* targetVehicle, uint32 door, CTaskUtilityLineUpPedWithCar* utility);
    ~CTaskSimpleCarCloseDoorFromInside() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleCarCloseDoorFromInside(m_TargetVehicle, m_nTargetDoor, m_Utility); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    void ComputeAnimID(AssocGroupId& outGroup, AnimationId& outAnimId);
    auto ComputeAnimID_Helper() -> std::tuple<AssocGroupId, AnimationId>;
    void StartAnim(CPed const* ped);
    void ProcessDoorOpen(CPed const* ped); // NOTSA

    static void FinishAnimCarCloseDoorFromInsideCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleCarCloseDoorFromInside* Constructor(CVehicle* veh, uint32 door, CTaskUtilityLineUpPedWithCar* lineUpTask) { this->CTaskSimpleCarCloseDoorFromInside::CTaskSimpleCarCloseDoorFromInside(veh, door, lineUpTask); return this; }
    CTaskSimpleCarCloseDoorFromInside* Destructor() { this->CTaskSimpleCarCloseDoorFromInside::~CTaskSimpleCarCloseDoorFromInside(); return this; }
};
VALIDATE_SIZE(CTaskSimpleCarCloseDoorFromInside, 0x1C);
