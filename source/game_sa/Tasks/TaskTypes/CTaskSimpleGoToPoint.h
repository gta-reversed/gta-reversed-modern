#pragma once

#include "CTaskSimpleGoTo.h"

class CTaskSimpleGoToPoint : public CTaskSimpleGoTo
{
public:
    union {
        struct
        {
            unsigned char m_bMoveTowardsTargetPoint : 1;
            unsigned char m_b02 : 1;
            unsigned char m_b03 : 1;
            unsigned char m_b04 : 1;
            unsigned char m_b05 : 1;
        } gotoPointFlags;
        unsigned char m_GoToPointFlags;
    };
private:
    unsigned char field_21[3]; // padding
public:
    CVector m_vecLastPedPos;

    static void InjectHooks();

    CTaskSimpleGoToPoint(int moveState, const CVector& targetPoint, float fRadius, bool bMoveTowardsTargetPoint, bool a6);
    ~CTaskSimpleGoToPoint();
private:
    CTaskSimpleGoToPoint* Constructor(int moveState, const CVector& targetPoint, float fRadius, bool bMoveTowardsTargetPoint, bool a6);
public:
    CTask* Clone();
    eTaskType GetId() override { return TASK_SIMPLE_GO_TO_POINT; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    bool ProcessPed(CPed* ped) override;
private:
    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);
    bool ProcessPed_Reversed(CPed* ped);
public:
    // bDontCheckRadius is always false
    void UpdatePoint(const CVector& targetPosition, float fRadius, bool bDontCheckRadius);
};

VALIDATE_SIZE(CTaskSimpleGoToPoint, 0x30);