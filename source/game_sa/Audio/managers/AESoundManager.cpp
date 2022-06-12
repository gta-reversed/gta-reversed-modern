#include "StdInc.h"

#include "AESoundManager.h"

#include "AEAudioEnvironment.h"
#include "AEAudioHardware.h"

CAESoundManager& AESoundManager = *(CAESoundManager*)0xB62CB0;

void CAESoundManager::InjectHooks() {
    RH_ScopedClass(CAESoundManager);
    RH_ScopedCategory("Audio/Managers");

    RH_ScopedInstall(Service, 0x4F0000);
    RH_ScopedInstall(Initialise, 0x5B9690);
    RH_ScopedInstall(Terminate, 0x4EFAA0);
    RH_ScopedInstall(Reset, 0x4EF4D0);
    RH_ScopedInstall(PauseManually, 0x4EF510);
    RH_ScopedInstall(RequestNewSound, 0x4EFB10);
    RH_ScopedInstall(AreSoundsPlayingInBankSlot, 0x4EF520);
    RH_ScopedInstall(AreSoundsOfThisEventPlayingForThisEntity, 0x4EF570);
    RH_ScopedInstall(AreSoundsOfThisEventPlayingForThisEntityAndPhysical, 0x4EF5D0);
    RH_ScopedInstall(GetVirtualChannelForPhysicalChannel, 0x4EF630);
    RH_ScopedInstall(CancelSoundsInBankSlot, 0x4EFC60);
    RH_ScopedInstall(CancelSoundsOfThisEventPlayingForThisEntity, 0x4EFB90);
    RH_ScopedInstall(CancelSoundsOfThisEventPlayingForThisEntityAndPhysical, 0x4EFBF0);
}

bool CAESoundManager::Initialise() {
    const auto availChannels = AEAudioHardware.GetNumAvailableChannels();
    if (availChannels <= 10)
        return false;

    m_nNumAvailableChannels = availChannels >= MAX_NUM_SOUNDS ? MAX_NUM_SOUNDS : availChannels;
    m_nChannel = AEAudioHardware.AllocateChannels(m_nNumAvailableChannels);
    if (m_nChannel == -1)
        return false;

    // BUG? There's some int16 weird logic in the original code, I simplified it to what's actually used i think
    m_aChannelSoundTable = new int16[m_nNumAvailableChannels];
    m_aChannelSoundPlayTimes = new int16[m_nNumAvailableChannels];
    m_aChannelSoundUncancellable = new int16[m_nNumAvailableChannels];

    for (CAESound& sound : m_aSounds) {
        sound.m_nIsUsed = 0;
        sound.m_nHasStarted = 0;
    }

    std::fill_n(m_aChannelSoundTable, m_nNumAvailableChannels, -1);

    m_nUpdateTime = CTimer::GetTimeInMS();
    m_bPauseTimeInUse = false;
    m_nPauseUpdateTime = 0;
    m_bManuallyPaused = false;

    printf("Initialised SoundManager\n");
    return true;
}

void CAESoundManager::Terminate() {
    delete[] m_aChannelSoundTable;
    delete[] m_aChannelSoundPlayTimes;
    delete[] m_aChannelSoundUncancellable;

    m_aChannelSoundTable = nullptr;
    m_aChannelSoundPlayTimes = nullptr;
    m_aChannelSoundUncancellable = nullptr;
}

void CAESoundManager::Reset() {
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed())
            continue;

        sound.StopSound();
    }
}

void CAESoundManager::PauseManually(uint8 bPause) {
    m_bManuallyPaused = bPause;
}

