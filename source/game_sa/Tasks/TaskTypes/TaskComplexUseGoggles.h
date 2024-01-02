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
    static constexpr auto Type = TASK_COMPLEX_USE_GOGGLES;

    CTaskComplexUseGoggles() = default; // 0x634EF0
    ~CTaskComplexUseGoggles() override = default; // 0x634F20

    eTaskType GetTaskType() const override { return Type; } // 0x634F10
    CTask* Clone() const override { return new CTaskComplexUseGoggles(); }      // 0x637060
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexUseGoggles* Constructor() {
        this->CTaskComplexUseGoggles::CTaskComplexUseGoggles();
        return this;
    }

    CTask* Clone_Reversed() { return CTaskComplexUseGoggles::Clone(); };
    eTaskType GetTaskType_Reversed() { return CTaskComplexUseGoggles::GetTaskType(); };
    CTask* CreateNextSubTask_Reversed(CPed* ped) { return CTaskComplexUseGoggles::CreateNextSubTask(ped); };
    CTask* CreateFirstSubTask_Reversed(CPed* ped) { return CTaskComplexUseGoggles::CreateFirstSubTask(ped); };
    CTask* ControlSubTask_Reversed(CPed* ped) { return CTaskComplexUseGoggles::ControlSubTask(ped); };
};

void TaskComplexUseGogglesTestCode();
