#pragma once

#include "CAEAudioEntity.h"

class CAEDoorAudioEntity : public CAEAudioEntity {
    uint m_nTime;
    uint m_nMovingDoorTime;
    uint m_nField84;

public:
    CAEDoorAudioEntity();

    void StaticInitialise();
    void Reset();

    void UpdateParameters(CAESound* sound, short curPlayPos) override;

    void AddAudioEvent(eAudioEvents event, CPhysical* physical);
    void AddAudioEvent(eAudioEvents event, CVector& posn, float volume, float speed);
    void PlayDoorSound(short sfxId, eAudioEvents event, CVector& posn, float volumeDelta, float speed);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    void UpdateParameters_Reversed(CAESound* sound, short curPlayPos);
};

VALIDATE_SIZE(CAEDoorAudioEntity, 0x88);
