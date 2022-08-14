#pragma once
#include "TaskComplex.h"

class CTaskComplexHitByGunResponse : public CTaskComplex {
public:
    static void InjectHooks();

    ~CTaskComplexHitByGunResponse();
    CTaskComplexHitByGunResponse(int32 a1);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_HIT_BY_GUN_RESPONSE;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x631DD0
    CTaskComplexHitByGunResponse* Constructor(int32 a1) {
        this->CTaskComplexHitByGunResponse::CTaskComplexHitByGunResponse(a1);
        return this;
    }

    // 0x631E30
    CTaskComplexHitByGunResponse* Destructor() {
        this->CTaskComplexHitByGunResponse::~CTaskComplexHitByGunResponse();
        return this;
    }
};
