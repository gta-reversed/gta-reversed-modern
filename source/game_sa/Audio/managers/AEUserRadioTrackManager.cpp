#include "StdInc.h" // TODO: Remove

#include <cstdio>

// COM
#include <ShObjIdl.h>

#include "common.h"

#include "AEUserRadioTrackManager.h"

#include "AEAudioUtility.h"
#include "AEDataStream.h"
#include "AEMFDecoder.h"
#include "AEWaveDecoder.h"
#include "AEWMADecoder.h"
#include "AEVorbisDecoder.h"

#include "FileMgr.h"
#include "MenuManager.h"

CAEUserRadioTrackManager& AEUserRadioTrackManager = *(CAEUserRadioTrackManager*)0xB6B970;

#if 0
// This is the default list
static tAudioExtensionType defaultAudioExtensionTypes[] = {
    {".ogg", AUDIO_FILE_TYPE_VORBIS},
    {".mp3", AUDIO_FILE_TYPE_QUICKTIME}, // replaced to AUDIO_FILE_TYPE_WMA if QuickTime is not installed
    {".wav", AUDIO_FILE_TYPE_WAV},
    {".wma", AUDIO_FILE_TYPE_WMA},
    {".wmv", AUDIO_FILE_TYPE_WMA},
    {".aac", AUDIO_FILE_TYPE_QUICKTIME},
    {".m4a", AUDIO_FILE_TYPE_QUICKTIME},
};
#endif
tAudioExtensionType (&CAEUserRadioTrackManager::audioExtensionTypes)[7] = *reinterpret_cast<tAudioExtensionType (*)[7]>(0x8cbb28);

// 0x4f35b0
bool CAEUserRadioTrackManager::Initialise() {
    m_bUserTracksLoaded = ReadUserTracks();
    m_bUserTracksLoadedCopy = m_bUserTracksLoaded;
    memset(m_baDecodersSupported, 0, sizeof(m_baDecodersSupported));
    m_baDecodersSupported[AUDIO_FILE_TYPE_VORBIS] = true;
    m_baDecodersSupported[AUDIO_FILE_TYPE_WAV] = true;
    m_baDecodersSupported[AUDIO_FILE_TYPE_WMA] = CAEWMADecoder::InitLibrary();
    m_baDecodersSupported[AUDIO_FILE_TYPE_QUICKTIME] = CAEMFDecoder::InitLibrary();

    if (m_baDecodersSupported[AUDIO_FILE_TYPE_QUICKTIME] == false)
        // change MP3 decoder from QuickTime to WMA
        audioExtensionTypes[1].type = AUDIO_FILE_TYPE_WMA;

    return true;
}

// 0x4f2fb0
void CAEUserRadioTrackManager::Shutdown() {
    if (m_bUserTracksLoaded && m_pUserTracksInfo) {
        CMemoryMgr::Free(m_pUserTracksInfo);
        m_pUserTracksInfo = nullptr;
    }

    CAEWMADecoder::Shutdown();
    CAEMFDecoder::Shutdown();
}

// 0x4f3050
char* CAEUserRadioTrackManager::GetTrackPath(int32 trackID) const {
    if (trackID >= static_cast<int32>(m_nUserTracksCount))
        return nullptr;

    CFileMgr::SetDirMyDocuments();
    FILESTREAM ufiles = CFileMgr::OpenFile("sa-ufiles.dat", "rb");
    CFileMgr::SetDir("");

    if (ufiles == nullptr)
        return nullptr;

    tUserTracksInfo& targetOffset = m_pUserTracksInfo[trackID];
    char*            dest = new char[targetOffset.pathLength + 1];

    CFileMgr::Seek(ufiles, targetOffset.startUfilesPath, SEEK_SET);
    CFileMgr::Read(ufiles, dest, targetOffset.pathLength);
    CFileMgr::CloseFile(ufiles);

    // NULL-terminate the path
    dest[targetOffset.pathLength] = 0;
    return dest;
}