void CAESoundManager::Service() {
    // Clear sounds uncancellable status for this frame
    std::fill_n(m_aChannelSoundUncancellable, m_nNumAvailableChannels, -1);

    // Calculate time diff from last update
    uint32 timeSinceLastUpdate;
    if (CAESoundManager::IsPaused()) {
        if (m_bPauseTimeInUse)
            timeSinceLastUpdate = CTimer::GetTimeInMSPauseMode() - m_nUpdateTime;
        else {
            m_nPauseUpdateTime = m_nUpdateTime;
            timeSinceLastUpdate = 0;
        }

        m_nUpdateTime = CTimer::GetTimeInMSPauseMode();
        m_bPauseTimeInUse = true;
    } else {
        if (m_bPauseTimeInUse)
            timeSinceLastUpdate = CTimer::GetTimeInMS() - m_nPauseUpdateTime;
        else
            timeSinceLastUpdate = CTimer::GetTimeInMS() - m_nUpdateTime;

        m_nUpdateTime = CTimer::GetTimeInMS();
        m_bPauseTimeInUse = false;
    }

    // Get current frame sounds infos
    AEAudioHardware.GetChannelPlayTimes(m_nChannel, m_aChannelSoundPlayTimes);
    AEAudioHardware.GetVirtualChannelSoundLengths(m_aSoundLengths);
    AEAudioHardware.GetVirtualChannelSoundLoopStartTimes(m_aSoundLoopStartTimes);

    // Initialize sounds that are using percentage specified start positions 0x4F011C
    for (auto i = 0; i < MAX_NUM_SOUNDS; ++i) {
        auto& sound = m_aSounds[i];
        if (!sound.IsUsed() || !sound.WasServiced() || !sound.GetStartPercentage())
            continue;

        sound.SetIndividualEnvironment(eSoundEnvironment::SOUND_START_PERCENTAGE, false);
        if (sound.m_nHasStarted)
            continue;

        sound.m_nCurrentPlayPosition *= uint16(static_cast<float>(m_aSoundLengths[i]) / 100.0F);
    }

    // Stop sounds that turned inactive
    for (auto i = 0; i < m_nNumAvailableChannels; ++i) {
        const auto channelSound = m_aChannelSoundTable[i];
        if (channelSound == -1)
            continue;

        auto& sound = m_aSounds[channelSound];
        sound.m_nCurrentPlayPosition = m_aChannelSoundPlayTimes[i];
        if (sound.m_nPlayingState != eSoundState::SOUND_ACTIVE)
            AEAudioHardware.StopSound(m_nChannel, i);
    }

    // Update sounds playtime
    for (auto i = 0; i < MAX_NUM_SOUNDS; ++i) {
        auto& sound = m_aSounds[i];
        if (!sound.IsUsed() || !sound.WasServiced() || sound.m_nIgnoredServiceCycles)
            continue;

        auto usedProgress = CAESoundManager::IsSoundPaused(sound) ? 0 : timeSinceLastUpdate;
        sound.UpdatePlayTime(m_aSoundLengths[i], m_aSoundLoopStartTimes[i], usedProgress);
    }

    // Remove songs that ended from sounds table
    for (auto i = 0; i < m_nNumAvailableChannels; ++i)
        if (m_aChannelSoundPlayTimes[i] == -1)
            m_aChannelSoundTable[i] = -1;

    // Mark songs that ended as finished
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed() || !sound.WasServiced() || sound.m_nCurrentPlayPosition != -1)
            continue;

        sound.SoundHasFinished();
    }

    // Update song positions and volumes
    for (CAESound& sound : m_aSounds) {
        if (sound.IsUsed()) {
            sound.UpdateParameters(sound.m_nCurrentPlayPosition);
            sound.CalculateVolume();
        }
    }

    // Mark uncancellable songs as so for this frame
    auto numUncancellableSoundsThisFrame = 0;
    for (auto i = 0; i < m_nNumAvailableChannels; ++i) {
        const auto channelSound = m_aChannelSoundTable[i];
        if (channelSound == -1 || !m_aSounds[channelSound].GetUncancellable())
            continue;

        m_aChannelSoundUncancellable[numUncancellableSoundsThisFrame] = channelSound;
        ++numUncancellableSoundsThisFrame;
    }

    // Mark some more songs as uncancellable under specific conditions
    for (auto i = 0; i < MAX_NUM_SOUNDS; ++i) {
        auto& sound = m_aSounds[i];
        if (!sound.IsUsed() || (sound.m_nHasStarted && sound.GetUncancellable()) || sound.m_nIgnoredServiceCycles)
            continue;

        int32 iCurUncancell;
        for (iCurUncancell = m_nNumAvailableChannels - 1; iCurUncancell >= numUncancellableSoundsThisFrame; --iCurUncancell) {
            if (m_aChannelSoundUncancellable[iCurUncancell] == -1)
                continue;

            auto& uncancellSound = m_aSounds[m_aChannelSoundUncancellable[iCurUncancell]];
            if (sound.m_fFinalVolume < uncancellSound.m_fFinalVolume && sound.GetPlayPhysically() <= uncancellSound.GetPlayPhysically()) {
                break;
            }
        }

        auto iFreeUncancellInd = iCurUncancell + 1;
        if (iFreeUncancellInd != m_nNumAvailableChannels) {
            for (auto ind = m_nNumAvailableChannels - 1; ind > iFreeUncancellInd; --ind)
                m_aChannelSoundUncancellable[ind] = m_aChannelSoundUncancellable[ind - 1];

            m_aChannelSoundUncancellable[iFreeUncancellInd] = i;
        }
    }

    // Stop songs that aren't marked as uncancellable in this frame
    for (auto i = 0; i < m_nNumAvailableChannels; ++i) {
        const auto channelSound = m_aChannelSoundTable[i];
        if (channelSound == -1)
            continue;

        int32 uncancellIndex;
        for (uncancellIndex = 0; uncancellIndex < m_nNumAvailableChannels; ++uncancellIndex)
            if (channelSound == m_aChannelSoundUncancellable[uncancellIndex])
                break;

        if (uncancellIndex == m_nNumAvailableChannels) {
            m_aSounds[channelSound].m_nHasStarted = false;
            m_aChannelSoundTable[i] = -1;
            AEAudioHardware.StopSound(m_nChannel, i);
        } else
            m_aChannelSoundUncancellable[uncancellIndex] = -1;
    }

    // Play sounds that require that
    auto curSound = 0;
    for (auto i = 0; i < m_nNumAvailableChannels; ++i) {
        const auto uncancell = m_aChannelSoundUncancellable[i];
        if (uncancell == -1)
            continue;

        while (m_aChannelSoundTable[curSound] != -1 && curSound < m_nNumAvailableChannels)
            ++curSound;

        if (curSound >= m_nNumAvailableChannels)
            continue;

        m_aChannelSoundTable[curSound] = uncancell;
        auto& sound = m_aSounds[uncancell];
        sound.m_nHasStarted = 1;

        auto freq = sound.GetRelativePlaybackFrequencyWithDoppler();
        auto slomoFactor = sound.GetSlowMoFrequencyScalingFactor();

        CAEAudioHardwarePlayFlags flags{};
        flags.m_nFlags = 0;

        flags.m_bIsFrontend        = sound.GetFrontEnd();
        flags.m_bIsUncompressable  = sound.GetUncompressable();
        flags.m_bIsUnduckable      = sound.GetUnduckable();
        flags.m_bIsStartPercentage = sound.GetStartPercentage();
        flags.m_bIsMusicMastered   = sound.GetMusicMastered();
        flags.m_bIsRolledOff       = sound.GetRolledOff();
        flags.m_bIsSmoothDucking   = sound.GetSmoothDucking();
        flags.m_bIsForcedFront     = sound.GetForcedFront();
        flags.m_bUnpausable        = flags.m_bIsFrontend ? sound.GetUnpausable() : false;

        AEAudioHardware.PlaySound(m_nChannel, curSound, sound.m_nSoundIdInSlot, sound.m_nBankSlotId, sound.m_nCurrentPlayPosition, flags.m_nFlags, sound.m_fSpeed);
        AEAudioHardware.SetChannelVolume(m_nChannel, curSound, sound.m_fFinalVolume, 0);

        CVector vecPos;
        sound.GetRelativePosition(&vecPos);
        AEAudioHardware.SetChannelPosition(m_nChannel, curSound, &vecPos, 0);
        AEAudioHardware.SetChannelFrequencyScalingFactor(m_nChannel, curSound, freq * slomoFactor);
        ++curSound;
    }

    for (auto i = 0; i < m_nNumAvailableChannels; ++i) {
        const auto channelSound = m_aChannelSoundTable[i];
        if (channelSound == -1)
            continue;

        auto& sound = m_aSounds[channelSound];
        if (!sound.IsUsed())
            continue;

        if (!CAESoundManager::IsSoundPaused(sound)) {
            AEAudioHardware.SetChannelVolume(m_nChannel, i, sound.m_fFinalVolume, 0);
            auto freq = sound.GetRelativePlaybackFrequencyWithDoppler();
            auto slomoFactor = sound.GetSlowMoFrequencyScalingFactor();
            AEAudioHardware.SetChannelFrequencyScalingFactor(m_nChannel, i, freq * slomoFactor);
        } else {
            AEAudioHardware.SetChannelVolume(m_nChannel, i, -100.0F, 0);
            AEAudioHardware.SetChannelFrequencyScalingFactor(m_nChannel, i, 0.0F);
        }

        CVector vecPos;
        sound.GetRelativePosition(&vecPos);
        AEAudioHardware.SetChannelPosition(m_nChannel, i, &vecPos, 0);
    }

    AEAudioHardware.Service();
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed())
            continue;

        sound.m_bWasServiced = 1;
        if (sound.m_nIgnoredServiceCycles > 0 && !CAESoundManager::IsSoundPaused(sound))
            --sound.m_nIgnoredServiceCycles;
    }
}

