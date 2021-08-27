#pragma once

#include "CTaskSimple.h"
#include "CTaskTimer.h"

class CTaskSimplePause : public CTaskSimple {
public:
    CTaskTimer m_timer;
    int m_nTime;

public:
    CTaskSimplePause(int time);
    ~CTaskSimplePause();

    CTask* Clone() override;
    eTaskType GetId() override {
        return TASK_SIMPLE_PAUSE;
    };
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed(CPed* ped) override;
    bool ProcessPed_Reversed(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimplePause* Constructor(int time);

};

VALIDATE_SIZE(CTaskSimplePause, 0x18);
