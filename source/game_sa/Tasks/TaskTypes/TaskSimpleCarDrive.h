#pragma once

#include "TaskSimple.h"

class CVehicle;
class CTaskUtilityLineUpPedWithCar;

class CTaskSimpleCarDrive : public CTaskSimple {
public:
    CVehicle*                     m_pVehicle;
    CAnimBlendAssociation*        m_pAnimCloseDoorRolling;
    CTaskUtilityLineUpPedWithCar* m_pTaskUtilityLineUpPedWithCar;
    int32                         field_14;
    int32                         field_18;
    char                          field_1C;
    char                          field_1D;
    char                          field_1E[2];
    int32                         m_nBoppingStartTime;
    int32                         field_24;
    int32                         m_nBoppingEndTime;
    float                         m_fBoppingProgress; // 0.0 to 1.0
    int32                         m_nBoppingCompletedTimes;
    int32                         m_nHeadBoppingStartTime;
    int32                         m_nHeadBoppingDirection;
    float                         m_fHeadBoppingOrientation;
    float                         m_fRandomHeadBoppingMultiplier;
    float                         m_fHeadBoppingFactor;
    int32                         m_nArmBoppingStartTime;
    int32                         m_nTimePassedSinceCarUpSideDown;
    CTaskTimer                    m_copCarStolenTimer;
    union {
        struct {
            uint8 m_b01 : 1;
            uint8 m_b02 : 1;
            uint8 m_bUpdateCurrentVehicle : 1; // updates m_pVehicle pointer to the current occupied vehicle by ped
            uint8 m_b04 : 1;
        };
        uint8 m_nFlags;
    };
    char _pad[3];

public:
    static constexpr auto Type = TASK_SIMPLE_CAR_DRIVE;

    CTaskSimpleCarDrive() = delete;

    CTaskSimpleCarDrive(CVehicle* vehicle, CTaskUtilityLineUpPedWithCar* utilityTask = {}, bool updateCurrentVehicle = {});

    eTaskType GetTaskType() override { return TASK_SIMPLE_CAR_DRIVE; }
    CTask* Clone() override;
    bool ProcessPed(class CPed* ped) override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override;

    auto GetVehicle() const { return m_pVehicle; }
private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleCarDrive* Constructor(CVehicle* vehicle, CTaskUtilityLineUpPedWithCar* utilityTask, bool updateCurrentVehicle);
};

VALIDATE_SIZE(CTaskSimpleCarDrive, 0x60);
