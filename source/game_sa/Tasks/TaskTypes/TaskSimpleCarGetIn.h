#pragma once

#include "TaskSimple.h"

class CVehicle;
class CTask;
class CTaskUtilityLineUpPedWithCar;
class CAnimBlendAssociation;

typedef void (*CAnimBlendAssocationCallback)(CAnimBlendAssociation *, void *); // todo: move

/*!
* Task responsible for playing the get-in animation.
* In case of vehicles it is created right after the door opening anim ends.
*/
class NOTSA_EXPORT_VTABLE CTaskSimpleCarGetIn : public CTaskSimple {
public:
    bool m_bIsFinished;                      // Has the anim finished (=> meaning task has finished)
    CAnimBlendAssociation* m_Anim;           // The animation playing
    CAnimBlendAssocationCallback m_cb;       // Unused
    CTask* m_pCallbackTask;                  // Unused
    CVehicle* m_TargetVehicle;               // The vehicle we're getting into
    uint32 m_nTargetDoor;                    // The door we want to enter at
    CTaskUtilityLineUpPedWithCar* m_Utility; // Utility lineup task

public:
    constexpr static auto Type = TASK_SIMPLE_CAR_GET_IN;

    CTaskSimpleCarGetIn(CVehicle* vehicle, uint32 door, CTaskUtilityLineUpPedWithCar* task);
    ~CTaskSimpleCarGetIn();

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleCarGetIn(m_TargetVehicle, m_nTargetDoor, m_Utility); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    void StartAnim(const CPed* ped);
    static void FinishAnimCarGetInCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleCarGetIn* Constructor(CVehicle* vehicle, uint32 door, CTaskUtilityLineUpPedWithCar* task) { this->CTaskSimpleCarGetIn::CTaskSimpleCarGetIn(vehicle, door, task); return this; }
    CTaskSimpleCarGetIn* Destructor() { this->CTaskSimpleCarGetIn::~CTaskSimpleCarGetIn(); return this; }
};
VALIDATE_SIZE(CTaskSimpleCarGetIn, 0x24);
