#pragma once

#include "TaskSimple.h"

class CVehicle;
class CTaskUtilityLineUpPedWithCar;
class CAnimBlendAssociation;

class NOTSA_EXPORT_VTABLE CTaskSimpleCarCloseDoorFromOutside : public CTaskSimple {
    bool m_bIsFinished;
    CAnimBlendAssociation* m_Anim;
    CVehicle* m_TargetVehicle;
    uint32 m_TargetDoor;
    CTaskUtilityLineUpPedWithCar* m_Utility;

public:
    constexpr static auto Type = TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_OUTSIDE;

    CTaskSimpleCarCloseDoorFromOutside(CVehicle* targetVehicle, uint32 targetDoor, CTaskUtilityLineUpPedWithCar* utility);
    ~CTaskSimpleCarCloseDoorFromOutside() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleCarCloseDoorFromOutside(m_TargetVehicle, m_TargetDoor, m_Utility); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    auto ComputeAnimID_Helper() -> std::tuple<AssocGroupId, AnimationId>;
    void ComputeAnimID(AssocGroupId& outGroup, AnimationId& outAnimId); // NOTSA
    void StartAnim(const CPed* ped);
    void ProcessDoorOpen(const CPed* ped); // NOTSA
    static void FinishAnimCarCloseDoorFromOutsideCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleCarCloseDoorFromOutside* Constructor(CVehicle* veh, int32 door, CTaskUtilityLineUpPedWithCar* lineUpTask) { this->CTaskSimpleCarCloseDoorFromOutside::CTaskSimpleCarCloseDoorFromOutside(veh, door, lineUpTask); return this; }
    CTaskSimpleCarCloseDoorFromOutside* Destructor() { this->CTaskSimpleCarCloseDoorFromOutside::~CTaskSimpleCarCloseDoorFromOutside(); return this; }
};
VALIDATE_SIZE(CTaskSimpleCarCloseDoorFromOutside, 0x1C);
