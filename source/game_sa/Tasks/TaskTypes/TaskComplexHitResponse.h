#pragma once

#include "TaskComplex.h"

class CTaskComplexHitResponse : public CTaskComplex {
public:
    int32 m_Direction;

public:
    static constexpr auto Type = TASK_COMPLEX_HIT_RESPONSE;

    explicit CTaskComplexHitResponse(int32 direction);
    ~CTaskComplexHitResponse() override = default; // 0x631DA0

    eTaskType GetTaskType() const override { return Type; } // 0x631D90
    CTask* Clone() const override { return new CTaskComplexHitResponse(m_Direction); } // 0x6365E0
    CTask* CreateNextSubTask(CPed* ped) override { return nullptr; } // 0x631DB0
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override { return m_pSubTask; } // 0x631DC0

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexHitResponse* Constructor(int32 a1) { this->CTaskComplexHitResponse::CTaskComplexHitResponse(a1); return this; }
    CTaskComplexHitResponse* Destructor() { this->CTaskComplexHitResponse::~CTaskComplexHitResponse(); return this; }
};
