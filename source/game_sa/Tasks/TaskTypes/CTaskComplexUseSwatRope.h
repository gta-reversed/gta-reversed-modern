#pragma once
#include "CTaskComplex.h"
#include "CHeli.h"

class CTaskComplexUseSwatRope : public CTaskComplex
{
public:
    unsigned int m_nRopeId;
    float m_fCoorAlongRope;
    unsigned char m_bIsOnHeli;
    unsigned char _pad_15[3];
    CHeli* m_pHeli;
private:
    CTaskComplexUseSwatRope* Constructor(unsigned int ropeId, CHeli* pHeli);
public:
    CTaskComplexUseSwatRope(unsigned int ropeId, CHeli* pHeli);
    CTaskComplexUseSwatRope(unsigned int ropeId);
    ~CTaskComplexUseSwatRope() override;

    static void InjectHooks();

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_USE_SWAT_ROPE; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
    virtual bool IsInterruptable(CPed* ped) { return false; }
    virtual bool AbortUrgently(CPed* ped) { return false; }
};

VALIDATE_SIZE(CTaskComplexUseSwatRope, 0x1C);
