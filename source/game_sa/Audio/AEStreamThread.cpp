#include "StdInc.h"

#include "AEStreamThread.h"
#include "AEAudioUtility.h"
#include "AEMP3TrackLoader.h"

void CAEStreamThread::InjectHooks() {
    RH_ScopedClass(CAEStreamThread);
    RH_ScopedCategory("Audio");

    RH_ScopedInstall(Initialise, 0x4F1680);
    RH_ScopedInstall(Start, 0x4F11F0);
    RH_ScopedInstall(Stop, 0x4F1590);
    RH_ScopedInstall(Pause, 0x4F1200);
    RH_ScopedInstall(Resume, 0x4F1210);
    RH_ScopedInstall(WaitForExit, 0x4F1220);
    RH_ScopedInstall(PlayTrack, 0x4F1230);
    RH_ScopedInstall(GetTrackPlayTime, 0x4F1530);
    RH_ScopedInstall(GetTrackLengthMs, 0x4F1550);
    RH_ScopedInstall(GetActiveTrackID, 0x4F1560);
    RH_ScopedInstall(GetPlayingTrackID, 0x4F1570);
    RH_ScopedInstall(StopTrack, 0x4F1580);
    RH_ScopedInstall(MainLoop, 0x4F15C0);
}

// 0x4F11E0
CAEStreamThread::~CAEStreamThread() {
    OS_MutexRelease(&m_criticalSection);
}

// 0x4F1680
bool CAEStreamThread::Initialise(CAEStreamingChannel* streamingChannel) {
    m_bActive          = true;
    m_bThreadActive    = false;
    field_12           = 0;
    m_bPreparingStream = 0;
    m_bStopRequest     = false;
    m_nPlayingTrackId  = streamingChannel->GetPlayingTrackID();
    m_nPlayTime        = streamingChannel->GetPlayTime();
    m_nActiveTrackId   = streamingChannel->GetActiveTrackID();
    m_nTrackLengthMs   = streamingChannel->GetLength();

    m_nHandle = CreateThread(nullptr, 0, &CAEStreamThread::MainLoop, this, CREATE_SUSPENDED, (LPDWORD)(&m_lpThreadId));
    assert(m_nHandle);
    SetThreadPriority(m_nHandle, 0);
    InitializeCriticalSection(&m_criticalSection);

    OS_MutexObtain(&m_criticalSection);
    m_pStreamingChannel = streamingChannel;

    m_pMp3TrackLoader = new CAEMP3TrackLoader();
    m_pMp3TrackLoader->Initialise();

    return m_bActive;
}

// 0x4F11F0
void CAEStreamThread::Start() {
    m_bThreadActive = true;
    ResumeThread(m_nHandle);
}

// 0x4F1590
void CAEStreamThread::Stop() {
    m_bThreadActive = false;
    if (std::exchange(m_bActive, false)) {
        delete m_pMp3TrackLoader;
    }
}

// 0x4F1200
void CAEStreamThread::Pause() const {
    SuspendThread(m_nHandle);
}

// 0x4F1210
void CAEStreamThread::Resume() const {
    ResumeThread(m_nHandle);
}

// 0x4F1220
void CAEStreamThread::WaitForExit() const {
    WaitForSingleObject(m_nHandle, INFINITE);
}

// 0x4F1530
int16 CAEStreamThread::GetTrackPlayTime() const {
    if (m_bPreparingStream)
        return -8;
    else
        return m_pStreamingChannel->GetPlayTime();
}

// 0x4F1550
int32 CAEStreamThread::GetTrackLengthMs() const {
    return m_nTrackLengthMs;
}

// 0x4F1560
int32 CAEStreamThread::GetActiveTrackID() const {
    return m_nActiveTrackId;
}

// 0x4F1570
int32 CAEStreamThread::GetPlayingTrackID() const {
    return m_nPlayingTrackId;
}

// 0x4F1230
void CAEStreamThread::PlayTrack(uint32 iTrackId, int32 iNextTrackId, uint32 a3, int32 a4, bool bIsUserTrack, bool bNextIsUserTrack) {
    OS_MutexObtain(&m_criticalSection);

    if (m_pStreamingChannel->GetPlayTime() == -2) {
        m_pStreamingChannel->Stop();
    }

    m_iTrackId         = iTrackId;
    m_iNextTrackId     = iNextTrackId;
    field_1C           = a3;
    field_24           = a4;
    m_bIsUserTrack     = bIsUserTrack;
    m_bNextIsUserTrack = bNextIsUserTrack;
    field_12           = 1;

    OS_MutexRelease(&m_criticalSection);
}

// 0x4F1580
void CAEStreamThread::StopTrack() {
    m_bStopRequest = true;
}

// 0x4F15C0
DWORD WINAPI CAEStreamThread::MainLoop(LPVOID data) {
#ifdef TRACY_ENABLE
    tracy::SetThreadName("AEStreamThread");
#endif

    const auto self = reinterpret_cast<CAEStreamThread*>(data);

    bool wasForeground = true;
    bool play = false;

    while (self->m_bThreadActive) {
        ZoneScoped;

        bool isForeground = IsForegroundApp();
        if (isForeground) {
            if (!wasForeground && play){
                self->m_pStreamingChannel->Play(0, 0, 1.0f);
            }

            auto start = CAEAudioUtility::GetCurrentTimeInMS();
            self->Service();
            self->m_pStreamingChannel->Service();
            auto end = CAEAudioUtility::GetCurrentTimeInMS();
            if (end - start < 5) {
                OS_ThreadSleep(uint32(start - end + 5));
            }
        } else if (wasForeground) {
            if (self->m_pStreamingChannel->IsBufferPlaying()) {
                self->m_pStreamingChannel->Pause();
                play = true;
            } else {
                play = false;
            }
        }
        wasForeground = isForeground;
        OS_ThreadSleep(100);
    }

    return 0;
}

// 0x4F1290
void CAEStreamThread::Service() {
    plugin::CallMethod<0x4F1290, CAEStreamThread*>(this);
}
