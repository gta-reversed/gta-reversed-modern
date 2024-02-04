/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimpleIKChain.h"

class NOTSA_EXPORT_VTABLE CTaskSimpleIKManager final : public CTaskSimple {
public:
    // 0    - `CTaskSimpleIKLookAt`
    // 1, 2 - Left and right arm `CTaskSimpleIKPointArm`
    std::array<CTaskSimpleIKChain*, 4> m_IKChainTasks;
    bool                               m_IsAborting;

public:
    static constexpr auto Type = TASK_SIMPLE_IK_MANAGER;

    CTaskSimpleIKManager();
    CTaskSimpleIKManager(const CTaskSimpleIKManager&);
    ~CTaskSimpleIKManager() override;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskSimpleIKManager{*this}; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;

    /*!
    * @addr 0x633940
    * @brief Store \a task in \a slot.
    * @param slot If < 0 the first unused slot will be used.
    */
    void AddIKChainTask(CTaskSimpleIKChain* task, int32 slot);
    CTaskSimpleIKChain* GetTaskAtSlot(int32 slot) { return m_IKChainTasks[slot]; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleIKManager* Constructor() { this->CTaskSimpleIKManager::CTaskSimpleIKManager(); return this; }
    CTaskSimpleIKManager* Destructor() { this->CTaskSimpleIKManager::~CTaskSimpleIKManager(); return this; }
                };
VALIDATE_SIZE(CTaskSimpleIKManager, 0x1C);
