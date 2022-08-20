#pragma once

#include "TaskSimple.h"
#include "Base.h"

class CEntity;

class CTaskSimpleFightingControl : public CTaskSimple {
public:
    bool m_bIsFinished;
    uint16 m_nComboSet;
    CEntity* m_TargetEntity;

    float m_fAttackAngle;
    float m_fAttackRange;
    float m_fAttackFreq;

    uint32 m_nNextAttackTime;
    uint32 m_nBlockCounter;

public:
    constexpr static auto Type = TASK_SIMPLE_FIGHT_CTRL;

    CTaskSimpleFightingControl(CEntity* entityToFight, float fAngle, float fRange);
    ~CTaskSimpleFightingControl() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleFightingControl(m_TargetEntity, m_fAttackAngle, m_fAttackRange); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    int16 CalcMoveCommand(CPed* ped);

    static void InjectHooks();
    CTaskSimpleFightingControl* Constructor(CEntity* entityToFight, float angleRad, float dist) { this->CTaskSimpleFightingControl::CTaskSimpleFightingControl(entityToFight, angleRad, dist); return this; }
    CTaskSimpleFightingControl* Destructor() { this->CTaskSimpleFightingControl::~CTaskSimpleFightingControl(); return this; }
};
VALIDATE_SIZE(CTaskSimpleFightingControl, 0x24);
