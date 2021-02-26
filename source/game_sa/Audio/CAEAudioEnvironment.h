#pragma once
#include "CVector.h"
class CPlaceable;

struct sReverbEnvironment
{
    unsigned int m_nEnvironment;
    signed int m_nDepth;
};

class CAEAudioEnvironment
{
public:
    static void InjectHooks();

    static float GetDopplerRelativeFrequency(float prevDist, float curDist, unsigned int prevTime, unsigned int curTime, float timeScale);
    static float GetDistanceAttenuation(float dist);
    static float GetDirectionalMikeAttenuation(CVector const& soundDir);
    static void GetReverbEnvironmentAndDepth(signed char* reverbEnv, int* depth);
    static void GetPositionRelativeToCamera(CVector* vecOut, CVector* vecPos);
    static void GetPositionRelativeToCamera(CVector* vecOut, CPlaceable* placeable);
};

static constexpr int NUM_AUDIO_ENVIRONMENTS = 68;
extern sReverbEnvironment(&gAudioZoneToReverbEnvironmentMap)[NUM_AUDIO_ENVIRONMENTS];

static constexpr int NUM_SOUND_DIST_ATTENUATION_ENTRIES = 1280;
extern float(&gSoundDistAttenuationTable)[NUM_SOUND_DIST_ATTENUATION_ENTRIES];
