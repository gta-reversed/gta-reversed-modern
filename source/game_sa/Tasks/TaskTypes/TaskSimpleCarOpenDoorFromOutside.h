#pragma once

#include "TaskSimple.h"
#include "AnimationEnums.h"

class CTaskSimpleCarOpenDoorFromOutside;
class CTaskUtilityLineUpPedWithCar;
class CAnimBlendAssociation;
class CPed;
class CVehicle;
class CEvent;

class NOTSA_EXPORT_VTABLE CTaskSimpleCarOpenDoorFromOutside : public CTaskSimple {
public:
    bool m_bIsFinished;
    CAnimBlendAssociation* m_Anim;
    CVehicle* m_TargetVehicle;
    int32 m_nTargetDoor;
    bool m_bQuitAfterOpeningDoor;
    bool m_bHasSetCanPlayerExitCarFlag;
    CTaskUtilityLineUpPedWithCar* m_Utility;
    float m_fDoorStartRatio;

public:
    constexpr static auto Type = TASK_SIMPLE_CAR_OPEN_DOOR_FROM_OUTSIDE;

    CTaskSimpleCarOpenDoorFromOutside(CVehicle* targetVehicle, int32 targetDoor, CTaskUtilityLineUpPedWithCar* utility, bool bQuitAfterOpeningDoor);
    ~CTaskSimpleCarOpenDoorFromOutside() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleCarOpenDoorFromOutside(m_TargetVehicle, m_nTargetDoor, m_Utility, m_bQuitAfterOpeningDoor); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    void ComputeAnimID_ToHook(AssocGroupId& group, AnimationId& animation);
    auto ComputeAnimID() -> std::pair<AssocGroupId, AnimationId>;
    void StartAnim(CPed* ped);
    void IfNotAlreadySetPlayerCanExitCarFlag(); // NOTSA?

    static void FinishAnimCarOpenDoorFromOutsideCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleCarOpenDoorFromOutside* Constructor(CVehicle* veh, int32 door, CTaskUtilityLineUpPedWithCar* lineUpTask, bool disallowPlayerDriverToExitCar) { this->CTaskSimpleCarOpenDoorFromOutside::CTaskSimpleCarOpenDoorFromOutside(veh, door, lineUpTask, disallowPlayerDriverToExitCar); return this; }
    CTaskSimpleCarOpenDoorFromOutside* Destructor() { this->CTaskSimpleCarOpenDoorFromOutside::~CTaskSimpleCarOpenDoorFromOutside(); return this; }
};
