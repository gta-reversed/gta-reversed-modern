#pragma once

#include "TaskComplex.h"

class CTaskComplexObserveTrafficLightsAndAchieveHeading : public CTaskComplex {
public:
    int32 m_nDurationInMs;
    float m_fTargetHeading;

public:
    static constexpr auto Type = TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING;

    CTaskComplexObserveTrafficLightsAndAchieveHeading(int32 durationInMs, float targetHeading);
    ~CTaskComplexObserveTrafficLightsAndAchieveHeading() override = default; // 0x631980

    eTaskType GetTaskType() const override { return Type; } // 0x631940
    CTask* Clone() const override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;

    CTask* CreateSubTask(eTaskType taskType) const;

private:
    friend void InjectHooksMain();
    static void InjectHooks() {
        RH_ScopedClass(CTaskComplexObserveTrafficLightsAndAchieveHeading);
        RH_ScopedCategory("Tasks/TaskTypes");

        RH_ScopedVirtualInstall(Clone, 0x636490);
        RH_ScopedVirtualInstall(ControlSubTask, 0x631AD0);
        RH_ScopedVirtualInstall(CreateFirstSubTask, 0x631AC0);
        RH_ScopedVirtualInstall(CreateNextSubTask, 0x631A70);
        RH_ScopedVirtualInstall(MakeAbortable, 0x631950);
    }

    CTaskComplexObserveTrafficLightsAndAchieveHeading* Constructor(int32 durationInMs, float fTargetHeading) {
        this->CTaskComplexObserveTrafficLightsAndAchieveHeading::CTaskComplexObserveTrafficLightsAndAchieveHeading(durationInMs, fTargetHeading);
        return this;
    }

    CTask* Clone_Reversed() { return Clone(); }
    CTask* ControlSubTask_Reversed(CPed* ped) { return ControlSubTask(ped); }
    CTask* CreateFirstSubTask_Reversed(CPed* ped) { return CreateFirstSubTask(ped); }
    CTask* CreateNextSubTask_Reversed(CPed* ped) { return CreateNextSubTask(ped); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) { return MakeAbortable(ped, priority, event); }
};

VALIDATE_SIZE(CTaskComplexObserveTrafficLightsAndAchieveHeading, 0x14);
