#pragma once

#include "TaskComplex.h"

class CVector;
class CVehicle;

class CTaskComplexGoToCarDoorAndStandStill : public CTaskComplex {
public:
    CVehicle*    m_pVehicle;
    int32        f4;
    bool         f14;
    float        f18;
    float        f1C;
    float        f20;
    int32        f24;
    float        f28;
    float        f2C;
    int16        f30;
    int32        m_nDoorId;
    CVector      m_vecPositionToOpenCarDoor;
    int32        f44;
    bool         f48;
    bool         f49;
    CPointRoute* f4C;
    int32        dword44;

public:
    static constexpr auto Type = TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL;

    CTaskComplexGoToCarDoorAndStandStill(CVehicle* vehicle, int32 a3, bool a4, int32 a5, float a6, float a7, float a8, int32 a9);
    ~CTaskComplexGoToCarDoorAndStandStill() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexGoToCarDoorAndStandStill(m_pVehicle, f4, f14, f44, f18, f1C, f20, f24); } // 0x6498B0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    bool IsVehicleInRange(const CPed& ped);
    CVector* ComputeRouteToDoor(const CPed & ped);
    CTask* CreateSubTask(eTaskType taskType, const CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexGoToCarDoorAndStandStill* Constructor(CVehicle* vehicle, int32 a3, bool a4, int32 a5, float a6, float a7, float a8, int32 a9) { this->CTaskComplexGoToCarDoorAndStandStill::CTaskComplexGoToCarDoorAndStandStill(vehicle, a3, a4, a5, a6, a7, a8, a9); return this; }
    CTaskComplexGoToCarDoorAndStandStill* Destructor() { this->CTaskComplexGoToCarDoorAndStandStill::~CTaskComplexGoToCarDoorAndStandStill(); return this; }
};
VALIDATE_SIZE(CTaskComplexGoToCarDoorAndStandStill, 0x54);
