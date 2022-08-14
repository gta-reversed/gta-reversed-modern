#pragma once
#include "TaskSimple.h"

class CTaskLeanOnVehicle : public CTaskSimple {
public:
    CVehicle*  m_vehicle = {}; // 8
    int32      m_leanAnimDurationInMs = {}; // 0xC
    int8       field_10 = {}; // 0x10
    uint8      field_11[3] = {}; // 0x11
    CAnimBlendAssociation* m_leanAnimAssoc = {}; // 0x14
    int32      m_nAnimId = {}; // 0x18
    CTaskTimer m_leanTimer = {}; // 0x1C
    int8       field_28 = {}; // 0x28
    int8       m_leanAnimId = {}; // 0x29
    int8       m_stopLeaning = {}; // 0x2A
    int8       field_2B = {}; // 0x2B

public:
    static void InjectHooks();

    ~CTaskLeanOnVehicle();
    CTaskLeanOnVehicle(CEntity* vehicle, int32 leanAnimDurationInMs, uint8 a4);

    static CTaskLeanOnVehicle* FinishAnimCB(CAnimBlendAssociation* assoc, void* data);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_LEAN_ON_VEHICLE; // ?

    virtual CTask*    Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool      MakeAbortable(CPed* ped, int32 priority, const CEvent* event);
    virtual bool      ProcessPed(CPed* ped);

private: // Wrappers for hooks
    // 0x660F90
    CTaskLeanOnVehicle* Constructor(CEntity* vehicle, int32 leanAnimDurationInMs, uint8 a4) {
        this->CTaskLeanOnVehicle::CTaskLeanOnVehicle(vehicle, leanAnimDurationInMs, a4);
        return this;
    }

    // 0x661030
    CTaskLeanOnVehicle* Destructor() {
        this->CTaskLeanOnVehicle::~CTaskLeanOnVehicle();
        return this;
    }
};
VALIDATE_SIZE(CTaskLeanOnVehicle, 0x2C);
