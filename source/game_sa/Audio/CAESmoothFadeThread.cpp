#include "StdInc.h"
#include "CAESmoothFadeThread.h"

#include "CAEAudioChannel.h"
#include "CAEAudioUtility.h"

CAESmoothFadeThread& AESmoothFadeThread = *(CAESmoothFadeThread*)0xB608D0;

void CAESmoothFadeThread::InjectHooks()
{
    ReversibleHooks::Install("CAESmoothFadeThread", "Start", 0x4EEA10, &CAESmoothFadeThread::Start);
    ReversibleHooks::Install("CAESmoothFadeThread", "Stop", 0x4EEA30, &CAESmoothFadeThread::Stop);
    ReversibleHooks::Install("CAESmoothFadeThread", "WaitForExit", 0x4EEA40, &CAESmoothFadeThread::WaitForExit);
    ReversibleHooks::Install("CAESmoothFadeThread", "Initialise", 0x4EEEC0, &CAESmoothFadeThread::Initialise);
    ReversibleHooks::Install("CAESmoothFadeThread", "InitialiseRequestSlots", 0x4EE9F0, &CAESmoothFadeThread::InitialiseRequestSlots);
    ReversibleHooks::Install("CAESmoothFadeThread", "CancelFade", 0x4EEA50, &CAESmoothFadeThread::CancelFade);
    ReversibleHooks::Install("CAESmoothFadeThread", "SetBufferVolume", 0x4EEC80, &CAESmoothFadeThread::SetBufferVolume);
    ReversibleHooks::Install("CAESmoothFadeThread", "SmoothFadeProc", 0x4EEE90, &CAESmoothFadeThread::SmoothFadeProc);
    ReversibleHooks::Install("CAESmoothFadeThread", "RequestFade", 0x4EEAA0, &CAESmoothFadeThread::RequestFade);
    ReversibleHooks::Install("CAESmoothFadeThread", "Service", 0x4EED10, &CAESmoothFadeThread::Service);
}

CAESmoothFadeThread::CAESmoothFadeThread()
{
    m_threadHandle = (HANDLE)-1;
    m_dwThreadId = 0;
    m_bThreadCreated = false;
    m_bActive = false;
    m_wUnkn = 0;
    m_wUnkn2 = 0;
    m_nLastServiceTime = 0;
    m_nNumAvailableBuffers = 0;
}

void CAESmoothFadeThread::Initialise()
{
    CAESmoothFadeThread::InitialiseRequestSlots();
    m_threadHandle = CreateThread(nullptr, 0, &CAESmoothFadeThread::SmoothFadeProc, this, CREATE_SUSPENDED, &m_dwThreadId);
    if (m_threadHandle == (HANDLE)-1)
        m_bThreadCreated = false;
    else
    {
        SetThreadPriority(m_threadHandle, 0);
        m_bThreadCreated = true;
        m_bThreadInvalid = false;
    }
}

void CAESmoothFadeThread::InitialiseRequestSlots()
{
    for (auto& entry : m_aEntries)
    {
        entry.m_nStatus = eSmoothFadeEntryStatus::STATE_INACTIVE;
        entry.m_pSoundBuffer = nullptr;
    }
}

void CAESmoothFadeThread::Start()
{
    m_bActive = true;
    ResumeThread(m_threadHandle);
}

void CAESmoothFadeThread::Stop()
{
    m_bActive = false;
}

void CAESmoothFadeThread::WaitForExit()
{
    WaitForSingleObject(m_threadHandle, -1);
}

void CAESmoothFadeThread::Service()
{
    m_nLastServiceTime = CAEAudioUtility::GetCurrentTimeInMilliseconds();
    for (auto& entry : m_aEntries)
    {
        if (entry.m_nStatus == eSmoothFadeEntryStatus::STATE_INACTIVE)
            continue;

        if (entry.m_nStatus == eSmoothFadeEntryStatus::STATE_CANCELLED)
        {
            --g_numSoundChannelsUsed;
            if (entry.m_pSoundBuffer)
                entry.m_pSoundBuffer->Release();

            entry.m_pSoundBuffer = nullptr;
            entry.m_nStatus = eSmoothFadeEntryStatus::STATE_INACTIVE;
            continue;
        }

        if (!entry.m_pSoundBuffer)
            continue;

        if (m_nLastServiceTime < entry.m_nStartTime)
            continue;

        const auto dwElapsed = m_nLastServiceTime - entry.m_nStartTime;
        if (dwElapsed < entry.m_wFadeTime)
        {
            const auto fStep = pow(10.0F, entry.m_fVolumeDiff / 20.0F) - 1.0F;
            const auto fProgress = static_cast<float>(dwElapsed) / static_cast<float>(entry.m_wFadeTime);
            entry.m_fCurVolume = entry.m_fStartVolume + LOG10_2 * log2(fStep * fProgress) * 20.0F;

            const auto dwVolume = static_cast<LONG>(entry.m_fCurVolume * 100.0F);
            entry.m_pSoundBuffer->SetVolume(dwVolume);
            continue;
        }

        int32_t dwCurVolume;
        entry.m_pSoundBuffer->GetVolume((LPLONG)&dwCurVolume);
        const auto fCurVolume = static_cast<float>(dwCurVolume) / 100.0F;
        if (entry.m_bStopBufferAfterFade || approxEqual2(fCurVolume, entry.m_fCurVolume, 0.01F))
        {
            const auto dwTargetVolume = static_cast<LONG>(entry.m_fTargetVolume * 100.0F);
            entry.m_pSoundBuffer->SetVolume(dwTargetVolume);
            if (entry.m_bStopBufferAfterFade)
                entry.m_pSoundBuffer->Stop();
        }

        --g_numSoundChannelsUsed;
        if (entry.m_pSoundBuffer)
            entry.m_pSoundBuffer->Release();

        entry.m_pSoundBuffer = nullptr;
        entry.m_nStatus = eSmoothFadeEntryStatus::STATE_INACTIVE;
    }
}

