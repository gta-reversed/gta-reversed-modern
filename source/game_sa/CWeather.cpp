/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

float& CWeather::TrafficLightsBrightness = *(float*)0xC812A8;
bool& CWeather::bScriptsForceRain = *(bool*)0xC812AC;
float& CWeather::Earthquake = *(float*)0xC81340;
unsigned int& CWeather::CurrentRainParticleStrength = *(unsigned int*)0xC812B0;
unsigned int& CWeather::LightningStartY = *(unsigned int*)0xC812B4;
unsigned int& CWeather::LightningStartX = *(unsigned int*)0xC812B8;
int& CWeather::LightningFlashLastChange = *(int*)0xC812BC;
int& CWeather::WhenToPlayLightningSound = *(int*)0xC812C0;
unsigned int& CWeather::LightningDuration = *(unsigned int*)0xC812C4;
unsigned int& CWeather::LightningStart = *(unsigned int*)0xC812C8;
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
unsigned int& CWeather::WeatherTypeInList = *(unsigned int*)0xC81310;
short& CWeather::WeatherRegion = *(short*)0xC81314;
short& CWeather::ForcedWeatherType = *(short*)0xC81318;
short& CWeather::NewWeatherType = *(short*)0xC8131C;
short& CWeather::OldWeatherType = *(short*)0xC81320;
CAEWeatherAudioEntity& CWeather::m_WeatherAudioEntity = *(CAEWeatherAudioEntity*)0xC81360;

// Converted from cdecl void CWeather::AddRain(void) 0x72A9A0
void CWeather::AddRain() {
    plugin::Call<0x72A9A0>();
}

// Converted from cdecl void CWeather::AddSandStormParticles(void) 0x72A820
void CWeather::AddSandStormParticles() {
    plugin::Call<0x72A820>();
}

// Converted from cdecl uchar* CWeather::FindWeatherTypesList(void) 0x72A520
unsigned char* CWeather::FindWeatherTypesList() {
    return plugin::CallAndReturn<unsigned char*, 0x72A520>();
}

// Converted from cdecl void CWeather::ForceWeather(short weatherType) 0x72A4E0
void CWeather::ForceWeather(short weatherType) {
    plugin::Call<0x72A4E0, short>(weatherType);
}

// Converted from cdecl void CWeather::ForceWeatherNow(short weatherType) 0x72A4F0
void CWeather::ForceWeatherNow(short weatherType) {
    plugin::Call<0x72A4F0, short>(weatherType);
}

// Converted from cdecl bool CWeather::ForecastWeather(int weatherType,int numSteps) 0x72A590
bool CWeather::ForecastWeather(int weatherType, int numSteps) {
    return plugin::CallAndReturn<bool, 0x72A590, int, int>(weatherType, numSteps);
}

// Converted from cdecl void CWeather::Init(void) 0x72A480
void CWeather::Init() {
    plugin::Call<0x72A480>();
}

// Converted from cdecl void CWeather::ReleaseWeather(void) 0x72A510
void CWeather::ReleaseWeather() {
    plugin::Call<0x72A510>();
}

// Converted from cdecl void CWeather::RenderRainStreaks(void) 0x72AF70
void CWeather::RenderRainStreaks() {
    plugin::Call<0x72AF70>();
}

// Converted from cdecl void CWeather::SetWeatherToAppropriateTypeNow(void) 0x72A790
void CWeather::SetWeatherToAppropriateTypeNow() {
    plugin::Call<0x72A790>();
}

// Converted from cdecl void CWeather::Update(void) 0x72B850
void CWeather::Update() {
    plugin::Call<0x72B850>();
}

// Converted from cdecl void CWeather::UpdateInTunnelness(void) 0x72B630
void CWeather::UpdateInTunnelness() {
    plugin::Call<0x72B630>();
}

// Converted from cdecl void CWeather::UpdateWeatherRegion(CVector *posn) 0x72A640
void CWeather::UpdateWeatherRegion(CVector* posn) {
    plugin::Call<0x72A640, CVector*>(posn);
}

bool CWeather::IsRainy()
{
    return plugin::CallAndReturn<bool, 0x4ABF50>();
}
