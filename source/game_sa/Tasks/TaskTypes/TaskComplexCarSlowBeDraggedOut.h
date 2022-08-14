#pragma once
#include "TaskComplex.h"
#include "Vehicle.h"

class CTaskUtilityLineUpPedWithCar;
class CTaskSimpleCarFallOut;

class CTaskComplexCarSlowBeDraggedOut : public CTaskComplex {
public:
    CVehicle* m_car = {}; // 0xC
    int32     m_door = {}; // 0x10
    int8      field_14 = {}; // 0x14
    uint8     field_15[3] = {}; // 0x15
    CTaskUtilityLineUpPedWithCar* m_taskUtilityLineUpPedWithCar = {}; // 0x18

public:
    static void InjectHooks();

    CTaskComplexCarSlowBeDraggedOut(CVehicle* car, int32 a3, bool a4);
    ~CTaskComplexCarSlowBeDraggedOut();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_CAR_SLOW_BE_DRAGGED_OUT;

    CTaskUtilityLineUpPedWithCar* CreateTaskUtilityLineUpPedWithCar(int32 a2);
    CTaskSimpleCarFallOut* CreateSubTask(int32 a2);

    virtual CTask*    Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool      MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask*    CreateNextSubTask(CPed* ped);
    virtual CTask*    CreateFirstSubTask(CPed* ped);
    virtual CTask*    ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x648490
    CTaskComplexCarSlowBeDraggedOut* Constructor(CVehicle* car, int32 a3, bool a4) {
        this->CTaskComplexCarSlowBeDraggedOut::CTaskComplexCarSlowBeDraggedOut(car, a3, a4);
        return this;
    }

    // 0x64C580
    CTaskComplexCarSlowBeDraggedOut* Destructor() {
        this->CTaskComplexCarSlowBeDraggedOut::~CTaskComplexCarSlowBeDraggedOut();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexCarSlowBeDraggedOut, 0x1C);
