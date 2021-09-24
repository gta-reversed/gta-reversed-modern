#pragma once

#include "CTaskSimpleGoTo.h"

class CTaskSimpleGoToPoint : public CTaskSimpleGoTo
{
public:
    union {
        struct
        {
            uint8 m_bMoveTowardsTargetPoint : 1;
            uint8 m_b02 : 1;
            uint8 m_b03 : 1;
            uint8 m_b04 : 1;
            uint8 m_b05 : 1;
        } gotoPointFlags;
        uint8 m_GoToPointFlags;
    };
private:
    uint8 field_21[3]; // padding
public:
    CVector m_vecLastPedPos;

    static void InjectHooks();

    CTaskSimpleGoToPoint(int32 moveState, const CVector& targetPoint, float fRadius, bool bMoveTowardsTargetPoint, bool a6);
    ~CTaskSimpleGoToPoint();
private:
    CTaskSimpleGoToPoint* Constructor(int32 moveState, const CVector& targetPoint, float fRadius, bool bMoveTowardsTargetPoint, bool a6);
public:
    CTask* Clone();
    eTaskType GetTaskType() override { return TASK_SIMPLE_GO_TO_POINT; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
private:
    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
public:
    // bDontCheckRadius is always false
    void UpdatePoint(const CVector& targetPosition, float fRadius, bool bDontCheckRadius);
};

VALIDATE_SIZE(CTaskSimpleGoToPoint, 0x30);