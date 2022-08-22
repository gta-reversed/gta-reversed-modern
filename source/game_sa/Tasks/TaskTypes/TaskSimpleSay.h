#pragma once

#include "TaskSimple.h"
#include "TaskTimer.h"

class CEvent;
class CTaskSimpleSay;
class CPed;

class CTaskSimpleSay : public CTaskSimple {
public:
    uint32 m_SayId;
    uint32 m_SayDuration;
    CTaskTimer m_Timer;

public:
    constexpr static auto Type = TASK_SIMPLE_SAY;

    CTaskSimpleSay(uint32 sayId, uint32 sayDuration); // 0x48E360
    ~CTaskSimpleSay() override = default; // 0x48E4E0

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleSay(m_SayId, m_SayDuration); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return true; }
    bool ProcessPed(CPed* ped) override;
};
VALIDATE_SIZE(CTaskSimpleSay, 0x28);
