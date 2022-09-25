#pragma once

#include "TaskComplex.h"

class CTaskComplexEvasiveCower : public CTaskComplex {
public:
    CVector  m_Pos;
    CEntity* m_Entity;

public:
    static constexpr auto Type = TASK_COMPLEX_EVASIVE_COWER;

    CTaskComplexEvasiveCower(CEntity* entity, CVector& pos);
    ~CTaskComplexEvasiveCower() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexEvasiveCower(m_Entity, m_Pos); }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override { return m_pSubTask; }

    CTask* CreateSubTask(eTaskType taskType);
};
VALIDATE_SIZE(CTaskComplexEvasiveCower, 0x1C);
