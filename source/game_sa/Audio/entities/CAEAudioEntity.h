/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CAESound.h"

#include "eAudioEvents.h"

class CEntity;

class CAEAudioEntity {
public:
    CEntity* m_pEntity;
    CAESound m_tempSound;

    static int8*& m_pAudioEventVolumes;

protected:
    CAEAudioEntity();
    ~CAEAudioEntity() = default;

public:
    // VTABLE
    virtual void UpdateParameters(CAESound* sound, int16 curPlayPos) { /* Empty on purpose */ };

    static float GetDefaultVolume(eAudioEvents audioEvent) { return static_cast<float>(m_pAudioEventVolumes[audioEvent]); }
};

VALIDATE_SIZE(CAEAudioEntity, 0x7C);