CAESound* CAESoundManager::RequestNewSound(CAESound* pSound) {
    int16 firstFree;
    for (firstFree = 0; firstFree < MAX_NUM_SOUNDS; ++firstFree) {
        if (!m_aSounds[firstFree].IsUsed())
            break;
    }

    if (firstFree >= MAX_NUM_SOUNDS)
        return nullptr;

    auto& newSound = m_aSounds[firstFree];
    newSound = *pSound;
    pSound->UnregisterWithPhysicalEntity();
    newSound.NewVPSLentry();
    AEAudioHardware.RequestVirtualChannelSoundInfo(firstFree, newSound.m_nSoundIdInSlot, newSound.m_nBankSlotId);

    return &newSound;
}

int16 CAESoundManager::AreSoundsPlayingInBankSlot(int16 bankSlot) {
    auto nPlaying = eSoundPlayingStatus::SOUND_NOT_PLAYING;
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed() || sound.m_nBankSlotId != bankSlot)
            continue;

        if (sound.m_nHasStarted)
            return eSoundPlayingStatus::SOUND_HAS_STARTED;

        nPlaying = eSoundPlayingStatus::SOUND_PLAYING;
    }

    return nPlaying;
}

int16 CAESoundManager::AreSoundsOfThisEventPlayingForThisEntity(int16 eventId, CAEAudioEntity* audioEntity) {
    auto nPlaying = eSoundPlayingStatus::SOUND_NOT_PLAYING;
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed() || sound.m_nEvent != eventId || sound.m_pBaseAudio != audioEntity)
            continue;

        if (sound.m_nHasStarted)
            return eSoundPlayingStatus::SOUND_HAS_STARTED;

        nPlaying = eSoundPlayingStatus::SOUND_PLAYING;
    }

    return nPlaying;
}

