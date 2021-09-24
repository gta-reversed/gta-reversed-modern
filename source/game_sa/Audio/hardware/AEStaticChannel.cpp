#include "StdInc.h"

#include "AEStaticChannel.h"

#include "AESmoothFadeThread.h"

void CAEStaticChannel::InjectHooks() {
    ReversibleHooks::Install("CAEStaticChannel", "IsSoundPlaying", 0x4F0F40, &CAEStaticChannel::IsSoundPlaying_Reversed);
    ReversibleHooks::Install("CAEStaticChannel", "GetPlayTime", 0x4F0F70, &CAEStaticChannel::GetPlayTime_Reversed);
    ReversibleHooks::Install("CAEStaticChannel", "GetLength", 0x4F0FA0, &CAEStaticChannel::GetLength_Reversed);
    ReversibleHooks::Install("CAEStaticChannel", "SynchPlayback", 0x4F1040, &CAEStaticChannel::SynchPlayback_Reversed);
    ReversibleHooks::Install("CAEStaticChannel", "Stop", 0x4F0FB0, &CAEStaticChannel::Stop_Reversed);
}

CAEStaticChannel::CAEStaticChannel(IDirectSound* pDirectSound, uint16 channelId, bool arg3, uint32 samplesPerSec, uint16 bitsPerSample)
    : CAEAudioChannel(pDirectSound, channelId, samplesPerSec, bitsPerSample)
{
    m_bUnkn1 = false;
    m_bNeedsSynch = false;
    field_8A = arg3;
}

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

uint16 CAEStaticChannel::GetPlayTime() {
    if (!this->IsSoundPlaying())
        return -1;

    const auto curPos = CAEAudioChannel::GetCurrentPlaybackPosition();
    return CAEAudioChannel::ConvertFromBytesToMS(curPos);
}
uint16 CAEStaticChannel::GetPlayTime_Reversed() {
    return CAEStaticChannel::GetPlayTime();
}

uint16 CAEStaticChannel::GetLength() {
    return CAEAudioChannel::ConvertFromBytesToMS(m_nLengthInBytes);
}
uint16 CAEStaticChannel::GetLength_Reversed() {
    return CAEStaticChannel::GetLength();
}

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

void CAEStaticChannel::Stop() {
    if (m_pDirectSoundBuffer &&
        CAEAudioChannel::IsBufferPlaying() &&
        !AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, -100.0F, -1, true)
    ) {
        m_pDirectSoundBuffer->Stop();
    }

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
void CAEStaticChannel::Stop_Reversed() {
    CAEStaticChannel::Stop();
}