void CAESmoothFadeThread::CancelFade(IDirectSoundBuffer* buffer)
{
    if (m_bThreadInvalid)
        return;

    for (auto& entry : m_aEntries)
        if (entry.m_nStatus == eSmoothFadeEntryStatus::STATE_ACTIVE && entry.m_pSoundBuffer == buffer)
            entry.m_nStatus = eSmoothFadeEntryStatus::STATE_CANCELLED;
}

bool CAESmoothFadeThread::RequestFade(IDirectSoundBuffer* buffer, float fTargetVolume, short fadeTime, bool bStopBufferAfterFade)
{
    if (!m_bThreadCreated || m_bThreadInvalid)
        return false;

    uint32_t dwStatus;
    buffer->GetStatus((LPDWORD)&dwStatus);
    if (!(dwStatus & DSBSTATUS_PLAYING))
        return false;

    int32_t dwCurVolume;
    buffer->GetVolume((LPLONG)&dwCurVolume);
    const auto fCurVolume = static_cast<float>(dwCurVolume) / 100.0F;

    if(approxEqual2(fCurVolume, fTargetVolume, 0.01F))
    {
        if (bStopBufferAfterFade)
            buffer->Stop();

        return true;
    }

    bool bFound = false;
    int iFreeInd = -1;
    for (uint32_t i = 0; i < m_nNumAvailableBuffers; ++i)
    {
        auto& sound = m_aEntries[i];
        if (sound.m_nStatus == eSmoothFadeEntryStatus::STATE_INACTIVE && !bFound)
        {
            bFound = true;
            iFreeInd = i;
            continue;
        }

        if (sound.m_nStatus != eSmoothFadeEntryStatus::STATE_ACTIVE)
            continue;

        if (sound.m_pSoundBuffer != buffer)
            continue;

        if (fadeTime + sound.m_nStartTime - m_nLastServiceTime <= 1)
            continue;

        bFound = true;
        iFreeInd = i;
        break;
    }

    if (!bFound)
        return false;

    auto& sound = m_aEntries[iFreeInd];
    if (sound.m_nStatus == eSmoothFadeEntryStatus::STATE_ACTIVE)
    {
        if (sound.m_bStopBufferAfterFade)
            return true;
    }
    else
    {
        ++g_numSoundChannelsUsed;
        buffer->AddRef();
        sound.m_pSoundBuffer = buffer;
    }

    sound.m_fTargetVolume = fTargetVolume;
    sound.m_fCurVolume = fCurVolume;
    sound.m_fStartVolume = fCurVolume;
    sound.m_fVolumeDiff = fTargetVolume - fCurVolume;
    sound.m_bStopBufferAfterFade = bStopBufferAfterFade;

    if (fadeTime == -2)
        sound.m_wFadeTime = (dwStatus & DSBSTATUS_LOCHARDWARE) ? 20 : 28;
    else if (fadeTime == -1)
        sound.m_wFadeTime = (dwStatus & DSBSTATUS_LOCHARDWARE) ? 20 : 30;
    else
        sound.m_wFadeTime = fadeTime;

    sound.m_nStartTime = m_nLastServiceTime;
    sound.m_nStatus = eSmoothFadeEntryStatus::STATE_ACTIVE;

    return true;
}

void CAESmoothFadeThread::SetBufferVolume(IDirectSoundBuffer* buffer, float volume)
{
    const auto dwVolume = static_cast<LONG>(volume * 100.0F);
    if (m_bThreadInvalid)
    {
        buffer->SetVolume(dwVolume);
        return;
    }

    int entryInd;
    for (entryInd = 0; entryInd < NUM_SMOOTHFADE_ENTRIES; ++entryInd)
    {
        auto& entry = m_aEntries[entryInd];
        if (entry.m_nStatus == eSmoothFadeEntryStatus::STATE_ACTIVE && entry.m_pSoundBuffer == buffer)
            break;
    }

    if (entryInd >= NUM_SMOOTHFADE_ENTRIES)
        buffer->SetVolume(dwVolume);
    else
    {
        auto& entry = m_aEntries[entryInd];
        if (entry.m_bStopBufferAfterFade || approxEqual2(volume, entry.m_fTargetVolume, 0.01F))
            return;

        entry.m_nStatus = eSmoothFadeEntryStatus::STATE_CANCELLED;
        buffer->SetVolume(dwVolume);
    }
}

DWORD WINAPI CAESmoothFadeThread::SmoothFadeProc(void* pSmoothFade)
{
    auto* pFade = static_cast<CAESmoothFadeThread*>(pSmoothFade);
    while (pFade->m_bActive)
    {
        pFade->Service();
        Sleep(1);
    }

    return 0;
}
