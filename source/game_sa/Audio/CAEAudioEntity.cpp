/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

int8_t*& CAEAudioEntity::m_pAudioEventVolumes = *reinterpret_cast<int8_t**>(0xBD00F8);

CAEAudioEntity::CAEAudioEntity() : m_tempSound()
{}
