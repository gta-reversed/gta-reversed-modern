/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "TaskTimer.h"

enum class eFacialExpression {
    NONE    = -1,
    SURP    =  0,
    SURPM   =  1,
    URIOS   =  2, // can be 2 or 4
    ANGER   =  3, // can be 3 or 5
    URIOS_1 =  4,
    ANGER_1 =  5,
    TALK    =  7,
    GUM     =  8,
};

class CTaskSimpleFacial : public CTaskSimple {
public:
    CTaskTimer        m_Timer;
    eFacialExpression m_nFacialExpression;
    int32             m_nDuration;

public:
    static constexpr auto Type = TASK_SIMPLE_FACIAL;

    CTaskSimpleFacial(eFacialExpression nFacialExpress, int32 nDuration);
    ~CTaskSimpleFacial() override = default; // 0x690CB0

    eTaskType GetTaskType() const override { return Type; } // 0x690CA0
    CTask* Clone() const override { return new CTaskSimpleFacial(m_nFacialExpression, m_nDuration); } // 0x692820
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;
    static AnimationId GetAnimId(eFacialExpression expression);
};
VALIDATE_SIZE(CTaskSimpleFacial, 0x1C);
