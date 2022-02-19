#pragma once

#include "TaskComplex.h"
#include "TaskSimpleFacial.h"

class CPed;

class CTaskComplexFacial : public CTaskComplex {
public:
    bool              m_bNotPlayer;
    bool              m_bStarted;
    bool              m_bIsAborting;

    // TODO: Should probably make a struct of this then an array of it.
    eFacialExpression m_nFacialExpression1;
    int32             m_nDuration1;

    eFacialExpression m_nFacialExpression2;
    int32             m_nDuration2;
    
public:
    static void InjectHooks();

    ~CTaskComplexFacial() override;
    CTaskComplexFacial();

    void StopAll();

    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_COMPLEX_FACIAL; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private:
    CTaskComplexFacial* Constructor();
    CTaskComplexFacial* Destructor();

    // Virtual wrappers for hooks
    CTask* Clone_Reversed() { return CTaskComplexFacial::Clone(); }
    int32  GetTaskType_Reversed() { return CTaskComplexFacial::GetTaskType(); }
    bool   MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskComplexFacial::MakeAbortable(ped, priority, event); }
    CTask* CreateNextSubTask_Reversed(CPed* ped) { return CTaskComplexFacial::CreateNextSubTask(ped); }
    CTask* CreateFirstSubTask_Reversed(CPed* ped) { return CTaskComplexFacial::CreateFirstSubTask(ped); }
    CTask* ControlSubTask_Reversed(CPed* ped) { return CTaskComplexFacial::ControlSubTask(ped); }
};
VALIDATE_SIZE(CTaskComplexFacial, 0x20);
