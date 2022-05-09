/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AEAudioEntity.h"
#include "AESound.h"
#include "AETwinLoopSoundEntity.h"

class CPed;

class CAEPedAudioEntity : public CAEAudioEntity {
public:
    bool                   m_bCanAddEvent;
    char                   field_7D;
    int16                  m_nSfxId;
    uint32                 m_nTimeInMS;

    float                  m_fVolume1;
    float                  m_fVolume2;
    float                  m_fVolume3;
    float                  m_JetPackSoundSpeedMult;
    CPed*                  m_pPed;

    bool                   m_bJetPackPlaying;
    CAESound*              m_JetPackSound0;
    CAESound*              m_JetPackSound1;
    CAESound*              m_JetPackSound2;

    CAETwinLoopSoundEntity m_sTwinLoopSoundEntity;
    CAESound*              field_150;
    float                  field_154;
    float                  field_158;

public:
    CAEPedAudioEntity();
    ~CAEPedAudioEntity() = default; // 0x5DE920

    void Initialise(CPed* ped);
    static void StaticInitialise();
    void Terminate();

    void AddAudioEvent(int32 event, float volume, float speed, CPhysical* ped = nullptr, uint8 surfaceId = 0, int32 a7 = 0, uint32 maxVol = 0);

    void TurnOnJetPack();
    void TurnOffJetPack();
    void StopJetPackSound();
    void UpdateJetPack(float thrustFwd, float thrustAngle);
    void PlayWindRush(float, float);
    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;

    void HandleFootstepEvent(int32 event, float volume, float speed, uint8 surfaceId);
    void HandleSkateEvent(int32 event, float volume, float speed);
    void HandleLandingEvent(int32 event);
    void HandlePedSwing(int32 event, int32 a3, uint32 volume);
    void HandlePedHit(int32 event, CPhysical* physical, uint8 surfaceId, float volume, uint32 maxVol);
    void HandlePedJacked(int32 event) ;
    void HandleSwimSplash(int32 event);
    void HandleSwimWake(int32 event);

    void PlayShirtFlap(float volume, float speed);
    void Service();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) { UpdateParameters(sound, curPlayPos); }
};

VALIDATE_SIZE(CAEPedAudioEntity, 0x15C);
