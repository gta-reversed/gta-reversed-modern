#pragma once

#include "TaskSimpleCarDrive.h"

class CPed;
class CEvent;
class CVehicle;
class CTaskSimpleCarSetTempAction;

class NOTSA_EXPORT_VTABLE CTaskSimpleCarSetTempAction : public CTaskSimpleCarDrive {
public:
    uint32 m_Action; // TODO: ENUM => CAutoPilot::TemporaryAction
    uint32 m_DurationMs;

public:
    constexpr static auto Type = TASK_SIMPLE_CAR_SET_TEMP_ACTION;

    CTaskSimpleCarSetTempAction(CVehicle* vehicle, uint32 action, uint32 timeMs);
    ~CTaskSimpleCarSetTempAction() = default;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleCarSetTempAction(m_Action, m_DurationMs); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    static void InjectHooks();
    CTaskSimpleCarSetTempAction* Constructor(CVehicle* veh, uint32 action, uint32 timeMs) { this->CTaskSimpleCarSetTempAction::CTaskSimpleCarSetTempAction(veh, action, timeMs); return this; }
    CTaskSimpleCarSetTempAction* Destructor() { this->CTaskSimpleCarSetTempAction::~CTaskSimpleCarSetTempAction(); return this; }
};
VALIDATE_SIZE(CTaskSimpleCarSetTempAction, 0x68);
