#pragma once

#include "TaskSimple.h"
#include "AnimationEnums.h"

class CTaskUtilityLineUpPedWithCar;
class CPed;
class CVehicle;

class CTaskSimpleBikeJacked : public CTaskSimple {
    bool m_bIsFinished;
    CAnimBlendAssociation* m_Anim;
    AnimationId m_nFinishAnim; // Animation that is played after `m_Anim` has finished
    CVehicle* m_TargetVehicle;
    int32 m_TargetDoor;
    int32 m_DownTime;
    CPed* m_DraggingPed;
    bool  m_bWasDriver;
    CTaskUtilityLineUpPedWithCar* m_Utility;

public:
    constexpr static auto Type = eTaskType::TASK_SIMPLE_BIKE_JACKED;

    CTaskSimpleBikeJacked(CVehicle* targetVehicle, int32 targetDoor, int32 downTime, CPed* draggingPed, bool bWasDriver);
    ~CTaskSimpleBikeJacked() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleBikeJacked(m_TargetVehicle, m_TargetDoor, m_DownTime, m_DraggingPed, m_bWasDriver); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    static void FinishAnimBikeHitCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleBikeJacked* Constructor(CVehicle* vehicle, uint32 door, uint32 time, CPed* carJacker, bool a6) { this->CTaskSimpleBikeJacked::CTaskSimpleBikeJacked(vehicle, door, time, carJacker, a6); return this; }
    CTaskSimpleBikeJacked* Destructor() { this->CTaskSimpleBikeJacked::~CTaskSimpleBikeJacked(); return this; }
};
VALIDATE_SIZE(CTaskSimpleBikeJacked, 0x2C);
