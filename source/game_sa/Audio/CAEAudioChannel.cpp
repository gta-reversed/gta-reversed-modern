#include "StdInc.h"
#include "CAEAudioChannel.h"
#include "CAEAudioUtility.h"
#include "CAESmoothFadeThread.h"

uint32_t& g_numSoundChannelsUsed = *(uint32_t*)0xB5F898;

void CAEAudioChannel::InjectHooks()
{
    ReversibleHooks::Install("CAEAudioChannel", "SetPosition", 0x4D7950, &CAEAudioChannel::SetPosition);
    ReversibleHooks::Install("CAEAudioChannel", "UpdateStatus", 0x4D7BD0, &CAEAudioChannel::UpdateStatus);
    ReversibleHooks::Install("CAEAudioChannel", "Lost", 0x4D7A10, &CAEAudioChannel::Lost);
    ReversibleHooks::Install("CAEAudioChannel", "ConvertFromBytesToMS", 0x4D79D0, &CAEAudioChannel::ConvertFromBytesToMS);
    ReversibleHooks::Install("CAEAudioChannel", "ConvertFromMsToBytes", 0x4D79F0, &CAEAudioChannel::ConvertFromMsToBytes);
    ReversibleHooks::Install("CAEAudioChannel", "SetFrequency", 0x4D7A50, &CAEAudioChannel::SetFrequency);
    ReversibleHooks::Install("CAEAudioChannel", "SetVolume", 0x4D7C60, &CAEAudioChannel::SetVolume);
    ReversibleHooks::Install("CAEAudioChannel", "SetOriginalFrequency", 0x4D7A70, &CAEAudioChannel::SetOriginalFrequency);
    ReversibleHooks::Install("CAEAudioChannel", "SetFrequencyScalingFactor", 0x4D7D00, &CAEAudioChannel::SetFrequencyScalingFactor_Reversed);
    ReversibleHooks::Install("CAEAudioChannel", "GetCurrentPlaybackPosition", 0x4D79A0, &CAEAudioChannel::GetCurrentPlaybackPosition);
}

CAEAudioChannel::CAEAudioChannel(IDirectSound* pDirectSound,
    unsigned short channelId,
    unsigned samplesPerSec,
    unsigned short bitsPerSample)
{
    m_wBitsPerSample = bitsPerSample;
    m_pDirectSound = pDirectSound;
    m_nChannelId = channelId;
    m_nBytesPerSec = samplesPerSec * (bitsPerSample / 8);
    m_dwFlags = 0;
    m_dwBufferStatus = 0;
    m_dwFrequency = samplesPerSec;
    field_57 = 0;
    field_53 = 2;
    m_wFrequencyMult = 1;
    m_dwBufferFrequency = samplesPerSec;
    m_dwOriginalFrequency = samplesPerSec;
    field_47 = 1;
    m_fVolume = -100.0;
    m_pDirectSoundBuffer = 0;
    m_pDirectSound3DBuffer = 0;
    m_bNoScalingFactor = 0;
    m_bLooped = 0;
    field_45 = 0;
}

CAEAudioChannel::~CAEAudioChannel()
{
    if (m_pDirectSoundBuffer)
    {
        --g_numSoundChannelsUsed;
        m_pDirectSoundBuffer->Release();
        m_pDirectSoundBuffer = nullptr;
    }

    if (m_pDirectSound3DBuffer)
    {
        m_pDirectSound3DBuffer->Release();
        m_pDirectSound3DBuffer = nullptr;
    }
}

void CAEAudioChannel::SetFrequencyScalingFactor(float factor)
{
    if (factor == 0.0F)
    {
        if (m_pDirectSoundBuffer
            && !m_bNoScalingFactor
            && CAEAudioChannel::IsBufferPlaying()
            && !AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, -100.0F, -1, true))
        {
            m_pDirectSoundBuffer->Stop();
        }

        m_bNoScalingFactor = true;
        return;
    }

    const auto dwNewFreq = static_cast<uint32_t>(m_dwOriginalFrequency * factor);
    CAEAudioChannel::SetFrequency(dwNewFreq);

    if (m_bNoScalingFactor)
    {
        const auto curPos = CAEAudioChannel::GetCurrentPlaybackPosition();
        if (curPos != 0)
            m_pDirectSoundBuffer->SetVolume(-10000);

        if (m_pDirectSoundBuffer)
            m_pDirectSoundBuffer->Play(0, 0, m_bLooped);

        if (curPos != 0
            && !AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, m_fVolume, -2, false))
        {
            const auto dwVolume = static_cast<LONG>(m_fVolume * 100.0F);
            m_pDirectSoundBuffer->SetVolume(dwVolume);
        }

        m_bNoScalingFactor = false;
    }
}
void CAEAudioChannel::SetFrequencyScalingFactor_Reversed(float factor)
{
    CAEAudioChannel::SetFrequencyScalingFactor(factor);
}

void CAEAudioChannel::SetPosition(CVector* vecPos)
{
    if (!m_pDirectSoundBuffer)
        return;

    if (!m_pDirectSound3DBuffer)
        return;

    m_pDirectSound3DBuffer->SetPosition(vecPos->x, vecPos->y, vecPos->z, DS3D_DEFERRED);
}

void CAEAudioChannel::SetVolume(float volume)
{
    if (!m_pDirectSoundBuffer)
        return;

    if (CAEAudioChannel::IsBufferPlaying() && fabs(volume - m_fVolume) > 60.0F)
    {
        if (volume <= m_fVolume)
        {
            if (AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, volume, -1, false))
            {
                m_fVolume = volume;
                return;
            }
        }
        else if (AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, volume, -2, false))
        {
            m_fVolume = volume;
            return;
        }
    }

    AESmoothFadeThread.SetBufferVolume(m_pDirectSoundBuffer, volume);
    m_fVolume = volume;
}

int CAEAudioChannel::GetCurrentPlaybackPosition()
{
    if (!m_pDirectSoundBuffer)
        return 0;

    uint32_t outPos;
    m_pDirectSoundBuffer->GetCurrentPosition(reinterpret_cast<LPDWORD>(&outPos), nullptr);
    return outPos;
}

uint32_t CAEAudioChannel::ConvertFromBytesToMS(uint32_t bytes)
{
    return CAEAudioUtility::ConvertFromBytesToMS(bytes, m_dwBufferFrequency, m_wFrequencyMult);
}

uint32_t CAEAudioChannel::ConvertFromMsToBytes(uint32_t ms)
{
    return CAEAudioUtility::ConvertFromMSToBytes(ms, m_dwBufferFrequency, m_wFrequencyMult);
}

void CAEAudioChannel::SetFrequency(uint32_t freq)
{
    if (m_dwFrequency == freq)
        return;

    m_dwFrequency = freq;
    if (m_pDirectSoundBuffer)
        m_pDirectSoundBuffer->SetFrequency(freq);
}

void CAEAudioChannel::SetOriginalFrequency(uint32_t freq)
{
    CAEAudioChannel::SetFrequency(freq);
    m_dwOriginalFrequency = freq;
}

void CAEAudioChannel::UpdateStatus()
{
    m_pDirectSoundBuffer->GetStatus(reinterpret_cast<LPDWORD>(&m_dwBufferStatus));
    if (m_dwBufferStatus & DSBSTATUS_BUFFERLOST)
        CAEAudioChannel::Lost();
}

bool CAEAudioChannel::Lost()
{
    while (m_pDirectSoundBuffer->Restore() == DSERR_BUFFERLOST) //BUG: Infinite loop if we don't restore
        Sleep(10);

    return true;
}

