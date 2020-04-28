#pragma once
#include "CTaskSimple.h"
#include "CTaskTimer.h"

class CTaskSimplePause : public CTaskSimple 
{
public:
    CTaskTimer m_timer;
    int m_nTime;

    static void InjectHooks();
    CTaskSimplePause(int time);
    ~CTaskSimplePause();
private:
    CTaskSimplePause* Constructor(int time);
public:

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_PAUSE; };
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    bool ProcessPed(CPed* ped) override;
};

VALIDATE_SIZE(CTaskSimplePause, 0x18);