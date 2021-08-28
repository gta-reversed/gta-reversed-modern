#pragma once
#include "CTaskComplex.h"

class CTaskComplexFallAndGetUp : public CTaskComplex
{
public:
    eAnimID m_nFallAnimId;
    eAnimGroup m_nFallAnimGroup;
    int m_nFallDownTime;
private:
    CTaskComplexFallAndGetUp* Constructor(eAnimID nFallAnimId, eAnimGroup nFallAnimGroup, int nFallDownTime);
    CTaskComplexFallAndGetUp* Constructor2(int nDir, int nFallDownTime);
public:
    CTaskComplexFallAndGetUp(eAnimID nFallAnimId, eAnimGroup nFallAnimGroup, int nFallDownTime);
    CTaskComplexFallAndGetUp(int nDir, int nFallDownTime);
    ~CTaskComplexFallAndGetUp() override { }

    static void InjectHooks();

    CTask* Clone() override { return new CTaskComplexFallAndGetUp(m_nFallAnimId, m_nFallAnimGroup, m_nFallDownTime); }
    eTaskType GetId() override { return TASK_COMPLEX_FALL_AND_GET_UP; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);

    CTask* CreateSubTask(eTaskType taskType);
    bool IsFalling();
    void SetDownTime(int nTime);
};

VALIDATE_SIZE(CTaskComplexFallAndGetUp, 0x18);
