#pragma once

#include "TaskSimpleStandStill.h"

class CEntity;
class CTaskSimpleWaitUntilAreaCodesMatch;
class CPed;
class CEvent;

class NOTSA_EXPORT_VTABLE CTaskSimpleWaitUntilAreaCodesMatch : public CTaskSimpleStandStill {
public:
    CPed* m_TargetPed;

public:
    constexpr static auto Type = TASK_WAIT_FOR_MATCHING_AREA_CODES;

    CTaskSimpleWaitUntilAreaCodesMatch(CPed* targetPed); // 0x635540
    ~CTaskSimpleWaitUntilAreaCodesMatch() override;         // 0x6355E0

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleWaitUntilAreaCodesMatch(m_TargetPed); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return priority == ABORT_PRIORITY_IMMEDIATE; }
    bool ProcessPed(CPed* ped) override;

    static void InjectHooks();
    CTaskSimpleWaitUntilAreaCodesMatch* Constructor(CPed* pedToWaitFor) { this->CTaskSimpleWaitUntilAreaCodesMatch::CTaskSimpleWaitUntilAreaCodesMatch(pedToWaitFor); return this; }
    CTaskSimpleWaitUntilAreaCodesMatch* Destructor() { this->CTaskSimpleWaitUntilAreaCodesMatch::~CTaskSimpleWaitUntilAreaCodesMatch(); return this; }
};
VALIDATE_SIZE(CTaskSimpleWaitUntilAreaCodesMatch, 0x24);
