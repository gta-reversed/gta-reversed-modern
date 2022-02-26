/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimpleIKChain.h"

class CTaskSimpleIKManager : public CTaskSimple {
public:
    // 0 - CTaskSimpleIKLookAt
    // 1, 2 - Left and right arm `CTaskSimpleIKPointArm`
    CTaskSimpleIKChain* m_pIKChainTasks[4]{};
    bool                m_bAborting{};

public:
    static void InjectHooks();

    CTaskSimpleIKManager();
    ~CTaskSimpleIKManager();

    void AddIKChainTask(CTaskSimpleIKChain* task, int32 slot);
    CTaskSimpleIKChain* GetTaskAtSlot(int32);

    CTaskSimpleIKManager* Clone() override;
    eTaskType GetTaskType() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool ProcessPed(CPed* ped) override;
private:
    CTaskSimpleIKManager* Constructor();
    CTaskSimpleIKManager* Destructor();

    CTaskSimpleIKManager* Clone_Reversed() { return CTaskSimpleIKManager::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleIKManager::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleIKManager::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed* ped) { return CTaskSimpleIKManager::ProcessPed(ped); }
};

VALIDATE_SIZE(CTaskSimpleIKManager, 0x1C);
