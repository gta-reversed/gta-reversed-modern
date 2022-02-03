/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AEAudioEntity.h"

class CAEWeatherAudioEntity : public CAEAudioEntity {
public:
    uint8 m_nThunderFrequencyVariationCounter;
    char  _pad7D[3];

    static float& m_sfRainVolume;

public:
    CAEWeatherAudioEntity();
    ~CAEWeatherAudioEntity();

    static void StaticInitialise();
    static void StaticReset();

    void AddAudioEvent(eAudioEvents event);
    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;
    void Service();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEWeatherAudioEntity* Constructor();
    CAEWeatherAudioEntity* Destructor();
    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
};

VALIDATE_SIZE(CAEWeatherAudioEntity, 0x80);

void WeatherAudioEntityTestCode();
