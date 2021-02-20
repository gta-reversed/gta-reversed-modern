/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
class CAEAudioEntity;
/*
enum  eSoundEnvironment : unsigned short {
    SOUND_FRONT_END = 1,
    SOUND_UNCANCELLABLE = 2,
    SOUND_REQUEST_UPDATES = 4,
    SOUND_PLAY_PHYSICALLY = 8,
    SOUND_UNPAUSABLE = 16,
    SOUND_START_PERCENTAGE = 32,
    SOUND_MUSIC_MASTERED = 64,
    SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY = 128,
    SOUND_UNDUCKABLE = 256,
    SOUND_UNCOMPRESSABLE = 512,
    SOUND_ROLLED_OFF = 1024,
    SOUND_SMOOTH_DUCKING = 2048,
    SOUND_FORCED_FRONT = 4096
};
*/
class  CAESound {
public:
    CAESound() { m_pPhysicalEntity = nullptr; }
    CAESound(CAESound& sound);
    CAESound(short bankSlotId, short sfxId, CAEAudioEntity* baseAudio, CVector posn, float volume,
        float fDistance, float speed, float timeScale, unsigned char arg9,
        unsigned short environmentFlags, float arg11);
    ~CAESound();
public:
    short                 m_nBankSlotId;
    short                 m_nSoundIdInSlot;
    CAEAudioEntity       *m_pBaseAudio;
    class CEntity        *m_pPhysicalEntity;
    unsigned int          m_nEvent;
    float                 m_fMaxVolume;
    float                 m_fVolume;
    float                 m_fSoundDistance;
    float                 m_fSpeed;
    float field_20;
    CVector               m_vecCurrPosn;
    CVector               m_vecPrevPosn;
    int                   m_nLastFrameUpdate;
    int                   m_nCurrTimeUpdate;
    int                   m_nPrevTimeUpdate;
    float                 m_fCurrCamDist;
    float                 m_fPrevCamDist;
    float                 m_fTimeScale;
    char field_54;
    char field_55;
    union {
        unsigned short m_nEnvironmentFlags;
        struct {
            unsigned short m_bFrontEnd : 1;
            unsigned short m_bUncancellable : 1;
            unsigned short m_bRequestUpdates : 1;
            unsigned short m_bPlayPhysically : 1;
            unsigned short m_bUnpausable : 1;
            unsigned short m_bStartPercentage : 1;
            unsigned short m_bMusicMastered : 1;
            unsigned short m_bLifespanTiedToPhysicalEntity : 1;
            unsigned short m_bUndackable : 1;
            unsigned short m_bUncompressable : 1;
            unsigned short m_bRolledOff : 1;
            unsigned short m_bSmoothDucking : 1;
            unsigned short m_bForcedFront : 1;
        };
    };
    unsigned short        m_nIsUsed;
    short field_5A;
    short                 m_nCurrentPlayPosition;
    short field_5E;
    float                 m_fFinalVolume;
    float                 m_fFrequency;
    short                 m_nPlayingState;
    char field_6A[2];
    float                 m_fSoundHeadRoom;
    short m_nSoundLength;
    short field_72;

public:
    static void InjectHooks();
    
    void operator=(CAESound& sound);
    void UnregisterWithPhysicalEntity();
    void StopSound();
    bool GetUncancellable();
    bool GetFrontEnd();
    bool GetRequestUpdates();
    bool GetUnpausable();
    bool GetPlayPhysically();
    bool GetStartPercentage();
    bool GetMusicMastered();
    bool GetLifespanTiedToPhysicalEntity();
    bool GetUnduckable();
    bool GetUncompressable();
    bool GetRolledOff();
    bool GetSmoothDucking();
    bool GetForcedFront();
    void SetIndividualEnvironment(unsigned short environment, unsigned short state);
    void UpdatePlayTime(short arg1, short arg2, short arg3);
    void GetRelativePosition(CVector *outPosn);
    void CalculateFrequency();
    void UpdateFrequency();
    float GetRelativePlaybackFrequencyWithDoppler();
    float GetSlowMoFrequencyScalingFactor();
    void NewVPSLentry();
    void RegisterWithPhysicalEntity(CEntity *entity);
    void StopSoundAndForget();
    void SetPosition(CVector posn);
    void CalculateVolume();
    void Initialise(short bankSlotId, short sfxId, CAEAudioEntity *baseAudio, CVector posn,
        float volume, float maxDistance, float speed, float timeScale, unsigned char arg9,
        unsigned short environmentFlags, float arg11, short currPlayPosn);
    void UpdateParameters(short arg1);
};

VALIDATE_SIZE(CAESound, 0x74);
