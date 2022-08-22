#pragma once

#include "TaskSimple.h"
#include "Vector.h"

class CTaskUtilityLineUpPedWithCar;
class CAnimBlendAssociation;
class CVehicle;

class CTaskSimpleCarAlign : public CTaskSimple {
public:
    bool m_bIsFinished;
    CAnimBlendAssociation* m_Anim;

    CVehicle* m_TargetVehicle;
    CVector   m_TargetDoorPos;
    uint32    m_nTargetDoor;

    CTaskUtilityLineUpPedWithCar* m_Utility;

public:
    static constexpr auto Type = TASK_SIMPLE_CAR_ALIGN;

    CTaskSimpleCarAlign(CVehicle* targetVehicle, CVector const& targetDoorPos, uint32 targetDoor, CTaskUtilityLineUpPedWithCar* utility);
    ~CTaskSimpleCarAlign() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleCarAlign(m_TargetVehicle, m_TargetDoorPos, m_nTargetDoor, m_Utility); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    void FixHeading(CPed* ped);
    void StartAnim(CPed* ped);

    static void FinishAnimCarAlignCB(CAnimBlendAssociation*, void*);

    static void InjectHooks();
    CTaskSimpleCarAlign* Constructor(CVehicle* veh, CVector const& doorPos, int32 targetDoor, CTaskUtilityLineUpPedWithCar* taskLineUp) { this->CTaskSimpleCarAlign::CTaskSimpleCarAlign(veh, doorPos, targetDoor, taskLineUp); return this; }
    CTaskSimpleCarAlign* Destructor() { this->CTaskSimpleCarAlign::~CTaskSimpleCarAlign(); return this; }
};