// 0x4f35f0
CAEStreamingDecoder* CAEUserRadioTrackManager::LoadUserTrack(int32 trackID) {
    if (m_bUserTracksLoaded == false)
        return nullptr;

    if (trackID < 0 || trackID >= m_nUserTracksCount)
        return nullptr;

    tUserTracksInfo& targetOffset = m_pUserTracksInfo[trackID];
    if (m_baDecodersSupported[targetOffset.fileType] == false)
        return nullptr;

    char* filename = GetTrackPath(trackID);
    if (filename == nullptr)
        return nullptr;

    CAEStreamingDecoder* decoder = nullptr;

    // QuickTime decoder doesn't need the data stream
    if (targetOffset.fileType == AUDIO_FILE_TYPE_QUICKTIME)
        // MikuAuahDark: We've agreed to replace QuickTime with MediaFoundation
        decoder = new CAEMFDecoder(filename, trackID);
    else {
        CAEDataStream* dataStream = new CAEDataStream(trackID, filename, 0, 0, false);

        CFileMgr::SetDirMyDocuments();
        bool dataStreamInitialized = dataStream->Initialise();
        CFileMgr::SetDir("");

        if (dataStreamInitialized == false) {
            delete dataStream;
            return nullptr;
        }

        switch (targetOffset.fileType) {
        case AUDIO_FILE_TYPE_UNKNOWN:
        default: {
            delete dataStream;
            return nullptr;
        }
        case AUDIO_FILE_TYPE_VORBIS: {
            decoder = new CAEVorbisDecoder(dataStream, true);
            break;
        }
        case AUDIO_FILE_TYPE_WAV: {
            decoder = new CAEWaveDecoder(dataStream);
            break;
        }
        case AUDIO_FILE_TYPE_WMA: {
            decoder = new CAEWMADecoder(dataStream);
            break;
        }
        }
    }

    return decoder;
}

// 0x4f2fd0
bool CAEUserRadioTrackManager::ReadUserTracks() {
    CFileMgr::SetDirMyDocuments();
    auto file = CFileMgr::OpenFile("sa-utrax.dat", "rb");
    CFileMgr::SetDir("");

    if (file == nullptr)
        return false;

    auto size = CFileMgr::GetTotalSize(file);
    if (size == 0) {
        CFileMgr::CloseFile(file);
        return false;
    }

    m_nUserTracksCount = size / sizeof(tUserTracksInfo);

    if (m_pUserTracksInfo) {
        CMemoryMgr::Free(m_pUserTracksInfo);
    }
    m_pUserTracksInfo = (tUserTracksInfo*)CMemoryMgr::Malloc(size);

    CFileMgr::Read(file, m_pUserTracksInfo, size);
    CFileMgr::CloseFile(file);

    return true;
}

// 0x4f4ba0
bool CAEUserRadioTrackManager::ScanUserTracks() {
    switch (m_nUserTracksScanState) {
    case USER_TRACK_SCAN_OFF: {
        m_nUserTracksScanState = USER_TRACK_SCAN_IN_PROGRESS;
        m_hwndUserTracksScanThreadHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)WriteUserTracksThread, this, 0, &m_nUserTracksScanThreadID);
        // no "break"
    }
    case USER_TRACK_SCAN_IN_PROGRESS:
        return false;
    case USER_TRACK_SCAN_COMPLETE:
    case USER_TRACK_SCAN_ERROR:
        return true;
    default:
        return false;
    }
}

// 0x4f32f0
void CAEUserRadioTrackManager::DeleteUserTracksInfo() {
    TerminateThread(m_hwndUserTracksScanThreadHandle, 0);
    CFileMgr::SetDirMyDocuments();
    remove("sa-ufiles.dat"); // todo: cross-platform
    remove("sa-utrax.dat");
    CFileMgr::SetDir("");

    m_nUserTracksScanState = USER_TRACK_SCAN_OFF;
}

// 0x4f3340
void CAEUserRadioTrackManager::SetUserTrackIndex(int32 index) {
    if (index != -1)
        FrontEndMenuManager.m_nUserTrackIndex = index;
}

// 0x4f3250
int32 CAEUserRadioTrackManager::SelectUserTrackIndex() const {
    if (m_nUserTracksCount > 0 && FrontEndMenuManager.m_nRadioMode >= 0) {
        switch (FrontEndMenuManager.m_nRadioMode) {
        case USER_TRACK_PLAY_RADIO:
        case USER_TRACK_PLAY_RANDOM: {
            if (m_nUserTracksCount == 1)
                return FrontEndMenuManager.m_nUserTrackIndex = 1;
            else {
                int32 index;

                do
                    index = static_cast<int32>(CAEAudioUtility::GetRandomNumberInRange(0, m_nUserTracksCount - 1));
                while (index == FrontEndMenuManager.m_nUserTrackIndex);

                return FrontEndMenuManager.m_nUserTrackIndex = index;
            }
        }
        case USER_TRACK_PLAY_SEQUENTAL: {
            return FrontEndMenuManager.m_nUserTrackIndex = (FrontEndMenuManager.m_nUserTrackIndex + 1) % m_nUserTracksCount;
        }
        }
    }

    return -1;
}

