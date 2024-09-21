#pragma once

#include "TaskSimpleCarDrive.h"

class CPed;
class CEvent;
class CVehicle;
class CTaskSimpleCarSetTempAction;

class NOTSA_EXPORT_VTABLE CTaskSimpleCarSetTempAction : public CTaskSimpleCarDrive {

public:
    uint32 m_action = {}; // TODO: ENUM => CAutoPilot::TemporaryAction
    uint32 m_durationMs = {};

public:
    static void InjectHooks();

    constexpr static auto Type = eTaskType::TASK_SIMPLE_CAR_SET_TEMP_ACTION;

    CTaskSimpleCarSetTempAction(CVehicle* veh, uint32 action, uint32 timeMs);
    CTaskSimpleCarSetTempAction(const CTaskSimpleCarSetTempAction&);
    ~CTaskSimpleCarSetTempAction() = default;

    CTask*    Clone() const override { return new CTaskSimpleCarSetTempAction(*this); }
    eTaskType GetTaskType() const override { return Type; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool      ProcessPed(CPed* ped) override;

private: // Wrappers for hooks
    // 0x63D6F0
    CTaskSimpleCarSetTempAction* Constructor(CVehicle* veh, uint32 action, uint32 timeMs) {
        this->CTaskSimpleCarSetTempAction::CTaskSimpleCarSetTempAction(veh, action, timeMs);
        return this;
    }
    // 0x63D730
    CTaskSimpleCarSetTempAction* Destructor() {
        this->CTaskSimpleCarSetTempAction::~CTaskSimpleCarSetTempAction();
        return this;
    }
};
