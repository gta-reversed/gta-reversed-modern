#pragma once

#include "TaskSimple.h"
#include "TaskTimer.h"

class NOTSA_EXPORT_VTABLE CTaskSimplePause : public CTaskSimple {
public:
    CTaskTimer m_timer;
    int32      m_nTime;

public:
    static constexpr auto Type = TASK_SIMPLE_PAUSE;

    explicit CTaskSimplePause(int32 time = 0);
    ~CTaskSimplePause() = default;

    CTask* Clone() const override;
    eTaskType GetTaskType() const override {
        return TASK_SIMPLE_PAUSE;
    };
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed(CPed* ped) override;
    bool ProcessPed_Reversed(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimplePause* Constructor(int32 time);

};

VALIDATE_SIZE(CTaskSimplePause, 0x18);
