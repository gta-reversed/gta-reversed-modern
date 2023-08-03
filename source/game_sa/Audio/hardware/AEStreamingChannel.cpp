#include "StdInc.h"

#include "AEStreamingChannel.h"
#include <AESmoothFadeThread.h>

// 0x4F2200
CAEStreamingChannel::~CAEStreamingChannel() {
    plugin::CallMethod<0x4F2200, CAEStreamingChannel*>(this);
}

// 0x4F22F0
void CAEStreamingChannel::Initialise() {
    plugin::CallMethod<0x4F22F0, CAEStreamingChannel*>(this);
}

// 0x4F1C70
void CAEStreamingChannel::InitialiseSilence() {
    DSBUFFERDESC bufferDesc{};
    bufferDesc.dwSize = 36;
    bufferDesc.lpwfxFormat = &m_WaveFormat;
    bufferDesc.dwBufferBytes = 0x8000;
    bufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE;

    if (SUCCEEDED(m_pDirectSound->CreateSoundBuffer(&bufferDesc, &m_pSilenceBuffer, 0))) {
        void *audioPtr;
        DWORD audioPtrBytes;

        m_pSilenceBuffer->Lock(0, 0, &audioPtr, &audioPtrBytes, nullptr, 0, DSBLOCK_ENTIREBUFFER);
        memset(audioPtr, 0, audioPtrBytes);
        m_pSilenceBuffer->Unlock(audioPtr, audioPtrBytes, nullptr, 0);
        m_pSilenceBuffer->Play(0, 0, DSBPLAY_LOOPING);

    } else {
        NOTSA_LOG_WARN("Creating silence buffer failed.");
    }
}

// 0x4F1FF0
void CAEStreamingChannel::SetReady() {
    switch (m_nState) {
    case StreamingChannelState::UNK_MINUS_5:
        AESmoothFadeThread.CancelFade(m_pDirectSoundBuffer);
        m_pDirectSoundBuffer->Stop();
        m_nState = StreamingChannelState::UNK_MINUS_6;

        break;
    case StreamingChannelState::UNK_MINUS_6:
        if (m_pStreamingDecoder)
            m_nState = StreamingChannelState::UNK_MINUS_2;
        break;
    }
}

// 0x4F1F30
void CAEStreamingChannel::SetBassEQ(IDirectSoundFXParamEq* paramEq, float gain) {
    if (!paramEq) {
        if (m_bFxEnabled)
            RemoveFX();

        return;
    }

    if (!m_bFxEnabled && !AddFX())
        return;

    // per channel?
    for (auto i = 0; i < 2; i++) {
        auto* buffer8 = (IDirectSoundBuffer8*)(m_pDirectSoundBuffer);

        if (FAILED(buffer8->GetObjectInPath(
            GUID_All_Objects,
            i,
            IID_IDirectSoundFXParamEq,
            reinterpret_cast<LPVOID*>(&paramEq)
        )))
            continue;

        // TODO: check
        DSFXParamEq params{};
        paramEq->GetAllParameters(&params);
        params.fGain *= gain;
        paramEq->SetAllParameters(&params);

        paramEq->Release();
    }
}

// 0x4F2060
void CAEStreamingChannel::SetFrequencyScalingFactor(float factor) {
    if (factor == 0.0f) {
        if (!m_pDirectSoundBuffer || m_nState == StreamingChannelState::UNK_MINUS_7 || !IsBufferPlaying())
            return;

        if (!AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, -100.0f, 35, true))
            m_pDirectSoundBuffer->Stop();

        m_nState = StreamingChannelState::UNK_MINUS_7;
    } else {
        SetFrequency(static_cast<uint32>((float)m_nOriginalFrequency * factor));

        if (m_nState == StreamingChannelState::UNK_MINUS_7)
            return;

        m_nState = StreamingChannelState::UNK_MINUS_1;

        if (!m_pDirectSoundBuffer)
            return;

        m_pDirectSoundBuffer->SetVolume(-10'000);
        m_pDirectSoundBuffer->Play(0, 0, m_bLooped ? DSBPLAY_LOOPING : 0);

        if (!AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, m_fVolume, 35, true))
            m_pDirectSoundBuffer->SetVolume(static_cast<int32>(m_fVolume * 100.0f));
    }
}

// 0x4F1870
void CAEStreamingChannel::SynchPlayback() {
    // NOP
}

