#include "StdInc.h"

HANDLE(&gStreamFileHandles)[MAX_CD_STREAM_HANDLES] = *(HANDLE(*)[MAX_CD_STREAM_HANDLES])0x8E4010;
char(&gCdImageNames)[MAX_CD_STREAM_HANDLES][MAX_CD_STREAM_IMAGE_NAME_SIZE] = *(char(*)[MAX_CD_STREAM_HANDLES][MAX_CD_STREAM_IMAGE_NAME_SIZE])0x8E4098;
std::uint32_t& gStreamFileCreateFlags = *(std::uint32_t*)0x8E3FE0;
CdStream*& gCdStreams = *(CdStream**)0x8E3FFC;
std::int32_t& gStreamCount = *(std::int32_t*)0x8E4090;
std::int32_t& gOpenStreamCount = *(std::int32_t*)0x8E4094;
std::int32_t& gStreamingInitialized = *(std::int32_t*)0x8E3FE4;
std::int32_t& gOverlappedIO = *(std::int32_t*)0x8E3FE8;
Queue& gStreamQueue = *(Queue*)0x8E3FEC;
HANDLE& gStreamSemaphore = *(HANDLE*)0x8E4004;
HANDLE& gStreamingThread = *(HANDLE*)0x8E4008;
DWORD& gStreamingThreadId = *(DWORD*)0x8E4000;
std::uint32_t& gLastCdStreamPosn = *(std::uint32_t*)0x8E4898;

#define APPLY_CD_STREAM_DEADLOCK_FIX 1

#ifdef APPLY_CD_STREAM_DEADLOCK_FIX
// thanks to http://forums.codeguru.com/showthread.php?175474-a-CCriticalSection-question
class CSync
{
public:
    CSync() { InitializeCriticalSection(&m_CriticalSection); }
    ~CSync() { DeleteCriticalSection(&m_CriticalSection); }
    void Acquire() { EnterCriticalSection(&m_CriticalSection); }
    void Release() { LeaveCriticalSection(&m_CriticalSection); }
private:
    CRITICAL_SECTION m_CriticalSection;
};


class CLockGuard
{
public:
    CLockGuard(CSync& refSync) : m_refSync(refSync) { Lock(); }
    ~CLockGuard() { Unlock(); }
private:
    CSync& m_refSync;
    CLockGuard(const CLockGuard& refcSource);
    CLockGuard& operator=(const CLockGuard& refcSource);
public:
    void Lock() { m_refSync.Acquire(); }
    void Unlock() { m_refSync.Release(); }
};

static CSync cdStreamThreadSync;
#endif

void InjectCdStreamHooks()
{
    HookInstall(0x4067B0, &CdStreamOpen);
    HookInstall(0x406460, &CdStreamSync);
    HookInstall(0x4063E0, &CdStreamGetStatus);
    HookInstall(0x406A20, &CdStreamRead);
    HookInstall(0x406560, &CdStreamThread);
    HookInstall(0x4068F0, &CdStreamInitThread);
    HookInstall(0x406B70, &CdStreamInit);
    HookInstall(0x406690, &CdStreamRemoveImages);
    HookInstall(0x406370, &CdStreamShutdown);
}

std::int32_t __cdecl CdStreamOpen(const char* lpFileName)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<std::int32_t, 0x4067B0, const char*>(lpFileName);
#else
    std::int32_t freeHandleIndex = 0;
    for (; freeHandleIndex < MAX_CD_STREAM_HANDLES; freeHandleIndex++) {
        if (!gStreamFileHandles[freeHandleIndex])
            break;
    }
    SetLastError(NO_ERROR);
    const DWORD dwFlagsAndAttributes = gStreamFileCreateFlags | FILE_ATTRIBUTE_READONLY | FILE_FLAG_RANDOM_ACCESS;
    HANDLE file = CreateFileA(lpFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, dwFlagsAndAttributes, NULL);
    gStreamFileHandles[freeHandleIndex] = file;
    if (file == INVALID_HANDLE_VALUE)
        return 0;
    strncpy(gCdImageNames[freeHandleIndex], lpFileName, MAX_CD_STREAM_IMAGE_NAME_SIZE);
    return freeHandleIndex << 24;
