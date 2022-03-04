#pragma once

#include <utility>
#include "TaskSimple.h"
#include "Enums/eTargetDoor.h"

class CAnimBlendAssociation;
class CVehicle;
class CTaskUtilityLineUpPedWithCar;

class CTaskSimpleCarSlowDragPedOut : public CTaskSimple {
public:
    bool m_animFinished{};                                          // 8
    CAnimBlendAssociation* m_animAssoc{};                   // 0xC
    CVehicle* m_vehicle{};                                  // 0x10
    eTargetDoor m_targetDoor{};                             // 0x14
    CTaskUtilityLineUpPedWithCar* m_lineUpPedWithCarTask{}; // 0x18
    bool m_wasPedStatic{};                                  // 0x1C

public:
    static constexpr auto Type = TASK_SIMPLE_CAR_SLOW_DRAG_PED_OUT;

    static void InjectHooks();

    CTaskSimpleCarSlowDragPedOut(CVehicle* veh, eTargetDoor targetDoor, CTaskUtilityLineUpPedWithCar* lineUpPedWithCarTask, bool isPedStatic);
    CTaskSimpleCarSlowDragPedOut(const CTaskSimpleCarSlowDragPedOut&); // NOTSA - Helper for `Clone()`
    ~CTaskSimpleCarSlowDragPedOut();

    static void FinishAnimCarSlowDragPedOutCB(CAnimBlendAssociation* anim, void* task);

    std::pair<AssocGroupId, AnimationId> ComputeAnimID();
    void StartAnim(CPed* ped);

    CTask* Clone() override { return new CTaskSimpleCarSlowDragPedOut{ *this }; }
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

private:
    void ComputeAnimID_Wrapper(AssocGroupId& animGrp, AnimationId& animId);

    CTaskSimpleCarSlowDragPedOut* Constructor(CVehicle* veh, eTargetDoor targetDoor, CTaskUtilityLineUpPedWithCar* lineUpPedWithCarTask, bool isPedStatic) {
        this->CTaskSimpleCarSlowDragPedOut::CTaskSimpleCarSlowDragPedOut(veh, targetDoor, lineUpPedWithCarTask, isPedStatic);
        return this;
    }

    CTaskSimpleCarSlowDragPedOut* Destructor() {
        this->CTaskSimpleCarSlowDragPedOut::~CTaskSimpleCarSlowDragPedOut();
        return this;
    }

    CTask * Clone_Reversed() { return CTaskSimpleCarSlowDragPedOut::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleCarSlowDragPedOut::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed * ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleCarSlowDragPedOut::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed * ped) { return CTaskSimpleCarSlowDragPedOut::ProcessPed(ped); }
    bool SetPedPosition_Reversed(CPed * ped) { return CTaskSimpleCarSlowDragPedOut::SetPedPosition(ped); }
};
VALIDATE_SIZE(CTaskSimpleCarSlowDragPedOut, 0x20);
