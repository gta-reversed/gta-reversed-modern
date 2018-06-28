/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVector.h"
#include "CAEWeatherAudioEntity.h"

enum eWeatherType {
    WEATHER_EXTRASUNNY_LA = 0,
    WEATHER_SUNNY_LA = 1,
    WEATHER_EXTRASUNNY_SMOG_LA = 2,
    WEATHER_SUNNY_SMOG_LA = 3,
    WEATHER_CLOUDY_LA = 4,
    WEATHER_SUNNY_SF = 5,
    WEATHER_EXTRASUNNY_SF = 6,
    WEATHER_CLOUDY_SF = 7,
    WEATHER_RAINY_SF = 8,
    WEATHER_FOGGY_SF = 9,
    WEATHER_SUNNY_VEGAS = 10,
    WEATHER_EXTRASUNNY_VEGAS = 11,
    WEATHER_CLOUDY_VEGAS = 12,
    WEATHER_EXTRASUNNY_COUNTRYSIDE = 13,
    WEATHER_SUNNY_COUNTRYSIDE = 14,
    WEATHER_CLOUDY_COUNTRYSIDE = 15,
    WEATHER_RAINY_COUNTRYSIDE = 16,
    WEATHER_EXTRASUNNY_DESERT = 17,
    WEATHER_SUNNY_DESERT = 18,
    WEATHER_SANDSTORM_DESERT = 19,
    WEATHER_UNDERWATER = 20,
    WEATHER_EXTRACOLOURS_1 = 21,
    WEATHER_EXTRACOLOURS_2 = 22
};

enum eWeatherRegion {
    WEATHER_REGION_DEFAULT = 0,
    WEATHER_REGION_LA = 1,
    WEATHER_REGION_SF = 2,
    WEATHER_REGION_LV = 3,
    WEATHER_REGION_DESERT = 4
};

class CWeather {
public:
    static float &TrafficLightsBrightness;
    static bool &bScriptsForceRain;
    static float &Earthquake;
    static unsigned int &CurrentRainParticleStrength;
    static unsigned int &LightningStartY; // only initialized (0), not used
    static unsigned int &LightningStartX; // only initialized (0), not used
    static int &LightningFlashLastChange;
    static int &WhenToPlayLightningSound;
    static unsigned int &LightningDuration;
    static unsigned int &LightningStart; // frame number
    static bool &LightningFlash;
    static bool &LightningBurst;
    static float &HeadLightsSpectrum;
    static float &WaterFogFXControl;
    static float &HeatHazeFXControl;
    static float &HeatHaze;
    static float &SunGlare;
    static float &Rainbow;
    static float &Wavyness;
    static float &WindClipped;
    static CVector &WindDir;
    static float &Wind;
    static float &Sandstorm;
    static float &Rain;
    static float &InTunnelness;
    static float &WaterDepth;
    static float &UnderWaterness;
    static float &ExtraSunnyness;
    static float &Foggyness_SF;
    static float &Foggyness;
    static float &CloudCoverage;
    static float &WetRoads;
    static float &InterpolationValue;
    static unsigned int &WeatherTypeInList;
    static short &WeatherRegion; // see eWeatherRegion
    static short &ForcedWeatherType; // see eWeatherType
    static short &NewWeatherType; // see eWeatherType
    static short &OldWeatherType; // see eWeatherType
    static CAEWeatherAudioEntity &m_WeatherAudioEntity;

    static void AddRain();
    static void AddSandStormParticles();
    static unsigned char* FindWeatherTypesList();
    // for 'weatherType', see eWeatherType
    static void ForceWeather(short weatherType);
    // for 'weatherType', see eWeatherType
    static void ForceWeatherNow(short weatherType);
    // for 'weatherType', see eWeatherType
    static bool ForecastWeather(int weatherType, int numSteps);
    static void Init();
    static void ReleaseWeather();
    static void RenderRainStreaks();
    static void SetWeatherToAppropriateTypeNow();
    static void Update();
    static void UpdateInTunnelness();
    static void UpdateWeatherRegion(CVector* posn);
};