#pragma once
#include "CTaskComplex.h"

class CTaskComplexDriveFireTruck : public CTaskComplex
{
public:
    CVehicle* m_pVehicle;
    unsigned char m_bIsDriver;
    unsigned char _pad_11[3];
    CPed* m_pPartnerFireman;
    CFire* m_pFire;

private:
    CTaskComplexDriveFireTruck* Constructor(CVehicle* pVehicle, CPed* pPartnerFireman, bool bIsDriver);
public:
    CTaskComplexDriveFireTruck(CVehicle* pVehicle, CPed* pPartnerFireman, bool bIsDriver);
    ~CTaskComplexDriveFireTruck() override;

    static void InjectHooks();

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_DRIVE_FIRE_TRUCK; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* Clone_Reversed();
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
};

VALIDATE_SIZE(CTaskComplexDriveFireTruck, 0x1C);
