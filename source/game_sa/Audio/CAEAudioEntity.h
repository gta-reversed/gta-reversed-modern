/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CAESound.h"
#include "eAudioEvents.h"

class CEntity;

class  CAEAudioEntity {
protected:
    CAEAudioEntity();
    ~CAEAudioEntity() = default;
public:
    CEntity *m_pEntity;
    CAESound m_tempSound;

public:
// VTABLE
    virtual void UpdateParameters(CAESound* sound, short curPlayPos) { /* Empty on purpose */ };

public:
    static int8_t*& m_pAudioEventVolumes;

public:
    static float GetDefaultVolume(eAudioEvents audioEvent) { return static_cast<float>(CAEAudioEntity::m_pAudioEventVolumes[audioEvent]); }
};

VALIDATE_SIZE(CAEAudioEntity, 0x7C);
