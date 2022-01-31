#pragma once

#include "Vector.h"

class CVehicle;

class CStoredCar {
public:

    CVector  m_vPosn;
    uint32 m_dwHandlingFlags;
    uint8  m_nStoredCarFlags;
    uint8  _pad0;
    uint16 m_wModelIndex;
    int16  m_awCarMods[15];
    uint8  m_nPrimaryColor;
    uint8  m_nSecondaryColor;
    uint8  m_nTertiaryColor;
    uint8  m_nQuaternaryColor;
    uint8  m_nRadiostation;
    uint8  m_anCompsToUse[2];
    uint8  m_nBombType;
    uint8  m_nPaintjob;
    uint8  m_nNitroBoosts;
    uint8  m_nPackedForwardX;
    uint8  m_nPackedForwardY;
    uint8  m_nPackedForwardZ;
    uint8  _pad1;

public:
    static void InjectHooks();

    CVehicle* RestoreCar();
    void      StoreCar(CVehicle* pVehicle);

    // NOTSA
    void Init() { m_wModelIndex = 0; }
    void Clear() { m_wModelIndex = 0; }
    bool HasCar() { return m_wModelIndex != 0; }
};
VALIDATE_SIZE(CStoredCar, 0x40);
