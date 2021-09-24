#pragma once

#include "AEAudioEntity.h"

class CVector;
class CWaterCannon;

class CAEWaterCannonAudioEntity : public CAEAudioEntity {
public:
    bool    m_bInitialized;
    bool    m_bSplashInfoEnabled;
    char    f7E[2];
    CVector m_vecPosn;
    float   m_nSplashMagnitude;

public:
    CAEWaterCannonAudioEntity();
    // 0x728AB0 ~CAEWaterCannonAudioEntity();

    void Initialise(CWaterCannon* waterCannon);
    void Terminate();
    void StaticInitialise();

    void AddAudioEvent(int32, CVector&);
    void SetSplashInfo(CVector posn, float magnitude);
    void ClearSplashInfo();
    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;
    void UpdateGenericWaterCannonSound(bool splashInfoEnabled, int16 a3, int16 bankSlotId, int16 sfxId, float speed, float volume, CVector posn, float soundDistance);
    void Service();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEWaterCannonAudioEntity* Constructor();

    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
};

VALIDATE_SIZE(CAEWaterCannonAudioEntity, 0x90);
