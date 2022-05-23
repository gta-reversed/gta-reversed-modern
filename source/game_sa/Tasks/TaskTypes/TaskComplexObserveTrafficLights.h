#pragma once

#include "TaskComplex.h"

class CTaskComplexObserveTrafficLights : public CTaskComplex {
public:
    int32 dwordC;
    int32 dword10;
    int8  byte14;
    int8  byte15;

public:
    static constexpr auto Type = TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS;

    CTaskComplexObserveTrafficLights();
    ~CTaskComplexObserveTrafficLights() override = default; // 0x6317C0

    CTask* Clone() override { return new CTaskComplexObserveTrafficLights(); }          // 0x636410
    eTaskType GetTaskType() override { return TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS; }    // 0x6317B0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return true; }  // 0x6317D0
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override { return CreateNextSubTask(ped); }    // 0x6318D0
    CTask* ControlSubTask(CPed* ped) override;
};
