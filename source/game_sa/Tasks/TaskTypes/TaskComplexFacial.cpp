#include "StdInc.h"

#include "TaskComplexFacial.h"

void CTaskComplexFacial::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexFacial, 0x870ADC, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x690D20);

    RH_ScopedInstall(SetRequest, 0x691230);
    RH_ScopedInstall(StopAll, 0x691250);
    RH_ScopedVMTInstall(Clone, 0x6928B0, { .reversed = false });
    RH_ScopedVMTInstall(GetTaskType, 0x690D80, { .reversed = false });
    RH_ScopedVMTInstall(MakeAbortable, 0x690DA0);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x690DC0, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x690F30, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x690FC0, { .reversed = false });
}

// 0x690D20
CTaskComplexFacial::CTaskComplexFacial() : CTaskComplex() {
    m_nFacialExpression1 = eFacialExpression::NONE;
    m_nFacialExpression2 = eFacialExpression::NONE;
    m_bNotPlayer = CGeneral::GetRandomNumberInRange(0, 100) > 70;
    m_bStarted = false;
    m_bIsAborting = false;
}

// 0x691250
void CTaskComplexFacial::StopAll() {
    if (m_pSubTask->GetTaskType() == TASK_SIMPLE_FACIAL) {
        m_bIsAborting = true;
    }
}

// 0x691230
void CTaskComplexFacial::SetRequest(eFacialExpression type1, int32 duration1, eFacialExpression type2, int32 duration2) {
    m_nFacialExpression1 = type1;
    m_nDuration1         = duration1;

    m_nFacialExpression2 = type2;
    m_nDuration2         = duration2;
}

// 0x690DA0
bool CTaskComplexFacial::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return priority == ABORT_PRIORITY_IMMEDIATE && m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_IMMEDIATE, event);
}

// 0x690DC0
CTask* CTaskComplexFacial::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690DC0, CTaskComplexFacial*, CPed*>(this, ped);
}

// 0x690F30
CTask* CTaskComplexFacial::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690F30, CTaskComplexFacial*, CPed*>(this, ped);
}

// 0x690FC0
CTask* CTaskComplexFacial::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690FC0, CTaskComplexFacial*, CPed*>(this, ped);
}
