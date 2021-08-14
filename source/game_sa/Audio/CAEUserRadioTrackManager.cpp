#include "StdInc.h" // TODO: Remove

#include <cstdio>

// COM
#include <ShObjIdl.h>

#include "common.h"

#include "CAEUserRadioTrackManager.h"

#include "CAEAudioUtility.h"
#include "CAEDataStream.h"
#include "CAEMFDecoder.h"
#include "CAEWaveDecoder.h"
#include "CAEWMADecoder.h"
#include "CAEVorbisDecoder.h"

#include "CFileMgr.h"
#include "CMenuManager.h"

// Instance of CAEUserRadioTrackManager
CAEUserRadioTrackManager &CAEUserRadioTrackManager::instance = *(CAEUserRadioTrackManager *) 0xb6b970;

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
tAudioExtensionType (&CAEUserRadioTrackManager::audioExtensionTypes)[7] = *reinterpret_cast<tAudioExtensionType(*)[7]>(0x8cbb28);

bool CAEUserRadioTrackManager::Initialise()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall *)(CAEUserRadioTrackManager*)) 0x4f35b0)(this);
#else
    userTracksLoaded = ReadUserTracks();
    _userTracksLoadedCopy = userTracksLoaded;
    memset(decodersSupported, 0, sizeof (decodersSupported));
    decodersSupported[AUDIO_FILE_TYPE_VORBIS] = true;
    decodersSupported[AUDIO_FILE_TYPE_WAV] = true;
    decodersSupported[AUDIO_FILE_TYPE_WMA] = CAEWMADecoder::InitLibrary();
    decodersSupported[AUDIO_FILE_TYPE_QUICKTIME] = CAEMFDecoder::InitLibrary();

    if (decodersSupported[AUDIO_FILE_TYPE_QUICKTIME] == false)
        // change MP3 decoder from QuickTime to WMA
        audioExtensionTypes[1].type = AUDIO_FILE_TYPE_WMA;

    return true;
#endif
}

void CAEUserRadioTrackManager::Shutdown()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CAEUserRadioTrackManager*)) 0x4f2fb0)(this);
#else
    if (userTracksLoaded && userTracksInfo)
    {
        CMemoryMgr::Free(userTracksInfo);
        userTracksInfo = nullptr;
    }

    CAEWMADecoder::Shutdown();
    CAEMFDecoder::Shutdown();
#endif
}

char *CAEUserRadioTrackManager::GetTrackPath(std::int32_t trackID)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((char*(__thiscall *)(CAEUserRadioTrackManager*, int)) 0x4f3050)(this, trackID);
#else
    if (trackID >= static_cast<std::int32_t> (userTracksCount))
        return nullptr;

    CFileMgr::SetDirMyDocuments();
    FILESTREAM ufiles = CFileMgr::OpenFile("sa-ufiles.dat", "rb");
    CFileMgr::SetDir("");

    if (ufiles == 0)
        return nullptr;

    tUserTracksInfo &targetOffset = userTracksInfo[trackID];
    char *dest = new char[targetOffset.pathLength + 1];

    CFileMgr::Seek(ufiles, targetOffset.startUfilesPath, SEEK_SET);
    CFileMgr::Read(ufiles, dest, targetOffset.pathLength);
    CFileMgr::CloseFile(ufiles);

    // NULL-terminate the path
    dest[targetOffset.pathLength] = 0;
    return dest;
#endif
}

CAEStreamingDecoder* CAEUserRadioTrackManager::LoadUserTrack(std::int32_t trackID)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CAEStreamingDecoder*(__thiscall *)(CAEUserRadioTrackManager*, int)) 0x4f35f0)(this, trackID);
#else
    if (userTracksLoaded == false)
        return nullptr;

    if (trackID < 0 || trackID >= userTracksCount)
        return nullptr;
    
    tUserTracksInfo &targetOffset = userTracksInfo[trackID];
    if (decodersSupported[targetOffset.fileType] == false)
        return nullptr;

    char *filename = GetTrackPath(trackID);
    if (filename == nullptr)
        return nullptr;
    
    CAEStreamingDecoder *decoder = nullptr;

    // QuickTime decoder doesn't need the data stream
    if (targetOffset.fileType == AUDIO_FILE_TYPE_QUICKTIME)
        // MikuAuahDark: We've agreed to replace QuickTime with MediaFoundation
        decoder = new CAEMFDecoder(filename, trackID);
    else
    {
        CAEDataStream *dataStream = new CAEDataStream(trackID, filename, 0, 0, 0);

        CFileMgr::SetDirMyDocuments();
        bool dataStreamInitialized = dataStream->Initialise();
        CFileMgr::SetDir("");

        if (dataStreamInitialized == false)
        {
            delete dataStream;
            return nullptr;
        }

        switch (targetOffset.fileType)
        {
            case AUDIO_FILE_TYPE_UNKNOWN:
            default:
            {
                delete dataStream;
                return nullptr;
            }
            case AUDIO_FILE_TYPE_VORBIS:
            {
                decoder = new CAEVorbisDecoder(dataStream, true);
                break;
            }
            case AUDIO_FILE_TYPE_WAV:
            {
                decoder = new CAEWaveDecoder(dataStream);
                break;
            }
            case AUDIO_FILE_TYPE_WMA:
            {
                decoder = new CAEWMADecoder(dataStream);
                break;
            }
        }
    }

    return decoder;
