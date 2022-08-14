#pragma once
#include "TaskComplex.h"

class CVehicle;
class CEvent;

class CTaskComplexCarSlowBeDraggedOutAndStandUp : public CTaskComplex {
public:
    static void InjectHooks();

    CTaskComplexCarSlowBeDraggedOutAndStandUp(CVehicle* veh, int32 a3);
    ~CTaskComplexCarSlowBeDraggedOutAndStandUp();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_CAR_SLOW_BE_DRAGGED_OUT_AND_STAND_UP;

    void CreateSubTask(int32 a2, CPed* a3);

    virtual CTask*    Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool      MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask*    CreateNextSubTask(CPed* ped);
    virtual CTask*    CreateFirstSubTask(CPed* ped);
    virtual CTask*    ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x648620
    CTaskComplexCarSlowBeDraggedOutAndStandUp* Constructor(CVehicle* veh, int32 a3) {
        this->CTaskComplexCarSlowBeDraggedOutAndStandUp::CTaskComplexCarSlowBeDraggedOutAndStandUp(veh, a3);
        return this;
    }

    // 0x648690
    CTaskComplexCarSlowBeDraggedOutAndStandUp* Destructor() {
        this->CTaskComplexCarSlowBeDraggedOutAndStandUp::~CTaskComplexCarSlowBeDraggedOutAndStandUp();
        return this;
    }
};
