#pragma once
#include "CTaskComplex.h"
#include "CVehicle.h"

class CTaskComplexCarDrive : public CTaskComplex
{
public:
    CTaskComplexCarDrive(plugin::dummy_func_t) : CTaskComplex() {} //TODO: remove
public:
    CVehicle* m_pVehicle;
    float m_fSpeed;
    int field_14;
    int field_18;
    unsigned char field_1C;
    unsigned char m_nbTrafficBehavior;
    unsigned char m_nbDriverBehavior;
    unsigned char field_1F;
    unsigned char m_bSavedVehicleBehavior;
    unsigned char _pad_21[3];

    CTaskComplexCarDrive(CVehicle* vehicle, float arg2, int arg3, int arg4);
    ~CTaskComplexCarDrive();

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_CAR_DRIVE; }

    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    virtual void SetUpCar();
    virtual CTask* CreateSubTaskCannotGetInCar(CPed* ped);
    virtual CTask* Drive(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexCarDrive, 0x24);