#endif
}

bool CAEUserRadioTrackManager::ReadUserTracks()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall *)(CAEUserRadioTrackManager*)) 0x4f2fd0)(this);
#else
    CFileMgr::SetDirMyDocuments();
    FILE *f = CFileMgr::OpenFile("sa-utrax.dat", "rb");
    CFileMgr::SetDir("");

    if (f == nullptr)
        return false;

    size_t size = static_cast<size_t> (CFileMgr::GetFileLength(f));
    if (size == 0)
    {
        CFileMgr::CloseFile(f);
        return false;
    }

    userTracksCount = (uint16_t)(size / sizeof(tUserTracksInfo));

    if (userTracksInfo)
        CMemoryMgr::Free(userTracksInfo);
    userTracksInfo = (tUserTracksInfo *) CMemoryMgr::Malloc(size);

    CFileMgr::Read(f, userTracksInfo, size);
    CFileMgr::CloseFile(f);

    return true;
#endif
}

bool CAEUserRadioTrackManager::ScanUserTracks()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall *)(CAEUserRadioTrackManager*)) 0x4f4ba0)(this);
#else
    switch (userTracksScanState)
    {
        case USER_TRACK_SCAN_OFF:
        {
            userTracksScanState = USER_TRACK_SCAN_IN_PROGRESS;
            userTracksScanThreadHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) WriteUserTracksThread, this, 0, &userTracksScanThreadID);
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
#endif
}

void CAEUserRadioTrackManager::DeleteUserTracksInfo()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CAEUserRadioTrackManager*)) 0x4f32f0)(this);
#else
    TerminateThread(userTracksScanThreadHandle, 0);
    CFileMgr::SetDirMyDocuments();
    remove("sa-ufiles.dat");
    remove("sa-utrax.dat");
    CFileMgr::SetDir("");

    userTracksScanState = USER_TRACK_SCAN_OFF;
#endif
}

void CAEUserRadioTrackManager::SetUserTrackIndex(std::int32_t index)
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CAEUserRadioTrackManager*, int)) 0x4f3340)(this, index);
#else
    if (index != -1)
        FrontEndMenuManager.field_AC = index;
#endif
}

std::int32_t CAEUserRadioTrackManager::SelectUserTrackIndex()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((std::uint32_t(__thiscall *)(CAEUserRadioTrackManager*)) 0x4f3250)(this);
#else
    if (userTracksCount > 0 && FrontEndMenuManager.m_nRadioMode >= 0)
    {
        switch (FrontEndMenuManager.m_nRadioMode)
        {
            case USER_TRACK_PLAY_RADIO:
            case USER_TRACK_PLAY_RANDOM:
            {
                if (userTracksCount == 1)
                    return FrontEndMenuManager.field_AC = 1;
                else
                {
                    int index;

                    do
                        index = static_cast<int> (CAEAudioUtility::GetRandomNumberInRange(0, userTracksCount - 1));
                    while (index == FrontEndMenuManager.field_AC);

                    return FrontEndMenuManager.field_AC = index;
                }
            }
            case USER_TRACK_PLAY_SEQUENTAL:
            {
                return FrontEndMenuManager.field_AC = (FrontEndMenuManager.field_AC + 1) % userTracksCount;
            }
        }
    }

    return -1;
#endif
}

eAudioFileType CAEUserRadioTrackManager::GetAudioFileType(const char *filename)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((eAudioFileType(__thiscall *)(CAEUserRadioTrackManager*, const char*)) 0x4f31f0)(this, filename);
#else
    constexpr size_t AUDIO_EXTENSIONS = sizeof(CAEUserRadioTrackManager::audioExtensionTypes) / sizeof(tAudioExtensionType);
    const char *dotPosition = strrchr(filename, '.');

    if (dotPosition == nullptr)
        return AUDIO_FILE_TYPE_UNKNOWN;

    for (const tAudioExtensionType &audioExtType: audioExtensionTypes)
    {
        if (_stricmp(audioExtType.extension, dotPosition) == 0)
            return audioExtType.type;
    }

    return AUDIO_FILE_TYPE_UNKNOWN;