#endif
}

// This function halts the caller thread if CdStreamThread is still reading the file to "sync" it.
// CdStreamSync is always called from the main thread. It's called when entering or exiting
// interiors. It's used when the game wants a model to be loaded immediately,
// like when spawning after exiting interiors.
// This function was responsible for causing the deadlock since it was not thread-safe.
// The deadlock problem only exists on PC version of SA. R* fixed it on android.
// So it's fixed here because we used a critical section for it.
// Workflow:
// 1. CdStreamRead is called on the main thread and signals gStreamSemaphore to
//    read game asset in a secondary thread a.k.a CdStreamThread.
// 2. CdStreamThread starts reading the file on the secondary thread, and the main thread
//    immediately calls CdStreamSync to stop the main thread from execution until the model data has been read from the file.
// 3. When CdStreamThread is done reading the file, it signals `stream.sync.hSemaphore`, so the main thread can
//    continue exectuting code and continue the gameplay. 
eCdStreamStatus __cdecl CdStreamSync(std::int32_t streamId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<eCdStreamStatus, 0x406460, std::int32_t>(streamId);
#else
    CdStream& stream = gCdStreams[streamId];
#ifdef APPLY_CD_STREAM_DEADLOCK_FIX
    CLockGuard lockGuard(cdStreamThreadSync);
#endif
    if (gStreamingInitialized) {
        if (stream.nSectorsToRead) {
            stream.bLocked = true;
#ifdef APPLY_CD_STREAM_DEADLOCK_FIX
            lockGuard.Unlock();
#endif
            WaitForSingleObject(stream.sync.hSemaphore, INFINITE);
#ifdef APPLY_CD_STREAM_DEADLOCK_FIX
            lockGuard.Lock();
#endif
        }
        stream.bInUse = false;
        return stream.status;
    }
    else if (gOverlappedIO && stream.hFile) {
        DWORD numberOfBytesTransferred = 0;
        if (!GetOverlappedResult(stream.hFile, &stream.overlapped, &numberOfBytesTransferred, true))
            return eCdStreamStatus::READING_FAILURE;
    }
    return eCdStreamStatus::READING_SUCCESS;
#endif
}

eCdStreamStatus __cdecl CdStreamGetStatus(std::int32_t streamId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<eCdStreamStatus, 0x4063E0, std::int32_t>(streamId);
#else
    CdStream& stream = gCdStreams[streamId];
    if (gStreamingInitialized) {
        if (stream.bInUse)
            return eCdStreamStatus::READING;
        if (stream.nSectorsToRead)
            return eCdStreamStatus::WAITING_TO_READ;
        if (stream.status != eCdStreamStatus::READING_SUCCESS) {
            const eCdStreamStatus status = stream.status;
            stream.status = eCdStreamStatus::READING_SUCCESS;
            return status;
        }
    }
    else if (gOverlappedIO) {
        if (WaitForSingleObjectEx(stream.hFile, 0, 1) != WAIT_OBJECT_0)
            return eCdStreamStatus::READING;
    }
    return eCdStreamStatus::READING_SUCCESS;
#endif
}

