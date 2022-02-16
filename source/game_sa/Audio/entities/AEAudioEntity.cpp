/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

int8*& CAEAudioEntity::m_pAudioEventVolumes = *reinterpret_cast<int8**>(0xBD00F8);

CAEAudioEntity::CAEAudioEntity() : m_tempSound() {}