// 0x4F1E20
uint32 CAEStreamingChannel::FillBuffer(void* buffer, uint32 size) {
    return plugin::CallMethodAndReturn<uint32, 0x4F1E20, CAEStreamingChannel*, void*, uint32>(this, buffer, size);
}

// 0x4F23D0
void CAEStreamingChannel::PrepareStream(CAEStreamingDecoder* stream, int8 arg2, bool bStopCurrent) {
    plugin::CallMethod<0x4F23D0, CAEStreamingChannel*, CAEStreamingDecoder*, int8, bool>(this, stream, arg2, bStopCurrent);
}

// 0x4F1DE0
void CAEStreamingChannel::SetNextStream(CAEStreamingDecoder* decoder) {
    return plugin::CallMethod<0x4F1DE0, CAEStreamingChannel*, CAEStreamingDecoder*>(this, decoder);
}

// 0x4F1A60
int32 CAEStreamingChannel::GetPlayingTrackID() {
    switch (m_nState) {
    case StreamingChannelState::UNK_MINUS_3:
    case StreamingChannelState::UNK_MINUS_4:
    case StreamingChannelState::UNK_MINUS_1:
    case StreamingChannelState::UNK_MINUS_5:
        if (m_pStreamingDecoder)
            return m_pStreamingDecoder->GetStreamID();

        [[fallthrough]];
    default:
        return -1;
    }
}

// 0x4F1A40
int32 CAEStreamingChannel::GetActiveTrackID() {
    return m_pStreamingDecoder ? m_pStreamingDecoder->GetStreamID() : -1;
}

// 0x4F18A0
int32 CAEStreamingChannel::UpdatePlayTime() {
    return plugin::CallMethodAndReturn<int32, 0x4F18A0, CAEStreamingChannel*>(this);
}

// 0x4F1AE0
bool CAEStreamingChannel::AddFX() {
    return plugin::CallMethodAndReturn<bool, 0x4F1AE0, CAEStreamingChannel*>(this);
}

// 0x4F1C20
void CAEStreamingChannel::RemoveFX() {
    bool stopped{false};
    if (bufferStatus.Bit0x1) {
        m_pDirectSoundBuffer->Stop();
        stopped = true;
    }

    auto* buffer8 = (IDirectSoundBuffer8*)m_pDirectSoundBuffer;
    buffer8->SetFX(0, nullptr, nullptr);

    if (stopped)
        m_pDirectSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);

    m_bFxEnabled = false;
}

// 0x4F2040
bool CAEStreamingChannel::IsSoundPlaying() {
    return plugin::CallMethodAndReturn<bool, 0x4F2040, CAEStreamingChannel*>(this);
}

// 0x4F19E0
int16 CAEStreamingChannel::GetPlayTime() {
    return plugin::CallMethodAndReturn<int16, 0x4F19E0, CAEStreamingChannel*>(this);
}

// 0x4F1880
uint16 CAEStreamingChannel::GetLength() {
    return plugin::CallMethodAndReturn<uint16, 0x4F1880, CAEStreamingChannel*>(this);
}

// 0x4F1D40
void CAEStreamingChannel::Play(int16, int8 a3, float) {
    if (!m_pStreamingDecoder || !m_pDirectSoundBuffer)
        return;

    SetOriginalFrequency(m_pStreamingDecoder->GetSampleRate());

    if (m_nState != StreamingChannelState::UNK_MINUS_7)
        field_61 = a3;

    if (m_nState == StreamingChannelState::UNK_MINUS_5) {
        AESmoothFadeThread.CancelFade(m_pDirectSoundBuffer);
        m_pDirectSoundBuffer->Stop();

        m_nState = StreamingChannelState::UNK_MINUS_6;
    }

    m_nState = StreamingChannelState::UNK_MINUS_1;
    m_pDirectSoundBuffer->SetVolume(static_cast<int32>(m_fVolume * 100.0f));
    m_pDirectSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
}

// 0x4F2170
void CAEStreamingChannel::Pause() {
    if (!m_pDirectSoundBuffer)
        return;

    if (!AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, -100.0, 35, 1))
        m_pDirectSoundBuffer->Stop();

    m_nState = StreamingChannelState::UNK_MINUS_7;
}

