#pragma once
#include "TaskComplex.h"
#include "TaskComplexGoToPointAndStandStill.h"

class CTaskComplexGoToPointAiming : public CTaskComplex {
public:
    static void InjectHooks();

    ~CTaskComplexGoToPointAiming();
    CTaskComplexGoToPointAiming(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5);

    CTaskComplexGoToPointAndStandStill* CreateSubTask(int32 a2);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GO_TO_POINT_AIMING;
    
    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x668790
    CTaskComplexGoToPointAiming* Constructor(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5) {
        this->CTaskComplexGoToPointAiming::CTaskComplexGoToPointAiming(arg0, arg1, arg2, arg3, arg4, arg5);
        return this;
    }

    // 0x668870
    CTaskComplexGoToPointAiming* Destructor() {
        this->CTaskComplexGoToPointAiming::~CTaskComplexGoToPointAiming();
        return this;
    }
};
