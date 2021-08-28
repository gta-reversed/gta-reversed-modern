#pragma once
#include "CTaskSimpleGoTo.h"

class CTaskSimpleGoToPointFine : public CTaskSimpleGoTo 
{
public:
    float m_fBlend;

    static void InjectHooks();
    CTaskSimpleGoToPointFine(float fBlend, CVector targetPoint, float fRadius, int unused);
    ~CTaskSimpleGoToPointFine();
private:
    CTaskSimpleGoToPointFine* Constructor(float fBlend, CVector targetPoint, float fRadius, int unused);
public:
    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_GO_TO_POINT_FINE; };
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    bool ProcessPed(CPed* ped) override;
    
    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);
    bool ProcessPed_Reversed(CPed* ped);

    void SetBlendedMoveAnim(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleGoToPointFine, 0x24);