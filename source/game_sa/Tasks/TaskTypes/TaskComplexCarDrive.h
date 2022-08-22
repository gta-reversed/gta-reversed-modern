#pragma once

#include "TaskComplex.h"
#include "eCarMission.h"
#include "eCarDrivingStyle.h"

class CVehicle;

enum {
    AS_DRIVER         = 0,
    AS_PASSENGER      = 1,
    ANY_CAR_AS_DRIVER = 2
};

class NOTSA_EXPORT_VTABLE CTaskComplexCarDrive : public CTaskComplex {
public:
    CVehicle* m_pVehicle;
    float     m_fSpeed;
    int32     m_carModelIndexToCreate;
    eCarDrivingStyle m_nCarDrivingStyle;
    int8      _align[3];
    int8      field_1C; //
    int8      m_nOldCarDrivingStyle;
    int8      m_nCarMission;
    uint8     m_nSpeed;
    bool      m_bSavedVehicleBehavior;

public:
    static constexpr auto Type = TASK_COMPLEX_CAR_DRIVE;

    explicit CTaskComplexCarDrive(CVehicle* vehicle);
    CTaskComplexCarDrive(CVehicle* vehicle, float speed, int32 carModelIndexToCreate, eCarDrivingStyle carDrivingStyle);
    ~CTaskComplexCarDrive() override;

    CTask*    Clone() override;
    eTaskType GetTaskType() override { return Type; }

    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType, CPed* ped);

    virtual void   SetUpCar();
    virtual CTask* CreateSubTaskCannotGetInCar(CPed* ped);
    virtual CTask* Drive(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexCarDrive* Constructor_0(CVehicle* vehicle) { this->CTaskComplexCarDrive::CTaskComplexCarDrive(vehicle); return this; }
    CTaskComplexCarDrive* Constructor_1(CVehicle* vehicle, float speed, int32 carModelIndexToCreate, eCarDrivingStyle carDrivingStyle) { this->CTaskComplexCarDrive::CTaskComplexCarDrive(vehicle, speed, carModelIndexToCreate, carDrivingStyle); return this; }
    CTaskComplexCarDrive* Destructor() { this->CTaskComplexCarDrive::~CTaskComplexCarDrive(); return this; }
    CTask* Clone_Reversed() { return CTaskComplexCarDrive::Clone(); }
    CTask* CreateNextSubTask_Reversed(CPed* ped) { return CTaskComplexCarDrive::CreateNextSubTask(ped); }
    CTask* CreateFirstSubTask_Reversed(CPed* ped) { return CTaskComplexCarDrive::CreateFirstSubTask(ped); }
    CTask* ControlSubTask_Reversed(CPed* ped) { return CTaskComplexCarDrive::ControlSubTask(ped); }
    CTask* CreateSubTask_Reversed(eTaskType taskType, CPed* ped) { return CTaskComplexCarDrive::CreateSubTask(taskType, ped); }
    void   SetUpCar_Reversed() { CTaskComplexCarDrive::SetUpCar(); }
    CTask* CreateSubTaskCannotGetInCar_Reversed(CPed* ped) { return CTaskComplexCarDrive::CreateSubTaskCannotGetInCar(ped); }
    CTask* Drive_Reversed(CPed* ped) { return CTaskComplexCarDrive::Drive(ped); }
};
VALIDATE_SIZE(CTaskComplexCarDrive, 0x24);
