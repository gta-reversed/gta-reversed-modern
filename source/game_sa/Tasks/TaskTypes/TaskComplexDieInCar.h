#pragma once

#include "TaskComplex.h"

class CTaskComplexDieInCar : public CTaskComplex {
public:
    eWeaponType m_nWeaponType;
    uint32      m_nTimeMS;
    uint32      m_nOffset;
    bool        m_bPreparedForDeath;
    bool        m_bUpdateTime;

public:
    explicit CTaskComplexDieInCar(eWeaponType weaponType);

    // 0x62FCF0, 0x6375D0
    ~CTaskComplexDieInCar() override = default;

    eTaskType GetTaskType() override { return TASK_COMPLEX_DIE_IN_CAR; };       // 0x62FCB0
    CTask* Clone() override { return new CTaskComplexDieInCar(m_nWeaponType); } // 0x635F90
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    void PreparePedVehicleForPedDeath(CVehicle* vehicle);

private:
    friend void InjectHooksMain();
    static void InjectHooks() {
        RH_ScopedClass(CTaskComplexDieInCar);
        RH_ScopedCategory("Tasks/TaskTypes");

        RH_ScopedInstall(Clone_Reversed, 0x635F90);
        RH_ScopedInstall(ControlSubTask_Reversed, 0x6377B0);
        RH_ScopedInstall(CreateSubTask, 0x62FD50);
        RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x6375F0);
        RH_ScopedInstall(CreateNextSubTask_Reversed, 0x637850);
        RH_ScopedInstall(MakeAbortable_Reversed, 0x62FCC0);
        RH_ScopedInstall(PreparePedVehicleForPedDeath, 0x62FD00);
    };

    CTask* Clone_Reversed() { return CTaskComplexDieInCar::Clone(); }
    CTask* ControlSubTask_Reversed(CPed* ped) { return CTaskComplexDieInCar::ControlSubTask(ped); }
    CTask* CreateFirstSubTask_Reversed(CPed* ped) { return CTaskComplexDieInCar::CreateFirstSubTask(ped); }
    CTask* CreateNextSubTask_Reversed(CPed* ped) { return CTaskComplexDieInCar::CreateNextSubTask(ped); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) { return CTaskComplexDieInCar::MakeAbortable(ped, priority, event); }
};
