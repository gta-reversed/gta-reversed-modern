#pragma once

#include "TaskSimple.h"
#include "Base.h"
#include "Vector.h"

class CEntity;

class CTaskSimpleThrowControl : public CTaskSimple {
public:
    bool m_bIsFinished;
    bool m_bStartedThrowTask;
    CEntity* m_TargetEntity;
    CVector  m_TargetPos;

public:
    static constexpr auto Type = TASK_SIMPLE_THROW_CTRL;

    CTaskSimpleThrowControl(CEntity* targetEntity, const CVector* pos);
    ~CTaskSimpleThrowControl() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleThrowControl(m_TargetEntity, &m_TargetPos); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    static void InjectHooks();
    CTaskSimpleThrowControl* Constructor(CEntity* targetEntity, CVector const* pos) { this->CTaskSimpleThrowControl::CTaskSimpleThrowControl(targetEntity, pos); return this; }
    CTaskSimpleThrowControl* Destructor() { this->CTaskSimpleThrowControl::~CTaskSimpleThrowControl(); return this; }
};
VALIDATE_SIZE(CTaskSimpleThrowControl, 0x1C);
