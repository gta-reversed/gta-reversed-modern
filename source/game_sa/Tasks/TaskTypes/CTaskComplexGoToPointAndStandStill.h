#pragma once
#include "CTaskComplex.h"
#include "CVector.h"

class CTaskSimpleGoToPoint;

class CTaskComplexGoToPointAndStandStill : public CTaskComplex 
{
public:
    int m_moveState;
    CVector m_vecTargetPoint;
    float m_fRadius; // ped stops moving after it is within the radius of the point.
    float m_fMoveStateRadius; // The ped will either sprint, run, or walk depending on far it is from the radius
    union {
        struct
        {
            unsigned char m_b01 : 1;
            unsigned char m_bGoToPoint : 1;
            unsigned char m_bTargetPointUpdated : 1;
            unsigned char m_b04 : 1;
            unsigned char m_b05 : 1;
        };
        unsigned char m_nFlags;
    };
private:
    unsigned char field_25[3]; // padding
public:
    static void InjectHooks();
    CTaskComplexGoToPointAndStandStill(int moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint);
    ~CTaskComplexGoToPointAndStandStill();

private:
    CTaskComplexGoToPointAndStandStill* Constructor(int moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint);
public:
    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL; };
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* Clone_Reversed();
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);


    void GoToPoint(const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUpdateTargetEvenIfItsTheSame);
    void SelectMoveState(CTaskSimpleGoToPoint* pGotoPointTask, CPed* pPed, float fMoveStateRadius, float fRunOrSprintRadius);
    CTask* CreateFirstSubTask(int taskId, CPed* ped);
};

VALIDATE_SIZE(CTaskComplexGoToPointAndStandStill, 0x28);