int16 CAESoundManager::AreSoundsOfThisEventPlayingForThisEntityAndPhysical(int16 eventId, CAEAudioEntity* audioEntity, CPhysical* physical) {
    bool nPlaying = eSoundPlayingStatus::SOUND_NOT_PLAYING;
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed() || sound.m_nEvent != eventId || sound.m_pBaseAudio != audioEntity || sound.m_pPhysicalEntity != physical)
            continue;

        if (sound.m_nHasStarted)
            return eSoundPlayingStatus::SOUND_HAS_STARTED;

        nPlaying = eSoundPlayingStatus::SOUND_PLAYING;
    }

    return nPlaying;
}

void CAESoundManager::CancelSoundsOfThisEventPlayingForThisEntity(int16 eventId, CAEAudioEntity* audioEntity) {
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed() || sound.m_nEvent != eventId || sound.m_pBaseAudio != audioEntity)
            continue;

        sound.StopSoundAndForget();
    }
}

void CAESoundManager::CancelSoundsOfThisEventPlayingForThisEntityAndPhysical(int16 eventId, CAEAudioEntity* audioEntity, CPhysical* physical) {
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed() || sound.m_nEvent != eventId || sound.m_pBaseAudio != audioEntity || sound.m_pPhysicalEntity != physical)
            continue;

        sound.StopSoundAndForget();
    }
}

void CAESoundManager::CancelSoundsInBankSlot(int16 bankSlot, bool bFullStop) {
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed() || sound.m_nBankSlotId != bankSlot)
            continue;

        if (bFullStop)
            sound.StopSoundAndForget();
        else
            sound.StopSound();
    }
}

void CAESoundManager::CancelSoundsOwnedByAudioEntity(CAEAudioEntity* audioEntity, bool bFullStop) {
    for (CAESound& sound : m_aSounds) {
        if (!sound.IsUsed() || sound.m_pBaseAudio != audioEntity)
            continue;

        if (bFullStop)
            sound.StopSoundAndForget();
        else
            sound.StopSound();
    }
}

int16 CAESoundManager::GetVirtualChannelForPhysicalChannel(int16 physicalChannel) {
    const auto channel = physicalChannel - m_nChannel;
    if (channel < 0 || channel >= m_nNumAvailableChannels)
        return -1;

    return m_aChannelSoundTable[channel];
}