#endif
}

bool CAEUserRadioTrackManager::IsShortcut(const char *path)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall *)(CAEUserRadioTrackManager*, const char*)) 0x4f32c0)(this, path);
#else
    const char *dot = strrchr(path, '.');
    return dot ? _stricmp(dot, ".lnk") == 0 : false;
#endif
}

std::uint8_t CAEUserRadioTrackManager::GetUserTrackPlayMode()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((eUserTrackPlayMode(__thiscall *)(CAEUserRadioTrackManager*)) 0x4f3330)(this);
#else
    return (std::uint8_t) FrontEndMenuManager.m_nRadioMode;
#endif
}

DWORD __stdcall CAEUserRadioTrackManager::WriteUserTracksThread(CAEUserRadioTrackManager *self)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((DWORD(__stdcall *)(CAEUserRadioTrackManager*)) 0x4f4a20)(self);
#else
    CoInitialize(nullptr);
    
    // Open sa-ufiles.dat
    CFileMgr::SetDirMyDocuments();
    FILE *file = CFileMgr::OpenFile("sa-ufiles.dat", "wb");

    if (file == nullptr)
        self->userTracksScanState = USER_TRACK_SCAN_ERROR;
    else
    {
        // Create path to "User Tracks"
        size_t documentsDirLen = strlen(CFileMgr::ms_dirName), dummy = 0;
        char *userTracksDir = new char[documentsDirLen + 15];
        std::vector<tUserTracksInfo> offsets;

        // Concat
        strcpy(userTracksDir, CFileMgr::ms_dirName);
        strcat(userTracksDir, "\\User Tracks\\");

        // Retrieve all user tracks info
        int amountOfTracks = self->WriteUserTracksFile(userTracksDir, dummy, file, offsets, 0);
        CFileMgr::CloseFile(file);

        // Open sa-utrax.dat containing the offsets
        file = CFileMgr::OpenFile("sa-utrax.dat", "wb");

        // MikuAuahDark: GTASA doesn't check if sa-utrax.dat fails to open
        if (file == nullptr)
            self->userTracksScanState = USER_TRACK_SCAN_ERROR;
        else
        {
            if (amountOfTracks > 0)
                CFileMgr::Write(file, offsets.data(), amountOfTracks * sizeof(tUserTracksInfo));

            CFileMgr::CloseFile(file);

            self->userTracksScanState = USER_TRACK_SCAN_COMPLETE;
            FrontEndMenuManager.field_AC = 0;
        }
    }

    // Read user tracks back
    self->userTracksLoaded = self->ReadUserTracks();
    self->_userTracksLoadedCopy = self->userTracksLoaded;

    CFileMgr::SetDir("");
    CoUninitialize();
    return 0;
#endif
}

int CAEUserRadioTrackManager::WriteUserTracksFile(
    const char *dir,
    size_t &currentLength,
    FILE *file,
    std::vector<tUserTracksInfo> &offsets,
    int depth
)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using WriteUtraxFunc = int(__thiscall *)(CAEUserRadioTrackManager*, const char*, size_t&, FILE*, std::vector<tUserTracksInfo>&, int);
    return ((WriteUtraxFunc) 0x4f4690)(this, dir, currentLength, file, offsets, depth);
#else
    return WriteUserTracksFile(UTF8ToUnicode(dir), currentLength, file, offsets, depth);;
#endif
}

