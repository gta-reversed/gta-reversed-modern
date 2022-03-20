#pragma once

#include "TaskComplexCarDrive.h"
#include "Enums/eCarMission.h"
#include "Enums/eCarDrivingStyle.h"

class CVehicle;

class CTaskComplexCarDriveMission : public CTaskComplexCarDrive {
public:
    CEntity* m_targetEntity = {};   // 0x24
    uint32   m_carMission = {};      // 0x28 - eCarMission (Sadly we can't use it as the type because it's underlaying type isn't uint32) (TODO)

public:
    static constexpr auto Type = TASK_COMPLEX_CAR_DRIVE_MISSION;

    static void InjectHooks();

    CTaskComplexCarDriveMission(CVehicle* pVehicle, CEntity* targetEntity, eCarMission carDriveMission, eCarDrivingStyle carDrivingStyle, float fSpeed);
    CTaskComplexCarDriveMission(const CTaskComplexCarDriveMission&); // NOTSA: `Clone()` helper
    ~CTaskComplexCarDriveMission() override = default;

    CTask* Clone() override { return new CTaskComplexCarDriveMission{ *this }; }
    eTaskType GetTaskType() override { return Type; }
    void SetUpCar() override;

private: // Wrappers for hooks
    CTaskComplexCarDriveMission* Constructor(CVehicle * pVehicle, CEntity* targetEntity, eCarMission carDriveMission, eCarDrivingStyle carDrivingStyle, float fSpeed) {
        this->CTaskComplexCarDriveMission::CTaskComplexCarDriveMission(pVehicle, targetEntity, carDriveMission, carDrivingStyle, fSpeed);
        return this;
    }

    CTaskComplexCarDriveMission* Destructor() {
        this->CTaskComplexCarDriveMission::~CTaskComplexCarDriveMission();
        return this;
    }

    CTask* Clone_Reversed() { return CTaskComplexCarDriveMission::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskComplexCarDriveMission::GetTaskType(); }
    void SetUpCar_Reversed() { return CTaskComplexCarDriveMission::SetUpCar(); }
};
VALIDATE_SIZE(CTaskComplexCarDriveMission, 0x2C);
