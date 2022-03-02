#pragma once

#include "TaskSimple.h"

class CTaskSimpleCreateCarAndGetIn : public CTaskSimple {
public:
    CVector     m_pos{};                // 0x8
    int32       m_model{};              // 0x14
    CVehicle*   m_createdVeh{};         // 0x18
    CVector     m_pathNodePos{};        // 0x1C
    int32       m_timeMs{};             // 0x28
    int32       m_waitTime{};           // 0x2C
    bool        m_waitTimeSet{};        // 0x30
    int8        m_resetWaitTime{};      // 0x31

public:
    static constexpr auto Type = TASK_SIMPLE_CREATE_CAR_AND_GET_IN;

    static void InjectHooks();

    CTaskSimpleCreateCarAndGetIn(CVector const& pos, int32 model);
    ~CTaskSimpleCreateCarAndGetIn();

    CTask* Clone() override;
    eTaskType GetTaskType() override { return Type; };
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool ProcessPed(CPed* ped) override;

private:
    CTaskSimpleCreateCarAndGetIn* Constructor(CVector const& pos, int32 model) {
        this->CTaskSimpleCreateCarAndGetIn::CTaskSimpleCreateCarAndGetIn(pos, model);
        return this;
    }

    CTaskSimpleCreateCarAndGetIn* Destructor() {
        this->CTaskSimpleCreateCarAndGetIn::~CTaskSimpleCreateCarAndGetIn();
        return this;
    }


    CTask * Clone_Reversed() { return CTaskSimpleCreateCarAndGetIn::Clone(); }
    auto GetTaskType_Reversed() { return CTaskSimpleCreateCarAndGetIn::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed * ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleCreateCarAndGetIn::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed * ped) { return CTaskSimpleCreateCarAndGetIn::ProcessPed(ped); }
};
VALIDATE_SIZE(CTaskSimpleCreateCarAndGetIn, 0x34);
