#include "StdInc.h"

#include "AEStaticChannel.h"

#include "AESmoothFadeThread.h"

void CAEStaticChannel::InjectHooks() {
    RH_ScopedClass(CAEStaticChannel);
    RH_ScopedCategory("Audio/Hardware");

    RH_ScopedVirtualInstall(IsSoundPlaying, 0x4F0F40);
    RH_ScopedVirtualInstall(GetPlayTime, 0x4F0F70);
    RH_ScopedVirtualInstall(GetLength, 0x4F0FA0);
    RH_ScopedVirtualInstall(SynchPlayback, 0x4F1040);
    RH_ScopedVirtualInstall(Stop, 0x4F0FB0);
}

CAEStaticChannel::CAEStaticChannel(IDirectSound* pDirectSound, uint16 channelId, bool arg3, uint32 samplesPerSec, uint16 bitsPerSample)
    : CAEAudioChannel(pDirectSound, channelId, samplesPerSec, bitsPerSample)
{
    m_bUnkn1 = false;
    m_bNeedsSynch = false;
    field_8A = arg3;
}

// 0x4F0F40
bool CAEStaticChannel::IsSoundPlaying() {
    if (!m_pDirectSoundBuffer)
        return false;

    if (m_bNoScalingFactor || m_bNeedsSynch)
        return true;

    return CAEAudioChannel::IsBufferPlaying();
}
bool CAEStaticChannel::IsSoundPlaying_Reversed() {
    return CAEStaticChannel::IsSoundPlaying();
}

// 0x4F0F70
int16 CAEStaticChannel::GetPlayTime() {
    if (!IsSoundPlaying())
        return -1;

    const auto curPos = CAEAudioChannel::GetCurrentPlaybackPosition();
    return CAEAudioChannel::ConvertFromBytesToMS(curPos);
}
int16 CAEStaticChannel::GetPlayTime_Reversed() {
    return CAEStaticChannel::GetPlayTime();
}

// 0x4F0FA0
uint16 CAEStaticChannel::GetLength() {
    return CAEAudioChannel::ConvertFromBytesToMS(m_nLengthInBytes);
}
uint16 CAEStaticChannel::GetLength_Reversed() {
    return CAEStaticChannel::GetLength();
}

// 0x4F1040
void CAEStaticChannel::SynchPlayback() {
    if (!m_pDirectSoundBuffer || !m_bNeedsSynch || m_bNoScalingFactor)
        return;

    if (m_bUnkn2) {
        m_pDirectSoundBuffer->SetVolume(-10000);
        if (!AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, m_fVolume, -2, false)) {
            const auto dwVolume = static_cast<LONG>(m_fVolume * 100.0F);
            m_pDirectSoundBuffer->SetVolume(dwVolume);
        }
    }

    m_pDirectSoundBuffer->Play(0, 0, m_bLooped);
    m_nSyncTime = CTimer::GetTimeInMS();
    m_bNeedsSynch = false;
}
void CAEStaticChannel::SynchPlayback_Reversed() {
    CAEStaticChannel::SynchPlayback();
}

// 0x4F0FB0
void CAEStaticChannel::Stop() {
    if (m_pDirectSoundBuffer &&
        CAEAudioChannel::IsBufferPlaying() &&
        !AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, -100.0F, -1, true)
    ) {
        m_pDirectSoundBuffer->Stop();
    }

    { // todo: Same as CAEAudioChannel::~CAEAudioChannel
    if (m_pDirectSoundBuffer) {
        --g_numSoundChannelsUsed;
        m_pDirectSoundBuffer->Release();
        m_pDirectSoundBuffer = nullptr;
    }

    if (m_pDirectSound3DBuffer) {
        m_pDirectSound3DBuffer->Release();
        m_pDirectSound3DBuffer = nullptr;
    }
    }
}
void CAEStaticChannel::Stop_Reversed() {
    CAEStaticChannel::Stop();
}
