#pragma once

#include "TaskComplex.h"

class CTaskComplexBeInCouple : public CTaskComplex {
public:
    int32 fC;
    CPed* m_Ped;
    bool  byte14;
    bool  byte15;
    bool  byte16;
    float float18;
    int8  byte1C;

public:
    static constexpr auto Type = TASK_COMPLEX_BE_IN_COUPLE;

    CTaskComplexBeInCouple(CPed* ped, bool a3, bool a4, bool a5, float a6);
    ~CTaskComplexBeInCouple() override;

    eTaskType GetTaskType() override { return Type; } // 0x683770
    CTask* Clone() override { return new CTaskComplexBeInCouple(m_Ped, byte14, byte15, byte16, float18); } // 0x6839C0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    void AbortArmIK(CPed* ped);
};
VALIDATE_SIZE(CTaskComplexBeInCouple, 0x20);
