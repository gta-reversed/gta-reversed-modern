#pragma once

#include "CTaskComplex.h"
#include "CVehicle.h"
#include "CAccident.h"
class CTaskComplexMedicTreatInjuredPed : public CTaskComplex
{
public:
    CVehicle* m_pVehicle;
    CPed* m_pPartnerMedic;
    uint8 m_bIsDriver;
    char _pad[3];
    CAccident* m_pAccident;
    CVector m_vecAccidentPosition;
    uint8 m_bLeftCarOnce;
    char _pad2[3];


    static void InjectHooks();
    CTaskComplexMedicTreatInjuredPed(CVehicle* vehicle, CPed* ped, uint8 isDriver);
    ~CTaskComplexMedicTreatInjuredPed();
private:
    CTaskComplexMedicTreatInjuredPed* Constructor(CVehicle* vehicle, CPed* ped, uint8 isDriver);
public:

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_MEDIC_TREAT_INJURED_PED; };
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* Clone_Reversed();
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);

    CTask* CreateSubTask(eTaskType taskType);
    CTask* CreateDealWithNextAccidentTask(CPed* ped, CAccident* accident);
    void FindNearestAccident(CVector& posn);
    void FindAccidentPosition(CPed* ped, CPed* targetPed);
};

VALIDATE_SIZE(CTaskComplexMedicTreatInjuredPed, 0x2C);

