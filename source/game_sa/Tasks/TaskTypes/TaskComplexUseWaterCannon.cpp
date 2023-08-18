#include "StdInc.h"

#include "TaskComplexUseWaterCannon.h"

#include "TaskSimpleCarDrive.h"
#include "TaskSimpleCarDriveTimed.h"

void CTaskComplexUseWaterCannon::InjectHooks()
{
    RH_ScopedClass(CTaskComplexUseWaterCannon);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x659780);
    //VTABLE
    RH_ScopedVirtualInstall(Clone, 0x659D10);
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x6597D0);
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x6597C0);
    RH_ScopedVirtualInstall(ControlSubTask, 0x65A640);
}

CTaskComplexUseWaterCannon* CTaskComplexUseWaterCannon::Constructor(CFire* pFire)
{
    this->CTaskComplexUseWaterCannon::CTaskComplexUseWaterCannon(pFire);
    return this;
}

// 0x659780
CTaskComplexUseWaterCannon::CTaskComplexUseWaterCannon(CFire* pFire)
{
    m_pFire = pFire;
}

// 0x65A620
CTaskComplexUseWaterCannon::~CTaskComplexUseWaterCannon()
{
}

// 0x659D10
CTask* CTaskComplexUseWaterCannon::Clone() const {
    return Clone_Reversed();
}

// 0x6597C0
CTask* CTaskComplexUseWaterCannon::CreateNextSubTask(CPed* ped)
{
    return CreateNextSubTask_Reversed(ped);
}

// 0x6597D0
CTask* CTaskComplexUseWaterCannon::CreateFirstSubTask(CPed* ped)
{
    return CreateFirstSubTask_Reversed(ped);
}

// 0x65A640
CTask* CTaskComplexUseWaterCannon::ControlSubTask(CPed* ped)
{
    return ControlSubTask_Reversed(ped);
}

CTask* CTaskComplexUseWaterCannon::Clone_Reversed() const {
    return new CTaskComplexUseWaterCannon(m_pFire);
}

CTask* CTaskComplexUseWaterCannon::CreateNextSubTask_Reversed(CPed* ped)
{
    return nullptr;
}

CTask* CTaskComplexUseWaterCannon::CreateFirstSubTask_Reversed(CPed* ped)
{
    return new CTaskSimpleCarDrive(ped->m_pVehicle, nullptr, false);
}

CTask* CTaskComplexUseWaterCannon::ControlSubTask_Reversed(CPed* ped)
{
    if (m_pSubTask->GetTaskType() == TASK_SIMPLE_CAR_DRIVE)
    {
        if (ped->m_pVehicle->m_nStatus == STATUS_PHYSICS && m_pFire->IsActive())
            ped->m_pVehicle->AsAutomobile()->FireTruckControl(m_pFire);
        else
            return new CTaskSimpleCarDriveTimed(ped->m_pVehicle, 0);
    }

    return m_pSubTask;
}
