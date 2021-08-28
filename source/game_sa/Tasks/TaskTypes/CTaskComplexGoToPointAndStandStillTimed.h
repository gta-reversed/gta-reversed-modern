#pragma once
#include "CTaskComplexGoToPointAndStandStill.h"
#include "CTaskTimer.h"

class CTaskComplexGoToPointAndStandStillTimed : public CTaskComplexGoToPointAndStandStill
{
public:
    int m_nTime;
    CTaskTimer m_timer;

    static void InjectHooks();

    CTaskComplexGoToPointAndStandStillTimed(int moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, int time);
    ~CTaskComplexGoToPointAndStandStillTimed();
private:
    CTaskComplexGoToPointAndStandStillTimed* Constructor(int moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, int time);
public:
    CTask* Clone() override;
    void StopTimer(CEvent* _event) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* Clone_Reversed();
    void StopTimer_Reversed(CEvent* _event);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexGoToPointAndStandStillTimed, 0x38);