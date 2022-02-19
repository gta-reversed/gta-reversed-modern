#pragma once

#include "TaskSimpleDie.h"

class CTaskSimpleDrown : public CTaskSimpleDie {
public:
    bool m_bShouldExecute;

public:
    CTaskSimpleDrown();
    ~CTaskSimpleDrown() override = default; // 0x62FF10, 0x6378D0

    eTaskType GetTaskType() override { return TASK_SIMPLE_DROWN; } // 0x62FF00
    CTask* Clone() override { return new CTaskSimpleDrown(); } // 0x635E60
    bool ProcessPed(CPed* ped) override;
};
