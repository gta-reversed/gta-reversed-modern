#pragma once

#include <utility>
#include "TaskSimple.h"
#include "eTargetDoor.h"

class CAnimBlendAssociation;
class CVehicle;
class CTaskUtilityLineUpPedWithCar;

class CTaskSimpleCarSlowDragPedOut : public CTaskSimple {
public:
    bool                          m_bAnimFinished;
    CAnimBlendAssociation*        m_AnimAssoc;
    CVehicle*                     m_Vehicle;
    eTargetDoor                   m_TargetDoor;
    CTaskUtilityLineUpPedWithCar* m_LineUpPedWithCarTask;
    bool                          m_bWasPedStatic;

public:
    static constexpr auto Type = TASK_SIMPLE_CAR_SLOW_DRAG_PED_OUT;

    CTaskSimpleCarSlowDragPedOut(CVehicle* vehicle, eTargetDoor targetDoor, CTaskUtilityLineUpPedWithCar* lineUpPedWithCarTask, bool isPedStatic);
    ~CTaskSimpleCarSlowDragPedOut() override;

    static void FinishAnimCarSlowDragPedOutCB(CAnimBlendAssociation* anim, void* task);

    std::pair<AssocGroupId, AnimationId> ComputeAnimID();
    void StartAnim(const CPed* ped);
    CPed* GetJackedPed() const; // NOTSA

    CTask* Clone() const override { return new CTaskSimpleCarSlowDragPedOut(m_Vehicle, m_TargetDoor, m_LineUpPedWithCarTask, m_bWasPedStatic); } // 0x649FD0
    eTaskType GetTaskType() const override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

private:
    void ComputeAnimID_Wrapper(AssocGroupId& animGroup, AnimationId& animId);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleCarSlowDragPedOut* Constructor(CVehicle* veh, eTargetDoor targetDoor, CTaskUtilityLineUpPedWithCar* lineUpPedWithCarTask, bool isPedStatic) { this->CTaskSimpleCarSlowDragPedOut::CTaskSimpleCarSlowDragPedOut(veh, targetDoor, lineUpPedWithCarTask, isPedStatic); return this; }
    CTaskSimpleCarSlowDragPedOut* Destructor() { this->CTaskSimpleCarSlowDragPedOut::~CTaskSimpleCarSlowDragPedOut(); return this; }

    CTask * Clone_Reversed() { return CTaskSimpleCarSlowDragPedOut::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleCarSlowDragPedOut::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed * ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleCarSlowDragPedOut::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed * ped) { return CTaskSimpleCarSlowDragPedOut::ProcessPed(ped); }
    bool SetPedPosition_Reversed(CPed * ped) { return CTaskSimpleCarSlowDragPedOut::SetPedPosition(ped); }
};
VALIDATE_SIZE(CTaskSimpleCarSlowDragPedOut, 0x20);
