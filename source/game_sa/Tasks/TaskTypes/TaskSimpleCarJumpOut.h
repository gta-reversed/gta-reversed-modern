#pragma once

#include "TaskSimple.h"

class CAnimBlendAssociation;
class CTaskUtilityLineUpPedWithCar;
class CVehicle;

class NOTSA_EXPORT_VTABLE CTaskSimpleCarJumpOut : public CTaskSimple {
public:
    bool m_bIsFinished;
    CAnimBlendAssociation* m_Anim;
    CVehicle* m_TargetVehicle;
    float m_fStartCarSpeed;
    uint32 m_nTargetDoor;
    uint8 m_nDoorFlagsToClear;
    uint8 m_nNumGettingInToClear;
    CTaskUtilityLineUpPedWithCar* m_Utility;

public:
    constexpr static auto Type = TASK_SIMPLE_CAR_JUMP_OUT;

    CTaskSimpleCarJumpOut(CVehicle* targetVehicle, uint32 targetDoor, CTaskUtilityLineUpPedWithCar* utility);
    ~CTaskSimpleCarJumpOut() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleCarJumpOut(m_TargetVehicle, m_nTargetDoor, m_Utility); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    void StartAnim(const CPed* ped);
    auto ComputeAnimID() -> std::pair<AssocGroupId, AnimationId>; // NOTSA: Changed return type
    void ComputeAnimID_ToHook(AssocGroupId& animGroup, AnimationId& animId) { std::tie(animGroup, animId) = ComputeAnimID(); } // Hooking this instead

    static void FinishAnimCarJumpOutCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleCarJumpOut* Constructor(CVehicle* veh, uint32 door, CTaskUtilityLineUpPedWithCar* lineUpTask) { this->CTaskSimpleCarJumpOut::CTaskSimpleCarJumpOut(veh, door, lineUpTask); return this; }
    CTaskSimpleCarJumpOut* Destructor() { this->CTaskSimpleCarJumpOut::~CTaskSimpleCarJumpOut(); return this; }
};
VALIDATE_SIZE(CTaskSimpleCarJumpOut, 0x24);
