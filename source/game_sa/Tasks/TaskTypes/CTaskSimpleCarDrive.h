#pragma once
#include "PluginBase.h"
#include "CTaskSimple.h"

class CVehicle;
class CTaskUtilityLineUpPedWithCar;

class CTaskSimpleCarDrive : public CTaskSimple
{
    CTaskSimpleCarDrive() = delete;
public:
    CVehicle* m_pVehicle;
    int field_C;
    CTaskUtilityLineUpPedWithCar* m_pTaskUtilityLineUpPedWithCar;
    int field_14;
    int field_18;
    char field_1C;
    char field_1D;
    char field_1E[2];
    int m_nBoppingStartTime;
    int field_24;
    int m_nBoppingEndTime;
    float m_fBoppingProgress;// 0.0 to 1.0
    int m_nBoppingCompletedTimes;
    int m_nHeadBoppingStartTime;
    int m_nHeadBoppingDirection;
    float m_fHeadBoppingOrientation;
    float m_fRandomHeadBoppingMultiplier;
    float m_fHeadBoppingFactor;
    int m_nArmBoppingStartTime;
    int m_nTimePassedSinceCarUpSideDown;
    CTaskTimer m_copCarStolenTimer;
    union {
        struct {
            std::uint8_t m_b01 : 1;
            std::uint8_t m_b02 : 1;
            std::uint8_t m_bUpdateCurrentVehicle : 1; // updates m_pVehicle pointer to the current occupied vehicle by ped
            std::uint8_t m_b04 : 1;
        };
        std::uint8_t m_nFlags;
    };
private:
    char padding[3];
public:
    CTaskSimpleCarDrive* Constructor(CVehicle* pVehicle, CTaskUtilityLineUpPedWithCar* pUtilityTask, bool bUpdateCurrentVehicle);
};

VALIDATE_SIZE(CTaskSimpleCarDrive, 0x60);
