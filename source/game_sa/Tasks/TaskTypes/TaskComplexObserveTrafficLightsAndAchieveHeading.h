#pragma once

#include "TaskComplex.h"

class CTaskComplexObserveTrafficLightsAndAchieveHeading : public CTaskComplex {
public:
    int32 m_nDurationInMs;
    float m_fTargetHeading;

public:
    CTaskComplexObserveTrafficLightsAndAchieveHeading(int32 durationInMs, float targetHeading);
    ~CTaskComplexObserveTrafficLightsAndAchieveHeading() override = default; // 0x631980

    eTaskType GetTaskType() override { return TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING; } // 0x631940
    CTask* Clone() override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    CTask* CreateSubTask(eTaskType taskType) const;

private:
    friend void InjectHooksMain();
    static void InjectHooks() {
        RH_ScopedClass(CTaskComplexObserveTrafficLightsAndAchieveHeading);
        RH_ScopedCategory("Tasks/TaskTypes");

        RH_ScopedInstall(Clone_Reversed, 0x636490);
        RH_ScopedInstall(ControlSubTask_Reversed, 0x631AD0);
        RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x631AC0);
        RH_ScopedInstall(CreateNextSubTask_Reversed, 0x631A70);
        RH_ScopedInstall(MakeAbortable_Reversed, 0x631950, true);
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
