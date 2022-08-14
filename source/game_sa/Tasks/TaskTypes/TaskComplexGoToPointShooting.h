#pragma once
#include "TaskComplex.h"

class CTaskComplexGoToPointShooting : public CTaskComplex {
public:
    static void InjectHooks();

    CTaskComplexGoToPointShooting(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5);
    ~CTaskComplexGoToPointShooting();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GO_TO_POINT_SHOOTING;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }

private: // Wrappers for hooks
    // 0x668C70
    CTaskComplexGoToPointShooting* Constructor(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5) {
        this->CTaskComplexGoToPointShooting::CTaskComplexGoToPointShooting(arg0, arg1, arg2, arg3, arg4, arg5);
        return this;
    }

    // 0x0
    CTaskComplexGoToPointShooting* Destructor() {
        this->CTaskComplexGoToPointShooting::~CTaskComplexGoToPointShooting();
        return this;
    }
};
