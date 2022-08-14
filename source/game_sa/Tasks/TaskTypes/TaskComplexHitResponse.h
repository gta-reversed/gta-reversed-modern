#pragma once
#include "TaskComplex.h"

class CTaskComplexHitResponse : public CTaskComplex {
public:
    static void InjectHooks();

    ~CTaskComplexHitResponse();
    CTaskComplexHitResponse(int32 a1);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_HIT_RESPONSE;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x631D70
    CTaskComplexHitResponse* Constructor(int32 a1) {
        this->CTaskComplexHitResponse::CTaskComplexHitResponse(a1);
        return this;
    }

    // 0x631DA0
    CTaskComplexHitResponse* Destructor() {
        this->CTaskComplexHitResponse::~CTaskComplexHitResponse();
        return this;
    }
};
