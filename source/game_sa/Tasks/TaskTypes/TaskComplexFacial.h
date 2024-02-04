#pragma once

#include "TaskComplex.h"
#include "TaskSimpleFacial.h"

class CPed;

class NOTSA_EXPORT_VTABLE CTaskComplexFacial : public CTaskComplex {
public:
    bool              m_IsNotPlayer;
    bool              m_HasStarted;
    bool              m_IsAborting;


    eFacialExpression m_RequestA;
    int32             m_DurationA;

    eFacialExpression m_RequestB;
    int32             m_DurationB;

public:
    static constexpr auto Type = TASK_COMPLEX_FACIAL;

    CTaskComplexFacial();
    ~CTaskComplexFacial() override = default; // 0x690D90

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskComplexFacial(); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    void StopAll();
    void SetRequest(eFacialExpression type1, int32 time1, eFacialExpression type2 = eFacialExpression::NONE, int32 duration2 = -1);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexFacial* Constructor() { this->CTaskComplexFacial::CTaskComplexFacial(); return this; }

};
VALIDATE_SIZE(CTaskComplexFacial, 0x20);
