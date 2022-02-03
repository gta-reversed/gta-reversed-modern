/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"

class CTaskComplexUseGoggles : public CTaskComplex {
public:
    CTaskComplexUseGoggles();
    ~CTaskComplexUseGoggles() override;

    CTask* Clone() override { return new CTaskComplexUseGoggles(); }      // 0x637060
    eTaskType GetTaskType() override { return TASK_COMPLEX_USE_GOGGLES; } // 0x634F10
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

#if ANDROID
    void Serialize();
#endif

private:
    friend void InjectHooksMain();
    static void InjectHooks() {
        RH_ScopedClass(CTaskComplexUseGoggles);
        RH_ScopedCategory("Tasks/TaskTypes");

        RH_ScopedInstall(Clone_Reversed, 0x637060);
        RH_ScopedInstall(GetTaskType_Reversed, 0x634F10);
        RH_ScopedInstall(CreateNextSubTask_Reversed, 0x634F40);
        RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x634F90);
        RH_ScopedInstall(ControlSubTask_Reversed, 0x635050);
    };

    CTaskComplexUseGoggles* Constructor() {
        this->CTaskComplexUseGoggles::CTaskComplexUseGoggles();
        return this;
    }

    CTask* Clone_Reversed() { return Clone(); };
    eTaskType GetTaskType_Reversed() { return GetTaskType(); };
    CTask* CreateNextSubTask_Reversed(CPed* ped) { return CreateNextSubTask(ped); };
    CTask* CreateFirstSubTask_Reversed(CPed* ped) { return CreateFirstSubTask(ped); };
    CTask* ControlSubTask_Reversed(CPed* ped) { return ControlSubTask(ped); };
};

extern void TaskComplexUseGogglesTestCode();
