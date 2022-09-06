#pragma once

#include "TaskSimple.h"

class CTaskSimpleCarShuffle;
class CTaskUtilityLineUpPedWithCar;
class CPed;
class CVehicle;
class CAnimBlendAssociation;
class CEvent;


class NOTSA_EXPORT_VTABLE CTaskSimpleCarShuffle : public CTaskSimple {
 
public:
    bool m_animHasFinished = {};  // 0x8
    CAnimBlendAssociation * m_anim = {};  // 0xC
    CVehicle * m_veh = {};  // 0x10
    eTargetDoor m_targetDoor = {};  // 0x14
    CTaskUtilityLineUpPedWithCar * m_lineUpUtility = {};  // 0x18

public:
    static void InjectHooks();

    static constexpr auto Type = eTaskType::TASK_SIMPLE_CAR_SHUFFLE;

    CTaskSimpleCarShuffle(CVehicle* vehicle, eTargetDoor targetDoor, CTaskUtilityLineUpPedWithCar * task);
    CTaskSimpleCarShuffle(const CTaskSimpleCarShuffle& o);
    ~CTaskSimpleCarShuffle();
    static void FinishAnimCarShuffleCB(CAnimBlendAssociation * assoc, void * task);

    void StartAnim(CPed const* a2);

    CTask*    Clone() override { return new CTaskSimpleCarShuffle{*this}; }
    eTaskType GetTaskType() override { return Type; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool      ProcessPed(CPed* ped) override;
    bool      SetPedPosition(CPed * ped) override; 
 
private: // Wrappers for hooks

// 0x646810
CTaskSimpleCarShuffle* Constructor(CVehicle * vehicle, eTargetDoor targetDoor, CTaskUtilityLineUpPedWithCar * task) {
    this->CTaskSimpleCarShuffle::CTaskSimpleCarShuffle(vehicle, targetDoor, task);
    return this;
}
// 0x646890
CTaskSimpleCarShuffle* Destructor() {
    this->CTaskSimpleCarShuffle::~CTaskSimpleCarShuffle();
    return this;
}


};