// When CdStreamRead is called, it will update CdStream information for the channel and
// signal gStreamSemaphore, so the secondary thread `CdStreamThread` can start reading the model
// If this function is called with the same channelId/streamId whilst CdStreamThread is still reading the previous model
// for the channel, then it will return false.
// When CdStreamThread is done reading the model, then CdStreamThread will set `stream.nSectorsToRead` and `stream.bInUse` to 0,
// so the main thread can call CdStreamRead again to read more models.
bool __cdecl CdStreamRead(std::int32_t streamId, std::uint8_t* lpBuffer, std::uint32_t offsetAndHandle, std::int32_t sectorCount)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x406A20, std::int32_t, std::uint8_t*, std::uint32_t, std::int32_t>(streamId, lpBuffer, offsetAndHandle, sectorCount);
#else
    CdStream& stream = gCdStreams[streamId];
    gLastCdStreamPosn = sectorCount + offsetAndHandle;
    const std::uint32_t sectorOffset = offsetAndHandle & 0xFFFFFF;
    stream.hFile = gStreamFileHandles[offsetAndHandle >> 24];
    SetLastError(NO_ERROR);
    if (gStreamingInitialized) {
        if (stream.nSectorsToRead || stream.bInUse)
            return false;
        stream.status = eCdStreamStatus::READING_SUCCESS;
        stream.nSectorOffset = sectorOffset;
        stream.nSectorsToRead = sectorCount;
        stream.lpBuffer = lpBuffer;
        stream.bLocked = false;
        AddToQueue(&gStreamQueue, streamId);
        if (!ReleaseSemaphore(gStreamSemaphore, 1, 0))
            printf("Signal Sema Error\n");
        return true;
    }
    const DWORD numberOfBytesToRead = sectorCount * STREAMING_SECTOR_SIZE;
    const DWORD overlappedOffset = sectorOffset * STREAMING_SECTOR_SIZE;
    if (gOverlappedIO) {
        LPOVERLAPPED overlapped = &gCdStreams[streamId].overlapped;
        overlapped->Offset = overlappedOffset;
        if (ReadFile(stream.hFile, lpBuffer, numberOfBytesToRead, NULL, overlapped) || GetLastError() == ERROR_IO_PENDING)
            return true;
        return false;
    }
    SetFilePointer(stream.hFile, overlappedOffset, 0, 0);
    DWORD numberOfBytesRead = 0;
    return ReadFile(stream.hFile, lpBuffer, numberOfBytesToRead, &numberOfBytesRead, 0);
#endif
}

DWORD WINAPI CdStreamThread(LPVOID lpParam)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<DWORD, 0x406560, LPVOID>(lpParam);
#else
    while (true) {
        WaitForSingleObject(gStreamSemaphore, INFINITE);
        const std::int32_t streamId = GetFirstInQueue(&gStreamQueue);
        CdStream& stream = gCdStreams[streamId];
        stream.bInUse = true;
        if (stream.status == eCdStreamStatus::READING_SUCCESS) {
            const DWORD numberOfBytesToRead = stream.nSectorsToRead * STREAMING_SECTOR_SIZE;
            const DWORD overlappedOffset = stream.nSectorOffset * STREAMING_SECTOR_SIZE;
            if (gOverlappedIO) {
                stream.overlapped.Offset = overlappedOffset;
                if (ReadFile(stream.hFile, stream.lpBuffer, numberOfBytesToRead, NULL, &stream.overlapped)) {
                    stream.status = eCdStreamStatus::READING_SUCCESS;
                }
                else if (GetLastError() != ERROR_IO_PENDING) {
                    stream.status = eCdStreamStatus::READING_FAILURE;
                }
                else {
                    DWORD numberOfBytesTransferred = 0;
                    if (GetOverlappedResult(stream.hFile, &stream.overlapped, &numberOfBytesTransferred, true))
                        stream.status = eCdStreamStatus::READING_SUCCESS;
                    else
                        stream.status = eCdStreamStatus::READING_FAILURE;
                }
            }
            else {
                SetFilePointer(stream.hFile, overlappedOffset, 0u, 0u);
                DWORD numberOfBytesRead = 0;
                if (ReadFile(stream.hFile, stream.lpBuffer, numberOfBytesToRead, &numberOfBytesRead, NULL))
                    stream.status = eCdStreamStatus::READING_SUCCESS;
                else
                    stream.status = eCdStreamStatus::READING_FAILURE;
            }
        }
        RemoveFirstInQueue(&gStreamQueue);
#ifdef APPLY_CD_STREAM_DEADLOCK_FIX
        CLockGuard lockGuard(cdStreamThreadSync);
#endif
        // locking is necessary here, so ReleaseSemaphore is not called before WaitForSingleObject
        // in CdStreamSync to avoid causing a deadlock.
        stream.nSectorsToRead = 0;
        if (stream.bLocked)
            ReleaseSemaphore(stream.sync.hSemaphore, 1, 0);
        stream.bInUse = false;
    }
    return 0;
