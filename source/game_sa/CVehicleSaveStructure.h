#pragma once
#include "PluginBase.h"
#include "CMatrix.h"
class CVehicle;

class CVehicleSaveStructure
{
public:
    CMatrix   m_matrix;
    uint8_t   field_48;
    uint8_t   m_nPrimaryColor;
    uint8_t   m_nSecondaryColor;
    uint8_t   m_nTertiaryColor;
    uint8_t   m_nQuaternaryColor;
    uint16_t  m_nAlarmState;
    uint8_t   m_nMaxPassengers;
    float     m_fSteerAngle;
    float     m_fGasPedal;
    float     m_fBrakePedal;
    uint32_t  m_nVehicleUpperFlags;
    uint32_t  m_nVehicleLowerFlags;

public:
    static void InjectHooks();

    void Construct(CVehicle* pVeh);
    void Extract(CVehicle* pVeh);
};
VALIDATE_SIZE(CVehicleSaveStructure, 0x68);
