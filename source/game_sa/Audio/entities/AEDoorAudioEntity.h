#pragma once

#include "AEAudioEntity.h"

class CAEDoorAudioEntity : public CAEAudioEntity {
    uint32 m_nTime;
    uint32 m_nMovingDoorTime;
    uint32 m_nField84;

public:
    CAEDoorAudioEntity();

    void StaticInitialise();
    void Reset();

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;

    void AddAudioEvent(eAudioEvents event, CPhysical* physical);
    void AddAudioEvent(eAudioEvents event, CVector& posn, float volume, float speed);
    void PlayDoorSound(int16 sfxId, eAudioEvents event, CVector& posn, float volumeDelta, float speed);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
};

VALIDATE_SIZE(CAEDoorAudioEntity, 0x88);