#endif
}

void __cdecl CdStreamInitThread()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x4068F0>();
#else
    SetLastError(NO_ERROR);
    for (std::int32_t i = 0; i < gStreamCount; i++) {
        HANDLE hSemaphore = CreateSemaphoreA(0, 0, 2, 0);
        gCdStreams[i].sync.hSemaphore = hSemaphore;
        if (!hSemaphore) {
            printf("%s: failed to create sync semaphore\n", "cdvd_stream");
            return;
        }
    }
    InitialiseQueue(&gStreamQueue, gStreamCount + 1);
    gStreamSemaphore = CreateSemaphoreA(0, 0, 5, "CdStream");
    if (gStreamSemaphore) {
        gStreamingThread = CreateThread(NULL, 0x10000, CdStreamThread, NULL, CREATE_SUSPENDED, &gStreamingThreadId);
        if (gStreamingThread) {
            SetThreadPriority(gStreamingThread, GetThreadPriority(GetCurrentThread()));
            ResumeThread(gStreamingThread);
        }
        else {
            printf("%s: failed to create streaming thread\n", "cdvd_stream");
        }
    }
    else {
        printf("%s: failed to create stream semaphore\n", "cdvd_stream");
    }
#endif
}

void __cdecl CdStreamInit(std::int32_t streamCount)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x406B70, std::int32_t>(streamCount);
#else
    for (std::int32_t i = 0; i < MAX_CD_STREAM_HANDLES; i++) {
        gStreamFileHandles[i] = 0;
        gCdImageNames[i][0] = 0;
    }
    DWORD bytesPerSector = 0;
    DWORD totalNumberOfClusters = 0;
    DWORD numberOfFreeClusters = 0;
    DWORD sectorsPerCluster = 0;
    GetDiskFreeSpaceA(nullptr, &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters, &totalNumberOfClusters);
    gStreamFileCreateFlags = FILE_FLAG_OVERLAPPED;
    if (bytesPerSector <= STREAMING_SECTOR_SIZE)
        gStreamFileCreateFlags |= FILE_FLAG_NO_BUFFERING;
    gOverlappedIO = 1;
    gStreamingInitialized = 0;
    std::uint8_t* pAllocatedMemory = CMemoryMgr::MallocAlign(STREAMING_SECTOR_SIZE, bytesPerSector);
    SetLastError(NO_ERROR);
    gOpenStreamCount = 0;
    gStreamCount = streamCount;
    gCdStreams = (CdStream*)LocalAlloc(LPTR, sizeof(CdStream) * streamCount);
    CdStreamOpen("MODELS\\GTA3.IMG");
    bool bStreamRead = CdStreamRead(0, pAllocatedMemory, 0, 1);
    CdStreamRemoveImages();
    gStreamingInitialized = 1;
    if (!bStreamRead) {
        gOverlappedIO = 0;
        gStreamFileCreateFlags &= ~FILE_FLAG_OVERLAPPED;
    }
    CdStreamInitThread();
    CMemoryMgr::FreeAlign(pAllocatedMemory);
#endif
}


void __cdecl CdStreamRemoveImages()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x406690>();
#else
    for (std::int32_t i = 0; i < gStreamCount; ++i) {
        CdStreamSync(i);
    }
    for (std::int32_t i = 0; i < gOpenStreamCount; i++) {
        SetLastError(NO_ERROR);
        if (gStreamFileHandles[i])
            CloseHandle(gStreamFileHandles[i]);
        gStreamFileHandles[i] = 0;
        gCdImageNames[i][0] = 0;
    }
    gOpenStreamCount = 0;
#endif
}

void __cdecl CdStreamShutdown()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x406370>();
#else
    if (gStreamingInitialized) {
        FinalizeQueue(&gStreamQueue);
        CloseHandle(gStreamSemaphore);
        CloseHandle(gStreamingThread);
        for (std::int32_t i = 0; i < gStreamCount; i++) {
            CloseHandle(gCdStreams[i].sync.hSemaphore);
        }
    }
    LocalFree(gCdStreams);
#endif
}
