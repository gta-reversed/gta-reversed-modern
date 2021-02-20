/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CAEAudioEntity::CAEAudioEntity() : m_tempSound()
{}

void CAEAudioEntity::UpdateParameters(CAESound *sound, short arg2)
{
    return CAEAudioEntity::UpdateParameters_Reversed(sound, arg2);
}

void CAEAudioEntity::UpdateParameters_Reversed(CAESound* sound, short arg2)
{
    return;
}
