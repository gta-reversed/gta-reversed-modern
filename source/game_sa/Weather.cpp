/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "eWeatherType.h"
#include "game_sa/Data/Weather.def"

float& CWeather::TrafficLightsBrightness = *(float*)0xC812A8;
bool& CWeather::bScriptsForceRain = *(bool*)0xC812AC;
float& CWeather::Earthquake = *(float*)0xC81340;
uint32& CWeather::CurrentRainParticleStrength = *(uint32*)0xC812B0;
uint32& CWeather::LightningStartY = *(uint32*)0xC812B4;
uint32& CWeather::LightningStartX = *(uint32*)0xC812B8;
int32& CWeather::LightningFlashLastChange = *(int32*)0xC812BC;
int32& CWeather::WhenToPlayLightningSound = *(int32*)0xC812C0;
uint32& CWeather::LightningDuration = *(uint32*)0xC812C4;
uint32& CWeather::LightningStart = *(uint32*)0xC812C8;
bool& CWeather::LightningFlash = *(bool*)0xC812CC;
bool& CWeather::LightningBurst = *(bool*)0xC812CD;
float& CWeather::HeadLightsSpectrum = *(float*)0xC812D0;
float& CWeather::WaterFogFXControl = *(float*)0xC81338;
float& CWeather::HeatHazeFXControl = *(float*)0xC812D8;
float& CWeather::HeatHaze = *(float*)0xC812DC;
float& CWeather::SunGlare = *(float*)0xC812E0;
float& CWeather::Rainbow = *(float*)0xC812E4;
float& CWeather::Wavyness = *(float*)0xC812E8;
float& CWeather::WindClipped = *(float*)0xC812EC;
CVector& CWeather::WindDir = *(CVector*)0xC813E0;
float& CWeather::Wind = *(float*)0xC812F0;
float& CWeather::Sandstorm = *(float*)0xC812F4;
float& CWeather::Rain = *(float*)0xC81324;
float& CWeather::InTunnelness = *(float*)0xC81334;
float& CWeather::WaterDepth = *(float*)0xC81330;
float& CWeather::UnderWaterness = *(float*)0xC8132C;
float& CWeather::ExtraSunnyness = *(float*)0xC812F8;
float& CWeather::Foggyness_SF = *(float*)0xC812FC;
float& CWeather::Foggyness = *(float*)0xC81300;
float& CWeather::CloudCoverage = *(float*)0xC81304;
float& CWeather::WetRoads = *(float*)0xC81308;
float& CWeather::InterpolationValue = *(float*)0xC8130C;
uint32& CWeather::WeatherTypeInList = *(uint32*)0xC81310;
eWeatherRegion& CWeather::WeatherRegion = *(eWeatherRegion*)0xC81314;
eWeatherType& CWeather::ForcedWeatherType = *(eWeatherType*)0xC81318;
eWeatherType& CWeather::NewWeatherType = *(eWeatherType*)0xC8131C;
eWeatherType& CWeather::OldWeatherType = *(eWeatherType*)0xC81320;
CAEWeatherAudioEntity& CWeather::m_WeatherAudioEntity = *(CAEWeatherAudioEntity*)0xC81360;
bool& CWeather::StreamAfterRainTimer = *(bool*)0x8D5EAC;

float(&CWeather::saTreeWindOffsets)[16] = *(float(*)[16])0x8CCF30;
float(&CWeather::saBannerWindOffsets)[32] = *(float(*)[32])0x8CCF70;


void CWeather::InjectHooks() {
    ReversibleHooks::Install("CWeather", "Init", 0x72A480, &CWeather::Init);
//    ReversibleHooks::Install("CWeather", "AddRain", 0x72A9A0, &CWeather::AddRain);
//    ReversibleHooks::Install("CWeather", "AddSandStormParticles", 0x72A820, &CWeather::AddSandStormParticles);
    ReversibleHooks::Install("CWeather", "FindWeatherTypesList", 0x72A520, &CWeather::FindWeatherTypesList);
    ReversibleHooks::Install("CWeather", "ForceWeather", 0x72A4E0, &CWeather::ForceWeather);
    ReversibleHooks::Install("CWeather", "ForceWeatherNow", 0x72A4F0, &CWeather::ForceWeatherNow);
//    ReversibleHooks::Install("CWeather", "ForecastWeather", 0x72A590, &CWeather::ForecastWeather);
    ReversibleHooks::Install("CWeather", "ReleaseWeather", 0x72A510, &CWeather::ReleaseWeather);
//    ReversibleHooks::Install("CWeather", "RenderRainStreaks", 0x72AF70, &CWeather::RenderRainStreaks);
    ReversibleHooks::Install("CWeather", "SetWeatherToAppropriateTypeNow", 0x72A790, &CWeather::SetWeatherToAppropriateTypeNow);
//    ReversibleHooks::Install("CWeather", "Update", 0x72B850, &CWeather::Update);
//    ReversibleHooks::Install("CWeather", "UpdateInTunnelness", 0x72B630, &CWeather::UpdateInTunnelness);
    ReversibleHooks::Install("CWeather", "UpdateWeatherRegion", 0x72A640, &CWeather::UpdateWeatherRegion);
    ReversibleHooks::Install("CWeather", "IsRainy", 0x4ABF50, &CWeather::IsRainy);
}

