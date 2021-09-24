#pragma once

#include "CTaskComplex.h"
#include "CVehicle.h"
#include "CAccident.h"

class CTaskComplexMedicTreatInjuredPed : public CTaskComplex {
public:
    CVehicle*  m_pVehicle;
    CPed*      m_pPartnerMedic;
    uint8      m_bIsDriver;
    char       _pad[3];
    CAccident* m_pAccident;
    CVector    m_vecAccidentPosition;
    uint8      m_bLeftCarOnce;
    char       _pad2[3];

public:
    CTaskComplexMedicTreatInjuredPed(CVehicle* vehicle, CPed* ped, bool isDriver);
    ~CTaskComplexMedicTreatInjuredPed();

    CTask*    Clone() override;
    eTaskType GetTaskType() override { return TASK_COMPLEX_MEDIC_TREAT_INJURED_PED; };
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* CreateSubTask(eTaskType taskType);
    CTask* CreateDealWithNextAccidentTask(CPed* ped, CAccident* accident);
    void   FindNearestAccident(CVector& posn);
    void   FindAccidentPosition(CPed* ped, CPed* targetPed);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexMedicTreatInjuredPed* Constructor(CVehicle* vehicle, CPed* ped, bool isDriver);

    CTask* Clone_Reversed();
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexMedicTreatInjuredPed, 0x2C);