// 0x4f31f0
eAudioFileType CAEUserRadioTrackManager::GetAudioFileType(const char* filename) {
    constexpr size_t AUDIO_EXTENSIONS = sizeof(CAEUserRadioTrackManager::audioExtensionTypes) / sizeof(tAudioExtensionType);
    const char*      dotPosition = strrchr(filename, '.');

    if (dotPosition == nullptr)
        return AUDIO_FILE_TYPE_UNKNOWN;

    for (const tAudioExtensionType& audioExtType : audioExtensionTypes) {
        if (_stricmp(audioExtType.extension, dotPosition) == 0)
            return audioExtType.type;
    }

    return AUDIO_FILE_TYPE_UNKNOWN;
}

// 0x4f32c0
bool CAEUserRadioTrackManager::IsShortcut(const char* path) {
    const char* dot = strrchr(path, '.');
    return dot ? _stricmp(dot, ".lnk") == 0 : false;
}

// 0x4f3330
uint8 CAEUserRadioTrackManager::GetUserTrackPlayMode() {
    return (uint8)FrontEndMenuManager.m_nRadioMode;
}

// 0x4f4a20
DWORD __stdcall CAEUserRadioTrackManager::WriteUserTracksThread(CAEUserRadioTrackManager* self) {
    VERIFY(CoInitialize(nullptr));

    // Open sa-ufiles.dat
    CFileMgr::SetDirMyDocuments();
    auto file = CFileMgr::OpenFile("sa-ufiles.dat", "wb");

    if (file == nullptr)
        self->m_nUserTracksScanState = USER_TRACK_SCAN_ERROR;
    else {
        // Create path to "User Tracks"
        size_t                       documentsDirLen = strlen(CFileMgr::ms_dirName), dummy = 0;
        char*                        userTracksDir = new char[documentsDirLen + 15];
        std::vector<tUserTracksInfo> offsets;

        // Concat
        strcpy(userTracksDir, CFileMgr::ms_dirName);
        strcat(userTracksDir, "\\User Tracks\\");

        // Retrieve all user tracks info
        int32 amountOfTracks = self->WriteUserTracksFile(userTracksDir, dummy, file, offsets, 0);
        CFileMgr::CloseFile(file);

        // Open sa-utrax.dat containing the offsets
        file = CFileMgr::OpenFile("sa-utrax.dat", "wb");

        // todo: FIX_BUGS
        // MikuAuahDark: GTASA doesn't check if sa-utrax.dat fails to open
        if (file == nullptr)
            self->m_nUserTracksScanState = USER_TRACK_SCAN_ERROR;
        else {
            if (amountOfTracks > 0)
                CFileMgr::Write(file, offsets.data(), amountOfTracks * sizeof(tUserTracksInfo));

            CFileMgr::CloseFile(file);

            FrontEndMenuManager.m_nUserTrackIndex = 0;
            self->m_nUserTracksScanState = USER_TRACK_SCAN_COMPLETE;
        }
    }

    // Read user tracks back
    self->m_bUserTracksLoaded = self->ReadUserTracks();
    self->m_bUserTracksLoadedCopy = self->m_bUserTracksLoaded;

    CFileMgr::SetDir("");
    CoUninitialize();
    return 0;
}

// 0x4f4690
int32 CAEUserRadioTrackManager::WriteUserTracksFile(const char* dir, size_t& currentLength, auto file, std::vector<tUserTracksInfo>& offsets, int32 depth) {
    // todo: FIX_BUGS
    return WriteUserTracksFile(UTF8ToUnicode(dir), currentLength, file, offsets, depth);
}