int CAEUserRadioTrackManager::WriteUserTracksFile(
    const std::wstring &dir,
    size_t &currentLength,
    FILE *file,
    std::vector<tUserTracksInfo> &offsets,
    int depth
)
{
    // Limit folder scan to 16 folders deep
    if (depth >= 15)
        return 0;

    int amountOfTracks = 0;

    // Copy search directory
    std::wstring dirSearch = dir + L"\\*.*";

    WIN32_FIND_DATAW findData;
    HANDLE findHandle = FindFirstFileW(dirSearch.c_str(), &findData);

    if (findHandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (wcscmp(findData.cFileName, L".") && wcscmp(findData.cFileName, L".."))
                    // Nested scan
                    amountOfTracks += WriteUserTracksFile(dir + findData.cFileName + L"\\", currentLength, file, offsets, depth + 1);
            }
            else
            {
                size_t filenameLength = wcslen(findData.cFileName);
                std::wstring path = dir + L"\\" + findData.cFileName;
                
                // If the file is a shortcut, then resolve the target
                const wchar_t *extension = wcsrchr(findData.cFileName, L'.');
                if (path.rfind(L".lnk") == path.length() - 4)
                    path = ResolveShortcut(path);

                // "path" now points to target file (if it's a shortcut)
                // or the actual file (if it's regular file)
                DWORD fileAttr;
                if ((fileAttr = GetFileAttributesW(path.c_str())) != INVALID_FILE_ATTRIBUTES)
                {
                    // If path pointed by the shortcut is a directory
                    // then perform 15 deep scan on those folders too.
                    // MikuAuahDark: Note that GTASA code actually do this. My minor
                    // improvement is only to ensure it uses UTF-8 chars by operating
                    // on wide char.
                    if (fileAttr & FILE_ATTRIBUTE_DIRECTORY)
                        amountOfTracks += WriteUserTracksFile(path + L"\\", currentLength, file, offsets, 1);
                    else
                    {
                        std::string pathChar = UnicodeToUTF8(path);
                        eAudioFileType fileType = GetAudioFileType(pathChar.c_str());

                        if (fileType != AUDIO_FILE_TYPE_UNKNOWN)
                        {
                            size_t pathLen = pathChar.length();
                            CFileMgr::Write(file, pathChar.c_str(), pathLen);
                            offsets.push_back({currentLength, pathLen, fileType});
                            currentLength += pathLen;
                            amountOfTracks++;
                        }
                    }
                }
            }
        }
        while (FindNextFileW(findHandle, &findData));
    }

    FindClose(findHandle);
    return amountOfTracks;
}

char *CAEUserRadioTrackManager::ResolveShortcut(const char *path)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using ShortcutFunc = char*(__thiscall *)(CAEUserRadioTrackManager*, const char*);
    return ((ShortcutFunc) 0x4f30f0)(this, path);
#else
    std::string str = UnicodeToUTF8(ResolveShortcut(UTF8ToUnicode(path)));
    char *result = new char[str.length() + 1];

    memcpy(result, str.c_str(), str.length() + 1);
    return result;
#endif
}

std::wstring CAEUserRadioTrackManager::ResolveShortcut(const std::wstring &path)
{
    IShellLinkW *shellLink = nullptr;
    IPersistFile *persistFile = nullptr;

    if (FAILED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&shellLink)))
        throw std::runtime_error{"CoCreateInstance failed"};

    if (FAILED(shellLink->QueryInterface(IID_IPersistFile, (void **) &persistFile)))
    {
        shellLink->Release();
        throw std::runtime_error{ "QueryInterface failed" };
    }
    
    wchar_t *target = new wchar_t[MAX_PATH];
    WIN32_FIND_DATAW findData{};
    if (
        FAILED(persistFile->Load(path.c_str(), STGM_READ)) ||
        FAILED(shellLink->GetPath(target, MAX_PATH, &findData, 0))
    )
    {
        persistFile->Release();
        shellLink->Release();
        throw std::runtime_error{ "Load or GetPath failed" };
    }

    persistFile->Release();
    shellLink->Release();

    std::wstring out = target;
    delete[] target;
    return out;
}

void CAEUserRadioTrackManager::InjectHooks()
{
#ifndef USE_DEFAULT_FUNCTIONS
    HookInstall(0x4f2fb0, &CAEUserRadioTrackManager::Shutdown);
    HookInstall(0x4f2fd0, &CAEUserRadioTrackManager::ReadUserTracks);
    HookInstall(0x4f3050, &CAEUserRadioTrackManager::GetTrackPath);
    HookInstall(0x4f30f0, (char*(CAEUserRadioTrackManager::*)(const char*)) &CAEUserRadioTrackManager::ResolveShortcut);
    HookInstall(0x4f31f0, &CAEUserRadioTrackManager::GetAudioFileType);
    HookInstall(0x4f3250, &CAEUserRadioTrackManager::SelectUserTrackIndex);
    HookInstall(0x4f32f0, &CAEUserRadioTrackManager::DeleteUserTracksInfo);
    HookInstall(0x4f32c0, &CAEUserRadioTrackManager::IsShortcut);
    HookInstall(0x4f35b0, &CAEUserRadioTrackManager::Initialise);
    HookInstall(0x4f35f0, &CAEUserRadioTrackManager::LoadUserTrack);
    HookInstall(0x4f3330, &CAEUserRadioTrackManager::GetUserTrackPlayMode);
    HookInstall(0x4f3340, &CAEUserRadioTrackManager::SetUserTrackIndex);
    HookInstall(0x4f4690, (int(CAEUserRadioTrackManager::*)(const char*, size_t&, FILE*, std::vector<tUserTracksInfo>&, int)) &CAEUserRadioTrackManager::WriteUserTracksFile);
    HookInstall(0x4f4a20, &CAEUserRadioTrackManager::WriteUserTracksThread);
    HookInstall(0x4f4ba0, &CAEUserRadioTrackManager::ScanUserTracks);
#endif
}
