#pragma once

#include "Vector.h"

class CVehicle;

class CStoredCar {
public:
    CVector m_vPosn;
    uint32  m_nHandlingFlags;
    uint8   m_nStoredCarFlags;
    uint16  m_wModelIndex;
    int16   m_awCarMods[15];
    uint8   m_nPrimaryColor;
    uint8   m_nSecondaryColor;
    uint8   m_nTertiaryColor;
    uint8   m_nQuaternaryColor;
    uint8   m_nRadioStation;
    uint8   m_anCompsToUse[2];
    uint8   m_nBombType;
    uint8   m_nPaintJob;
    uint8   m_nNitroBoosts;
    uint8   m_nPackedForwardX;
    uint8   m_nPackedForwardY;
    uint8   m_nPackedForwardZ;

public:
    static void InjectHooks();

    void      StoreCar(CVehicle* vehicle);
    CVehicle* RestoreCar();

    // NOTSA
    void Init() { m_wModelIndex = 0; }
    void Clear() { m_wModelIndex = 0; }
    bool HasCar() { return m_wModelIndex != 0; }
};
VALIDATE_SIZE(CStoredCar, 0x40);