int32 CAEUserRadioTrackManager::WriteUserTracksFile(const std::wstring& dir, size_t& currentLength, auto file, std::vector<tUserTracksInfo>& offsets, int32 depth) {
    // Limit folder scan to 16 folders deep
    if (depth >= 15)
        return 0;

    int32 amountOfTracks = 0;

    // Copy search directory
    std::wstring dirSearch = dir + L"\\*.*";

    WIN32_FIND_DATAW findData;
    HANDLE           findHandle = FindFirstFileW(dirSearch.c_str(), &findData);

    if (findHandle != INVALID_HANDLE_VALUE) {
        do {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (wcscmp(findData.cFileName, L".") && wcscmp(findData.cFileName, L".."))
                    // Nested scan
                    amountOfTracks += WriteUserTracksFile(dir + findData.cFileName + L"\\", currentLength, file, offsets, depth + 1);
            } else {
                size_t       filenameLength = wcslen(findData.cFileName);
                std::wstring path = dir + L"\\" + findData.cFileName;

                // If the file is a shortcut, then resolve the target
                const wchar_t* extension = wcsrchr(findData.cFileName, L'.');
                if (path.rfind(L".lnk") == path.length() - 4)
                    path = ResolveShortcut(path);

                // "path" now points to target file (if it's a shortcut)
                // or the actual file (if it's regular file)
                DWORD fileAttr;
                if ((fileAttr = GetFileAttributesW(path.c_str())) != INVALID_FILE_ATTRIBUTES) {
                    // If path pointed by the shortcut is a directory
                    // then perform 15 deep scan on those folders too.
                    // MikuAuahDark: Note that GTASA code actually do this. My minor
                    // improvement is only to ensure it uses UTF-8 chars by operating
                    // on wide char.
                    if (fileAttr & FILE_ATTRIBUTE_DIRECTORY)
                        amountOfTracks += WriteUserTracksFile(path + L"\\", currentLength, file, offsets, 1);
                    else {
                        std::string    pathChar = UnicodeToUTF8(path);
                        eAudioFileType fileType = GetAudioFileType(pathChar.c_str());

                        if (fileType != AUDIO_FILE_TYPE_UNKNOWN) {
                            size_t pathLen = pathChar.length();
                            CFileMgr::Write(file, pathChar.c_str(), pathLen);
                            offsets.push_back({currentLength, pathLen, fileType});
                            currentLength += pathLen;
                            amountOfTracks++;
                        }
                    }
                }
            }
        } while (FindNextFileW(findHandle, &findData));
    }

    FindClose(findHandle);
    return amountOfTracks;
}

// todo: FIX_BUGS
// 0x4f30f0
char* CAEUserRadioTrackManager::ResolveShortcut(const char* path) {
    std::string str = UnicodeToUTF8(ResolveShortcut(UTF8ToUnicode(path)));
    char*       result = new char[str.length() + 1];

    memcpy(result, str.c_str(), str.length() + 1);
    return result;
}

std::wstring CAEUserRadioTrackManager::ResolveShortcut(const std::wstring& path) {
    IShellLinkW*  shellLink = nullptr;
    IPersistFile* persistFile = nullptr;

    if (FAILED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&shellLink))) {
        assert(true && "CoCreateInstance failed");
    }

    if (FAILED(shellLink->QueryInterface(IID_IPersistFile, (void**)&persistFile))) {
        shellLink->Release();
        return std::wstring();
    }

    wchar_t*         target = new wchar_t[MAX_PATH];
    WIN32_FIND_DATAW findData{};
    if (FAILED(persistFile->Load(path.c_str(), STGM_READ)) || FAILED(shellLink->GetPath(target, MAX_PATH, &findData, 0))) {
        persistFile->Release();
        shellLink->Release();
        assert(true && "Load or GetPath failed");
    }

    persistFile->Release();
    shellLink->Release();

    std::wstring out = target;
    delete[] target;
    return out;
}

void CAEUserRadioTrackManager::InjectHooks() {
    RH_ScopedClass(CAEUserRadioTrackManager);
    RH_ScopedCategory("Audio/Managers");

    RH_ScopedInstall(Initialise, 0x4f35b0);
    RH_ScopedInstall(Shutdown, 0x4f2fb0);
    RH_ScopedInstall(ReadUserTracks, 0x4f2fd0);
    RH_ScopedInstall(GetTrackPath, 0x4f3050);
    RH_ScopedOverloadedInstall(ResolveShortcut, "", 0x4f30f0, char* (CAEUserRadioTrackManager::*)(const char*));
    RH_ScopedInstall(GetAudioFileType, 0x4f31f0);
    RH_ScopedInstall(SelectUserTrackIndex, 0x4f3250);
    RH_ScopedInstall(DeleteUserTracksInfo, 0x4f32f0);
    RH_ScopedInstall(IsShortcut, 0x4f32c0);
    RH_ScopedInstall(LoadUserTrack, 0x4f35f0);
    RH_ScopedInstall(GetUserTrackPlayMode, 0x4f3330);
    RH_ScopedInstall(SetUserTrackIndex, 0x4f3340);
    RH_ScopedOverloadedInstall(WriteUserTracksFile, "", 0x4f4690, int32(CAEUserRadioTrackManager::*)(const char*, size_t&, FILE*, std::vector<tUserTracksInfo>&, int32));
    RH_ScopedInstall(WriteUserTracksThread, 0x4f4a20);
    RH_ScopedInstall(ScanUserTracks, 0x4f4ba0);
}