// 0x72A480
void CWeather::Init() {
    NewWeatherType = WEATHER_EXTRASUNNY_LA;
    OldWeatherType = WEATHER_EXTRASUNNY_LA;
    WeatherRegion = WEATHER_REGION_DEFAULT;
    InterpolationValue = 0.0f;
    WeatherTypeInList = 0;
    ForcedWeatherType = WEATHER_UNDEFINED;
    WhenToPlayLightningSound = 0;
    bScriptsForceRain = false;
    Rain = 0.0f;
    Sandstorm = 0.0f;
    CurrentRainParticleStrength = 0;
    InTunnelness = 0.0f;
    LightningStartX = 0;
    LightningStartY = 0;
    StreamAfterRainTimer = false;
}

// 0x72A9A0
void CWeather::AddRain() {
    plugin::Call<0x72A9A0>();
}

// 0x72A820
void CWeather::AddSandStormParticles() {
    plugin::Call<0x72A820>();
}

// 0x72A520
const eWeatherType* CWeather::FindWeatherTypesList() {
    switch (WeatherRegion) {
    case WEATHER_REGION_LA:
        return WeatherTypesListLA;
    case WEATHER_REGION_SF:
        return WeatherTypesListSF;
    case WEATHER_REGION_LV:
        return WeatherTypesListVegas;
    case WEATHER_REGION_DESERT:
        return WeatherTypesListDesert;
    default:
        return WeatherTypesListDefault;
    }
}

// 0x72A4E0
void CWeather::ForceWeather(eWeatherType weatherType) {
    ForcedWeatherType = weatherType;
}

// 0x72A4F0
void CWeather::ForceWeatherNow(eWeatherType weatherType) {
  ForcedWeatherType = weatherType;
  OldWeatherType = weatherType;
  NewWeatherType = weatherType;
}

// 0x72A590
bool CWeather::ForecastWeather(eWeatherType weatherType, int32 numSteps) {
    return plugin::CallAndReturn<bool, 0x72A590, int32, int32>(weatherType, numSteps);
}

// 0x72A510
void CWeather::ReleaseWeather() {
    ForcedWeatherType = WEATHER_UNDEFINED;
}

// 0x72AF70
void CWeather::RenderRainStreaks() {
    plugin::Call<0x72AF70>();
}

// 0x72A790
void CWeather::SetWeatherToAppropriateTypeNow() {
    CVector playerCoors = FindPlayerCoors(-1);
    UpdateWeatherRegion(&playerCoors);

    auto weatherType = static_cast<eWeatherType>(*FindWeatherTypesList());
    ForcedWeatherType = WEATHER_UNDEFINED;
    OldWeatherType = weatherType;
    NewWeatherType = weatherType;
}

// 0x72B850
void CWeather::Update() {
    plugin::Call<0x72B850>();
}

// 0x72B630
void CWeather::UpdateInTunnelness() {
    plugin::Call<0x72B630>();
}

// 0x72A640
void CWeather::UpdateWeatherRegion(CVector* posn) {
    CVector vecPos = TheCamera.GetPosition();
    if (posn) {
        vecPos = *posn;
    }
    if (vecPos.x > 1000.0f && vecPos.y > 910.0f) {
        WeatherRegion = WEATHER_REGION_LV;
        return;
    }
    if (vecPos.x > -850.0f && vecPos.x < 1000.0f && vecPos.y > 1280.0f) {
        WeatherRegion = WEATHER_REGION_DESERT;
        return;
    }
    if (vecPos.x < -1430.0f && vecPos.y > 580.0f && vecPos.y < 1430.0f) {
        WeatherRegion = WEATHER_REGION_SF;
        return;
    }
    if (vecPos.x > 250.0f && vecPos.x < 3000.0f && vecPos.y > -3000.0f && vecPos.y < -850.0f) {
        WeatherRegion = WEATHER_REGION_LA;
        return;
    }
    WeatherRegion = WEATHER_REGION_DEFAULT;
}

// 0x4ABF50
bool CWeather::IsRainy() {
    return Rain >= 0.2f;
}
