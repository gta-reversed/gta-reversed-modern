/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "tTransmissionGear.h"

const float TRANSMISSION_FREE_ACCELERATION = 0.1f;
const float TRANSMISSION_SMOOTHER_FRAC = 0.85f;
const float TRANSMISSION_AI_CHEAT_MULT = 1.2f;
const float TRANSMISSION_NITROS_MULT = 2.0f;
const float TRANSMISSION_AI_CHEAT_INERTIA_MULT = 0.75f;
const float TRANSMISSION_NITROS_INERTIA_MULT = 0.5f;


enum
{
    CHEAT_HANDLING_NONE = 0,
    CHEAT_HANDLING_PERFECT = 1,
    CHEAT_HANDLING_NITROS = 2
};

class cTransmission {
public:
    tTransmissionGear m_aGears[6];
    unsigned char m_nDriveType; // F/R/4
    unsigned char m_nEngineType; // P/D/E
    std::uint8_t m_nNumberOfGears; // 1 to 6
    char field_4B;
    std::uint32_t m_handlingFlags;
    float         m_fEngineAcceleration; // 0.1 to 10.0
    float         m_fEngineInertia; // 0.0 to 50.0
    float         m_fMaxGearVelocity; // 5.0 to 150.0
    int field_5C;
    float         m_maxReverseGearVelocity;
    float m_currentVelocity;

    static void InjectHooks();

    cTransmission() {}
    void DisplayGearRatios();
    void InitGearRatios();
    void CalculateGearForSimpleCar(float speed, uint8_t& currentGear);
    float CalculateDriveAcceleration(float const& gasPedal, uint8_t& currentGear, float& gearChangeCount, float& velocity, float* a6, float* a7, uint8_t allWheelsOnGround, uint8_t handlingType);
};

VALIDATE_SIZE(cTransmission, 0x68);