// 0x4F1A90
void CAEStreamingChannel::Stop() {
    if (!AESmoothFadeThread.RequestFade(m_pDirectSoundBuffer, -100.0f, 35, true))
        m_pDirectSoundBuffer->Stop();

    // SA: dead code
    if (false) {
        m_nState = StreamingChannelState::UNK_MINUS_5;
        field_60088 = 0;
    }
}

// 0x4F2550
void CAEStreamingChannel::Service() {
    plugin::CallMethod<0x4F2550, CAEStreamingChannel*>(this);
}

void CAEStreamingChannel::InjectHooks() {
    RH_ScopedClass(CAEStreamingChannel);
    RH_ScopedCategory("Audio/Hardware");

    RH_ScopedInstall(Constructor, 0x4F1800);
    // Install("CAEStreamingChannel", "~CAEStreamingChannel", 0x4F2200, static_cast<CAEStreamingChannel*(CAEStreamingChannel::*)()>(&CAEStreamingChannel::Destructor));
    RH_ScopedInstall(SynchPlayback, 0x4F1870);
    RH_ScopedInstall(PrepareStream, 0x4F23D0, { .reversed = false });
    RH_ScopedInstall(Initialise, 0x4F22F0, { .reversed = false });
    RH_ScopedInstall(Pause, 0x4F2170);
    RH_ScopedInstall(SetReady, 0x4F1FF0);
    RH_ScopedInstall(SetBassEQ, 0x4F1F30, { .reversed = true });
    RH_ScopedInstall(FillBuffer, 0x4F1E20, { .reversed = false });
    RH_ScopedInstall(InitialiseSilence, 0x4F1C70);
    RH_ScopedInstall(SetNextStream, 0x4F1DE0, { .reversed = false });
    RH_ScopedInstall(AddFX, 0x4F1AE0, { .reversed = false });
    RH_ScopedInstall(Stop, 0x4F1A90);
    RH_ScopedInstall(GetPlayingTrackID, 0x4F1A60);
    RH_ScopedInstall(GetActiveTrackID, 0x4F1A40);
    RH_ScopedInstall(UpdatePlayTime, 0x4F18A0, { .reversed = false });
    RH_ScopedInstall(RemoveFX, 0x4F1C20);
    RH_ScopedVirtualInstall(Service, 0x4F2550, { .reversed = false });
    RH_ScopedVirtualInstall(IsSoundPlaying, 0x4F2040, { .reversed = false });
    RH_ScopedVirtualInstall(GetPlayTime, 0x4F19E0, { .reversed = false });
    RH_ScopedVirtualInstall(GetLength, 0x4F1880, { .reversed = false });
    RH_ScopedVirtualInstall(Play, 0x4F1D40);
    // RH_ScopedVirtualOverloadedInstall(Stop, "", 0x4F21C0, int8(CAEStreamingChannel::*)()); <-- unused, maybe inlined?
    RH_ScopedVirtualInstall(SetFrequencyScalingFactor, 0x4F2060);
}

// 0x4F1800
CAEStreamingChannel* CAEStreamingChannel::Constructor(IDirectSound* directSound, uint16 channelId) {
    this->CAEStreamingChannel::CAEStreamingChannel(directSound, channelId);
    return this;
}

//
CAEStreamingChannel* CAEStreamingChannel::Destructor() {
    this->CAEStreamingChannel::~CAEStreamingChannel();
    return this;
}

// 0x4F2550
void CAEStreamingChannel::Service_Reversed() {
    CAEStreamingChannel::Service();
}

// 0x4F2040
bool CAEStreamingChannel::IsSoundPlaying_Reversed() {
    return CAEStreamingChannel::IsSoundPlaying();
}

// 0x4F19E0
int32 CAEStreamingChannel::GetPlayTime_Reversed() {
    return CAEStreamingChannel::GetPlayTime();
}

// 0x4F1880
int32 CAEStreamingChannel::GetLength_Reversed() {
    return CAEStreamingChannel::GetLength();
}

// 0x4F1D40
void CAEStreamingChannel::Play_Reversed(int16 a2, char a3, float a4) {
    CAEStreamingChannel::Play(a2, a3, a4);
}

// 0x4F21C0
void CAEStreamingChannel::Stop_Reversed() {
    CAEStreamingChannel::Stop();
}

// 0x4F2060
void CAEStreamingChannel::SetFrequencyScalingFactor_Reversed(float a2) {
    CAEStreamingChannel::SetFrequencyScalingFactor(a2);
}
