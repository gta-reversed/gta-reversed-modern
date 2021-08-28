#pragma once
#include "PluginBase.h"
#include "CAESound.h"
#include "CPhysical.h"

static constexpr int MAX_NUM_SOUNDS = 300;
static constexpr int MAX_NUM_AUDIO_CHANNELS = 64;

enum eSoundPlayingStatus : int16_t
{
    SOUND_NOT_PLAYING = 0,
    SOUND_PLAYING = 1,
    SOUND_HAS_STARTED = 2,
};

class CAESoundManager
{
public:
    CAESoundManager();
    ~CAESoundManager();

public:
    uint16_t m_nNumAvailableChannels;
    int16_t  m_nChannel;
    CAESound m_aSounds[MAX_NUM_SOUNDS];
    int16_t* m_aChannelSoundTable;
    int16_t* m_aChannelSoundPlayTimes;
    int16_t* m_aChannelSoundUncancellable;
    int16_t  m_aSoundLengths[MAX_NUM_SOUNDS];
    int16_t  m_aSoundLoopStartTimes[MAX_NUM_SOUNDS];
    uint32_t m_nUpdateTime;
    bool     m_bPauseTimeInUse;
    bool     m_bManuallyPaused;
    uint8_t  field_8CB6[2];
    uint32_t m_nPauseUpdateTime;

public:
    static void InjectHooks();

    bool Initialise();
    void Terminate();
    void Reset();
    void PauseManually(uint8_t bPause);
    void Service();
    CAESound* RequestNewSound(CAESound* pSound);
    int16_t AreSoundsPlayingInBankSlot(short bankSlot);
    int16_t AreSoundsOfThisEventPlayingForThisEntity(short eventId, CAEAudioEntity* audioEntity);
    int16_t AreSoundsOfThisEventPlayingForThisEntityAndPhysical(short eventId, CAEAudioEntity* audioEntity, CPhysical* physical);
    void CancelSoundsOfThisEventPlayingForThisEntity(short eventId, CAEAudioEntity* audioEntity);
    void CancelSoundsOfThisEventPlayingForThisEntityAndPhysical(short eventId, CAEAudioEntity* audioEntity, CPhysical* physical);
    void CancelSoundsInBankSlot(short bankSlot, uint8_t bFullStop);
    void CancelSoundsOwnedByAudioEntity(CAEAudioEntity* audioEntity, uint8_t bFullStop);
    int16_t GetVirtualChannelForPhysicalChannel(short physicalChannel);

public:
    bool IsPaused() const { return CTimer::GetIsPaused() || m_bManuallyPaused; }
    bool IsSoundPaused(CAESound const& sound) const { return CAESoundManager::IsPaused() && !sound.GetUnpausable(); }
};
VALIDATE_SIZE(CAESoundManager, 0x8CBC);

extern CAESoundManager& AESoundManager;
