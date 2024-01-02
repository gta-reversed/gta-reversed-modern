#pragma once

#include "TaskSimple.h"

class CTaskSimpleDead : public CTaskSimple {
public:
    uint32 m_nDeathTimeMS;
    uint8  m_nFlags;

public:
    static constexpr auto Type = TASK_SIMPLE_DEAD;

    CTaskSimpleDead(uint32 deathTime, bool);
    ~CTaskSimpleDead() override = default; // 0x6305F0

    eTaskType GetTaskType() const override { return Type; } // 0x6305D0
    CTask* Clone() const override { return new CTaskSimpleDead(m_nDeathTimeMS, m_nFlags); } // 0x636100
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override { return true; }; // 0x6305E0
    bool ProcessPed(CPed* ped) override;

    static void InjectHooks();
};
VALIDATE_SIZE(CTaskSimpleDead, 0x10);
