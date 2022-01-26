#include "StdInc.h"

#include "AEWeatherAudioEntity.h"

#include "AEAudioHardware.h"
#include "AEAudioUtility.h"

float& CAEWeatherAudioEntity::m_sfRainVolume = *(float*)0x8CC30C; // -100.0f

CAETwinLoopSoundEntity& gTwinLoopSoundEntityFirst = *(CAETwinLoopSoundEntity*)0xB6BB18;  // dunno about names
CAETwinLoopSoundEntity& gTwinLoopSoundEntitySecond = *(CAETwinLoopSoundEntity*)0xB6BBC0;

// 0x72A620
CAEWeatherAudioEntity::CAEWeatherAudioEntity() /* missing  : CAEAudioEntity() */ {
    m_nThunderFrequencyVariationCounter = 0;
}

// 0x72A400
CAEWeatherAudioEntity::~CAEWeatherAudioEntity() {
    // NOP
}

// 0x5B9A70
void CAEWeatherAudioEntity::StaticInitialise() {
    AEAudioHardware.LoadSoundBank(105, 6);
}

// 0x5052B0
void CAEWeatherAudioEntity::StaticReset() {
    m_sfRainVolume = -100.0f;

    if (gTwinLoopSoundEntityFirst.m_bIsInitialised)
        gTwinLoopSoundEntityFirst.StopSoundAndForget();

    if (gTwinLoopSoundEntitySecond.m_bIsInitialised)
        gTwinLoopSoundEntitySecond.StopSoundAndForget();
}

// 0x506800, see discord gists channel
void CAEWeatherAudioEntity::AddAudioEvent(eAudioEvents event) {
    plugin::CallMethod<0x506800, CAEWeatherAudioEntity*, eAudioEvents>(this, event);
}

// 0x505A00
void CAEWeatherAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    plugin::CallMethod<0x505A00, CAEWeatherAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
}

// 0x5052F0, see discord gists channel
void CAEWeatherAudioEntity::Service() {
    plugin::CallMethod<0x5052F0, CAEWeatherAudioEntity*>(this);
}

void CAEWeatherAudioEntity::InjectHooks() {
    RH_ScopedClass(CAEWeatherAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x72A620);
    RH_ScopedInstall(Destructor, 0x72A400);
    RH_ScopedInstall(StaticInitialise, 0x5B9A70);
    RH_ScopedInstall(StaticReset, 0x5052B0);
    // RH_ScopedInstall(AddAudioEvent, 0x506800);
    // RH_ScopedInstall(UpdateParameters_Reversed, 0x505A00);
    // RH_ScopedInstall(Service, 0x5052F0);
}

CAEWeatherAudioEntity* CAEWeatherAudioEntity::Constructor() {
    this->CAEWeatherAudioEntity::CAEWeatherAudioEntity();
    return this;
}

CAEWeatherAudioEntity* CAEWeatherAudioEntity::Destructor() {
    this->CAEWeatherAudioEntity::~CAEWeatherAudioEntity();
    return this;
}

void CAEWeatherAudioEntity::UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) {
    CAEWeatherAudioEntity::UpdateParameters(sound, curPlayPos);
}

void WeatherAudioEntityTestCode() {
    CWeather::m_WeatherAudioEntity.AddAudioEvent(AE_THUNDER);
}
