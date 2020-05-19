#pragma once
#include <windows.h>
#include "Queue.h"

enum class eCdStreamStatus : std::int32_t
{
    READING_SUCCESS = 0,
    WAITING_TO_READ = 250,
    READING_FAILURE = 254,
    READING = 255,
};

union SyncObj
{
    HANDLE hSemaphore;
    CONDITION_VARIABLE cv;
};

struct CdStream	// sizeof = 0x30
{
    std::uint32_t nSectorOffset;
    std::uint32_t nSectorsToRead;
    LPVOID lpBuffer;
    BYTE field_C;
    bool bLocked;
    bool bInUse;
    BYTE field_F;
    eCdStreamStatus status;
    SyncObj sync;
    HANDLE hFile;
    OVERLAPPED overlapped;
};

struct CdStreamInfoSA	// sizeof = 0x8CC
{
    DWORD streamCreateFlags;
    BOOL streamingInitialized;
    BOOL overlappedIO;
    Queue m_queue;
    CdStream* pStreams;
    DWORD thread_id;
    HANDLE semaphore;
    HANDLE thread;
    HANDLE streamHandles[32];
    DWORD streamCount;
    DWORD openStreamCount;
    CHAR  streamNames[2048];
    DWORD field_8A8;
    DWORD lastPosn;
    DWORD field_8B0;
    DWORD field_8B4;
    DWORD gtaint_id;
    DWORD gta3_id;
};

static_assert(sizeof(SyncObj) == sizeof(HANDLE), "Incorrect struct size: SyncObj");
static_assert(sizeof(CdStreamInfoSA) == 0x8CC, "Incorrect struct size: CdStreamInfoSA");
static_assert(sizeof(CdStream) == 0x30, "Incorrect struct size: CdStream");

const std::int32_t MAX_CD_STREAM_HANDLES = 32;
const std::int32_t MAX_CD_STREAM_IMAGE_NAME_SIZE = 64;

extern HANDLE(&gStreamFileHandles)[MAX_CD_STREAM_HANDLES];
extern char(&gCdImageNames)[MAX_CD_STREAM_HANDLES][MAX_CD_STREAM_IMAGE_NAME_SIZE];
extern std::uint32_t& gStreamFileCreateFlags;
extern CdStream*& gCdStreams;
extern std::int32_t& gStreamCount;
extern std::int32_t& gOpenStreamCount;
extern std::int32_t& gStreamingInitialized;
extern std::int32_t& gOverlappedIO;
extern Queue& gStreamQueue;
extern HANDLE& gStreamSemaphore;
extern HANDLE& gStreamingThread;
extern DWORD& gStreamingThreadId;
extern std::uint32_t& gLastCdStreamPosn;

void InjectCdStreamHooks();
std::int32_t __cdecl CdStreamOpen(const char* lpFileName);
eCdStreamStatus __cdecl CdStreamSync(std::int32_t streamId);
eCdStreamStatus __cdecl CdStreamGetStatus(std::int32_t streamId);
bool __cdecl CdStreamRead(std::int32_t streamId, std::uint8_t* lpBuffer, std::uint32_t offsetAndHandle, std::int32_t sectorCount);
static std::uint32_t __cdecl CdStreamGetLastPosn() { return gLastCdStreamPosn; }
DWORD WINAPI CdStreamThread(LPVOID lpParam);
void __cdecl CdStreamInitThread();
void __cdecl CdStreamInit(std::int32_t streamCount);
void __cdecl CdStreamRemoveImages();
void __cdecl CdStreamShutdown();
