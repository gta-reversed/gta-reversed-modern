/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "tTransmissionGear.h"

class  cTransmission {
public:
    tTransmissionGear m_aGears[6];
    unsigned char m_nDriveType; // F/R/4
    unsigned char m_nEngineType; // P/D/E
    unsigned char m_nNumberOfGears; // 1 to 6
    char field_4B;
    unsigned int  m_nHandlingFlags;
    float         m_fEngineAcceleration; // 0.1 to 10.0
    float         m_fEngineInertia; // 0.0 to 50.0
    float         m_fMaxGearVelocity; // 5.0 to 150.0
    int field_5C;
    float         m_fMinGearVelocity;
    float         m_fCurrentSpeed;

    cTransmission();
    void InitGearRatios();
    void CalculateGearForSimpleCar(float velocity, unsigned char& currrentGear);
    // it uses printf, so you won't see it actually...
    void DisplayGearRatios();
    float CalculateDriveAcceleration(float& gasPedal, unsigned char& currrentGear, float& gearChangeCount, float& speed, float& unk1, float& unk2, bool allWheelsOnGround, unsigned char handlingType);
};

VALIDATE_SIZE(cTransmission, 0x68);
