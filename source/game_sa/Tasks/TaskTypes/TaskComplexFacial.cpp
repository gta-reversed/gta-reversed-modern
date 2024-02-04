#include "StdInc.h"

#include "TaskComplexFacial.h"
#include "TaskSimplePause.h"

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
    RH_ScopedVMTInstall(ControlSubTask, 0x690FC0);
}

// 0x690D20
CTaskComplexFacial::CTaskComplexFacial() : CTaskComplex() {
    m_RequestA = eFacialExpression::NONE;
    m_RequestB = eFacialExpression::NONE;
    m_IsNotPlayer = CGeneral::GetRandomNumberInRange(0, 100) > 70;
    m_HasStarted = false;
    m_IsAborting = false;
}

// 0x691250
void CTaskComplexFacial::StopAll() {
    if (m_pSubTask->GetTaskType() == TASK_SIMPLE_FACIAL) {
        m_IsAborting = true;
    }
}

// 0x691230
void CTaskComplexFacial::SetRequest(eFacialExpression type1, int32 duration1, eFacialExpression type2, int32 duration2) {
    m_RequestA = type1;
    m_DurationA         = duration1;

    m_RequestB = type2;
    m_DurationB         = duration2;
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
    if (!ped->IsAlive() && m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_IMMEDIATE)) {
        return new CTaskSimplePause{ 5'000 };
    }
    if (m_IsAborting && m_pSubTask->MakeAbortable(ped)) {
        m_IsAborting = false;
        m_HasStarted = false;
        return new CTaskSimplePause{ 5'000 };
    }
    if (RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_IDLE_CHAT)) {
        m_RequestB   = eFacialExpression::NONE;
        m_HasStarted = true;
        if (!RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_FACTALK)) {
            return new CTaskSimpleFacial{ eFacialExpression::TALKING, 0 };
        }
    }
    if (m_HasStarted && m_pSubTask->MakeAbortable(ped)) {
        m_HasStarted = false;
        return new CTaskSimplePause{ 5'000 };
    }
    if (m_RequestA != eFacialExpression::NONE) {
        const auto requestedFacialType = std::exchange(m_RequestA, eFacialExpression::NONE);
        if (const auto st = CTask::DynCast<CTaskSimpleFacial>(m_pSubTask)) {
            if (st->GetFacialType() == requestedFacialType) {
                st->StartTimer(m_DurationA);
                return m_pSubTask;
            }
        }
        return new CTaskSimpleFacial{ requestedFacialType, m_DurationA };
    }
    return m_pSubTask;
}
