#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CTaskSimpleGoToPoint;

class CTaskComplexGoToPointAndStandStill : public CTaskComplex {
public:
    eMoveState m_moveState;
    CVector    m_vecTargetPoint;
    float      m_fRadius;          ///< Ped stops moving after it is within the radius of the point.
    float      m_fMoveStateRadius; ///< The ped will either sprint, run, or walk depending on far it is from the radius
    union {
        struct {
            uint8 m_b01 : 1;                    // 0x1
            uint8 m_bGoToPoint : 1;             // 0x2
            uint8 m_bTargetPointUpdated : 1;    // 0x4
            uint8 m_b04 : 1;                    // 0x8
            uint8 m_b05 : 1;                    // 0x10
        };
        uint8 m_nFlags;
    };

public:
    static constexpr auto Type = TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL;

    CTaskComplexGoToPointAndStandStill(eMoveState moveState, const CVector& targetPoint, float fRadius = 1.5f, float fMoveStateRadius = 2.f, bool bUnknown = false, bool bGoToPoint = false);
    ~CTaskComplexGoToPointAndStandStill() override;

    eTaskType GetTaskType() const override { return Type; }
    CTask*    Clone() const override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask*  Clone_Reversed() const;
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);

    void   GoToPoint(const CVector& targetPoint, float fRadius = 1.5f, float fMoveStateRadius = 2.f, bool bUpdateTargetEvenIfItsTheSame = false);
    void   SelectMoveState(CTaskSimpleGoToPoint* pGotoPointTask, CPed* ped, float fMoveStateRadius, float fRunOrSprintRadius);
    CTask* CreateFirstSubTask(int32 taskId, CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    // 0x668120
    CTaskComplexGoToPointAndStandStill* Constructor(eMoveState moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint) {
        this->CTaskComplexGoToPointAndStandStill::CTaskComplexGoToPointAndStandStill(moveState, targetPoint, fRadius, fMoveStateRadius, bUnknown, bGoToPoint);
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexGoToPointAndStandStill, 0x28);
