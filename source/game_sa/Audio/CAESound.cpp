/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CAESound::CAESound()
{

}

CAESound::CAESound(CAESound& sound)
{
    ((void(__thiscall *)(CAESound *, CAESound&))0x4EF0A0)(this, sound);
}

CAESound::CAESound(short bankSlotId, short sfxId, CAEAudioEntity *baseAudio, CVector posn,
    float volume, float maxDistance, float speed, float timeScale, unsigned char arg9,
    unsigned short environmentFlags, float arg11)
{
    ((void(__thiscall *)(CAESound *, short, short, CAEAudioEntity *, CVector, float, float, float,
        float, unsigned char, unsigned short, float))0x4EFD80)(this, bankSlotId, sfxId, baseAudio,
            posn, volume, maxDistance, speed, timeScale, arg9, environmentFlags, arg11);
}

CAESound::~CAESound()
{
    ((void(__thiscall *)(CAESound *))0x4EF660)(this);
}

void CAESound::operator=(CAESound& sound)
{
    ((void(__thiscall *)(CAESound *, CAESound&))0x4EF680)(this, sound);
}

void CAESound::UnregisterWithPhysicalEntity()
{
    ((void(__thiscall *)(CAESound *))0x4EF1A0)(this);
}

void CAESound::StopSound()
{
    ((void(__thiscall *)(CAESound *))0x4EF1C0)(this);
}

bool CAESound::GetUncancellable()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF1E0)(this);
}

bool CAESound::GetFrontEnd()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF1F0)(this);
}

bool CAESound::GetRequestUpdates()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF200)(this);
}

bool CAESound::GetUnpausable()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF210)(this);
}

bool CAESound::GetPlayPhysically()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF220)(this);
}

bool CAESound::GetStartPercentage()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF230)(this);
}

bool CAESound::GetMusicMastered()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF240)(this);
}

bool CAESound::GetLifespanTiedToPhysicalEntity()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF250)(this);
}

bool CAESound::GetUnduckable()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF260)(this);
}

bool CAESound::GetUncompressable()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF270)(this);
}

bool CAESound::GetRolledOff()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF280)(this);
}

bool CAESound::GetSmoothDucking()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF290)(this);
}

bool CAESound::GetForcedFront()
{
    return ((bool(__thiscall *)(CAESound *))0x4EF2A0)(this);
}

void CAESound::SetIndividualEnvironment(unsigned short environment, unsigned short state)
{
    ((void(__thiscall *)(CAESound *, unsigned short, unsigned short))0x4EF2B0)(this, environment,
        state);
}

void CAESound::UpdatePlayTime(short arg1, short arg2, short arg3)
{
    ((void(__thiscall *)(CAESound *, short, short, short))0x4EF2E0)(this, arg1, arg2, arg3);
}

void CAESound::GetRelativePosition(CVector *outPosn)
{
    ((void(__thiscall *)(CAESound *, CVector *))0x4EF350)(this, outPosn);
}

void CAESound::CalculateFrequency()
{
    ((void(__thiscall *)(CAESound *))0x4EF390)(this);
}

void CAESound::UpdateFrequency()
{
    ((void(__thiscall *)(CAESound *))0x4EF3E0)(this);
}

float CAESound::GetRelativePlaybackFrequencyWithDoppler()
{
    return ((float(__thiscall *)(CAESound *))0x4EF400)(this);
}

float CAESound::GetSlowMoFrequencyScalingFactor()
{
    return ((float(__thiscall *)(CAESound *))0x4EF440)(this);
}

void CAESound::NewVPSLentry()
{
    ((void(__thiscall *)(CAESound *))0x4EF7A0)(this);
}

void CAESound::RegisterWithPhysicalEntity(CEntity *entity)
{
    ((void(__thiscall *)(CAESound *, CEntity *))0x4EF820)(this, entity);
}

void CAESound::StopSoundAndForget()
{
    ((void(__thiscall *)(CAESound *))0x4EF850)(this);
}

void CAESound::SetPosition(CVector posn)
{
    ((void(__thiscall *)(CAESound *, CVector))0x4EF880)(this, posn);
}

void CAESound::CalculateVolume()
{
    ((void(__thiscall *)(CAESound *))0x4EFA10)(this);
}

void CAESound::Initialise(short bankSlotId, short sfxId, CAEAudioEntity *baseAudio, CVector posn,
    float volume, float maxDistance, float speed, float timeScale,
    unsigned char arg9, unsigned short environmentFlags, float arg11,
    short currPlayPosn)
{
    ((void(__thiscall *)(CAESound *, short, short, CAEAudioEntity *, CVector, float, float, float,
        float, unsigned char, unsigned short, float, short))0x4EFE50)(this, bankSlotId, sfxId,
            baseAudio, posn, volume, maxDistance, speed, timeScale, arg9, environmentFlags, arg11,
            currPlayPosn);
}

void CAESound::UpdateParameters(short arg1)
{
    ((void(__thiscall *)(CAESound *, short))0x4EFF50)(this, arg1);
}