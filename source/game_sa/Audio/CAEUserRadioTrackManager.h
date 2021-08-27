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

class CAEUserRadioTrackManager {
public:
    tUserTracksInfo*    m_pUserTracksInfo;
    bool                m_bUserTracksLoaded;
    bool                m_bUserTracksLoadedCopy;
    uint16_t            m_nUserTracksCount;
    bool                m_baDecodersSupported[MAX_SUPPORTED_DECODERS]; // index with eAudioFileType
    DWORD               m_nUserTracksScanThreadID;
    HANDLE              m_hwndUserTracksScanThreadHandle;
    eUserTrackScanState m_nUserTracksScanState;

    static CAEUserRadioTrackManager& instance;

public:
    bool Initialise();
    void Shutdown();

    char* GetTrackPath(int32_t trackID);
    CAEStreamingDecoder* LoadUserTrack(int32_t trackID);
    bool ReadUserTracks();
    bool ScanUserTracks();
    void DeleteUserTracksInfo();
    void SetUserTrackIndex(int32_t index);
    int32_t SelectUserTrackIndex();

    eAudioFileType GetAudioFileType(const char* filename);
    bool IsShortcut(const char* path);
    uint8_t GetUserTrackPlayMode();

private:
    static tAudioExtensionType (&audioExtensionTypes)[7];

    static DWORD __stdcall WriteUserTracksThread(CAEUserRadioTrackManager* self);
    int WriteUserTracksFile(const char* dir, size_t& currentLength, FILE* file, std::vector<tUserTracksInfo>& offsets, int depth);
    char* ResolveShortcut(const char* path);

// Private functions which aren't part of GTASA itself
private:
    int WriteUserTracksFile(const std::wstring& dir, size_t& currentLength, FILE* file, std::vector<tUserTracksInfo>& offsets, int depth);

    static std::wstring ResolveShortcut(const std::wstring& path);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
};

VALIDATE_SIZE(CAEUserRadioTrackManager, 0x1c);
