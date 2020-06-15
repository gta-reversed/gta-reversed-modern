#pragma once

#include <cstdint>
#include <cstdio>

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// MF
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#include "CAEStreamingDecoder.h"

#include "eUserTrackPlayMode.h"
#include "eUserTrackScanState.h"
#include "tAudioExtensionType.h"
#include "tUserTracksInfo.h"

constexpr size_t MAX_SUPPORTED_DECODERS = 8;

class CAEUserRadioTrackManager
{
public:
    static CAEUserRadioTrackManager &instance;
    
    bool Initialise();
    void Shutdown();
    char *GetTrackPath(std::int32_t trackID);
    CAEStreamingDecoder *LoadUserTrack(std::int32_t trackID);
    bool ReadUserTracks();
    bool ScanUserTracks();
    void DeleteUserTracksInfo();
    void SetUserTrackIndex(std::int32_t index);
    std::int32_t SelectUserTrackIndex();
    
    eAudioFileType GetAudioFileType(const char *filename);
    bool IsShortcut(const char *path);
    std::uint8_t GetUserTrackPlayMode();

public:
    tUserTracksInfo *userTracksInfo;
    bool userTracksLoaded;
    bool _userTracksLoadedCopy;
    std::uint16_t userTracksCount;
    bool decodersSupported[MAX_SUPPORTED_DECODERS]; // index with eAudioFileType
    DWORD userTracksScanThreadID;
    HANDLE userTracksScanThreadHandle;
    eUserTrackScanState userTracksScanState;

private:
    static tAudioExtensionType (&audioExtensionTypes)[7];

    static DWORD __stdcall WriteUserTracksThread(CAEUserRadioTrackManager *self);
    int WriteUserTracksFile(const char *dir, size_t &currentLength, FILE *file, std::vector<tUserTracksInfo> &offsets, int depth);
    char *ResolveShortcut(const char *path);

// Private functions which aren't part of GTASA itself
private:
    int WriteUserTracksFile(const std::wstring &dir, size_t &currentLength, FILE *file, std::vector<tUserTracksInfo> &offsets, int depth);

    static std::wstring ResolveShortcut(const std::wstring &path);

private:
    friend void InjectHooksMain(void);
    static void InjectHooks();
};

VALIDATE_SIZE(CAEUserRadioTrackManager, 0x1c);
