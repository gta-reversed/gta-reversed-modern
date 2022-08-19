#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CTaskSimpleGoToPoint;

class CTaskComplexGoToPointAndStandStill : public CTaskComplex {
public:
    int32   m_moveState;
    CVector m_vecTargetPoint;
    float   m_fRadius;          // ped stops moving after it is within the radius of the point.
    float   m_fMoveStateRadius; // The ped will either sprint, run, or walk depending on far it is from the radius
    union {
        struct {
            uint8 m_b01 : 1;
            uint8 m_bGoToPoint : 1;
            uint8 m_bTargetPointUpdated : 1;
            uint8 m_b04 : 1;
            uint8 m_b05 : 1;
        };
        uint8 m_nFlags;
    };

public:
    static constexpr auto Type = TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL;

    CTaskComplexGoToPointAndStandStill(int32 moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint);
    ~CTaskComplexGoToPointAndStandStill() override;

    eTaskType GetTaskType() override { return Type; }
    CTask*    Clone() override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* Clone_Reversed();
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);

    void   GoToPoint(const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUpdateTargetEvenIfItsTheSame);
    void   SelectMoveState(CTaskSimpleGoToPoint* pGotoPointTask, CPed* ped, float fMoveStateRadius, float fRunOrSprintRadius);
    CTask* CreateFirstSubTask(int32 taskId, CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexGoToPointAndStandStill* Constructor(int32 moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint);
};
VALIDATE_SIZE(CTaskComplexGoToPointAndStandStill, 0x28);
