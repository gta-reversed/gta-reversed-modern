/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTaskComplex.h"

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
        using namespace ReversibleHooks;
        Install("CTaskSimpleHoldEntity", "Clone_Reversed", 0x637060, &CTaskComplexUseGoggles::Clone_Reversed);
        Install("CTaskSimpleHoldEntity", "GetTaskType_Reversed", 0x634F10, &CTaskComplexUseGoggles::GetTaskType_Reversed);
        Install("CTaskSimpleHoldEntity", "CreateNextSubTask_Reversed", 0x634F40, &CTaskComplexUseGoggles::CreateNextSubTask_Reversed);
        Install("CTaskSimpleHoldEntity", "CreateFirstSubTask_Reversed", 0x634F90, &CTaskComplexUseGoggles::CreateFirstSubTask_Reversed);
        Install("CTaskSimpleHoldEntity", "ControlSubTask_Reversed", 0x635050, &CTaskComplexUseGoggles::ControlSubTask_Reversed);
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
