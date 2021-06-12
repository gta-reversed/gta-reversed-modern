#include "StdInc.h"

void CTaskComplexUseWaterCannon::InjectHooks()
{
    ReversibleHooks::Install("CTaskComplexUseWaterCannon", "Constructor", 0x659780, &CTaskComplexUseWaterCannon::Constructor);
    //VTABLE
    ReversibleHooks::Install("CTaskComplexUseWaterCannon", "Clone", 0x659D10, &CTaskComplexUseWaterCannon::Clone_Reversed);
    ReversibleHooks::Install("CTaskComplexUseWaterCannon", "CreateFirstSubTask", 0x6597D0, &CTaskComplexUseWaterCannon::CreateFirstSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexUseWaterCannon", "CreateNextSubTask", 0x6597C0, &CTaskComplexUseWaterCannon::CreateNextSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexUseWaterCannon", "ControlSubTask", 0x65A640, &CTaskComplexUseWaterCannon::ControlSubTask_Reversed);
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
CTask* CTaskComplexUseWaterCannon::Clone()
{
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

CTask* CTaskComplexUseWaterCannon::Clone_Reversed()
{
    return new CTaskComplexUseWaterCannon(m_pFire);
}

CTask* CTaskComplexUseWaterCannon::CreateNextSubTask_Reversed(CPed* ped)
{
    return nullptr;
}

CTask* CTaskComplexUseWaterCannon::CreateFirstSubTask_Reversed(CPed* ped)
{
    return new CTaskSimpleCarDrive(ped->m_pVehicle, 0, false);
}

CTask* CTaskComplexUseWaterCannon::ControlSubTask_Reversed(CPed* ped)
{
    if (m_pSubTask->GetId() == TASK_SIMPLE_CAR_DRIVE)
    {
        if (ped->m_pVehicle->m_nStatus == STATUS_PHYSICS && m_pFire->m_nFlags.bActive)
            ped->m_pVehicle->AsAutomobile()->FireTruckControl(m_pFire);
        else
            return new CTaskSimpleCarDriveTimed(ped->m_pVehicle, 0);
    }

    return m_pSubTask;
}
