#pragma once

#include "CMatrix.h"
class CVehicle;

class CVehicleSaveStructure {
public:
    CMatrix m_matrix;
    uint8   field_48;
    uint8   m_nPrimaryColor;
    uint8   m_nSecondaryColor;
    uint8   m_nTertiaryColor;
    uint8   m_nQuaternaryColor;
    uint16  m_nAlarmState;
    uint8   m_nMaxPassengers;
    float   m_fSteerAngle;
    float   m_fGasPedal;
    float   m_fBrakePedal;
    uint32  m_nVehicleUpperFlags;
    uint32  m_nVehicleLowerFlags;

public:
    static void InjectHooks();

    void Construct(CVehicle* pVeh);
    void Extract(CVehicle* pVeh);
};
VALIDATE_SIZE(CVehicleSaveStructure, 0x68);
