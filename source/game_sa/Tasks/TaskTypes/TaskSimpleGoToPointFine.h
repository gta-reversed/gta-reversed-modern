#pragma once

#include "TaskSimpleGoTo.h"

class CTaskSimpleGoToPointFine : public CTaskSimpleGoTo {
public:
    float m_fMoveRatio;

public:
    static constexpr auto Type = TASK_SIMPLE_GO_TO_POINT_FINE;

    CTaskSimpleGoToPointFine(float moveRatio, CVector targetPoint, float fRadius = 0.5f, CEntity* entity = nullptr);
    ~CTaskSimpleGoToPointFine() override = default;

    eTaskType GetTaskType() const override { return Type; }
    CTask*    Clone() const override;
    bool      MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool      ProcessPed(CPed* ped) override;

    void  Finish(CPed* ped);

    void  SetBlendedMoveAnim(CPed* ped);
    void  SetTargetPos(CVector posn);
    void  SetMoveRatio(float value) { m_fMoveRatio = value; } // 0x65F3A0
    static float BaseRatio(eMoveState moveState);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleGoToPointFine* Constructor(float moveRatio, CVector targetPoint, float fRadius, CEntity* entity);

    CTask*  Clone_Reversed() const;
    bool   MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool   ProcessPed_Reversed(CPed* ped);
};
VALIDATE_SIZE(CTaskSimpleGoToPointFine, 0x24);
