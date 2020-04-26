#include "StdInc.h" // TODO remove

#include <cerrno>
#include <cstring>
#include <direct.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ShlObj.h>

#include "CFileMgr.h"
//#include "RenderWare.h"

#include "HookSystem.h"

char *CFileMgr::ms_dirName = (char *) 0xb71a60;
char *CFileMgr::ms_rootDirName = (char *) 0xb71ae0;

/*
static char
    user_tracks_dir_path[256],
    user_gallery_dir_path[256],
    gta_user_dir_path[256];
*/
char
    *user_tracks_dir_path = (char *) 0xc92168,
    *user_gallery_dir_path = (char *) 0xc92268,
    *gta_user_dir_path = (char *) 0xc92368;

inline void createDirectory(const char *path)
{
    HANDLE folderHandle = CreateFileA(
        path,
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
    if (folderHandle == INVALID_HANDLE_VALUE)
        CreateDirectoryA(path, nullptr);
    else
        CloseHandle(folderHandle);
}

static char *InitUserDirectories()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((char*(*)()) 0x744FB0)();
#else
    if (*gta_user_dir_path == 0)
    {
        if (SHGetFolderPathA(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, gta_user_dir_path) == S_OK)
        {
            constexpr const char *USERFILES = "\\GTA San Andreas User Files";
            constexpr const char *GALLERY = ".\\Gallery";
            constexpr const char *USERTRACKS = ".\\User Tracks";

            memset(user_gallery_dir_path, 0, 256);
            memset(user_tracks_dir_path, 0, 256);

            if ((strlen(gta_user_dir_path) + strlen(USERFILES)) >= 256)
                memcpy(gta_user_dir_path, ".", 2);
            else
                strcat(gta_user_dir_path, USERFILES);

            createDirectory(gta_user_dir_path);
            strcpy(user_gallery_dir_path, gta_user_dir_path);
            strcpy(user_tracks_dir_path, gta_user_dir_path);

            if ((strlen(gta_user_dir_path) + strlen(GALLERY + 1)) >= 256)
                memcpy(user_gallery_dir_path, GALLERY, strlen(GALLERY) + 1);
            else
                strcpy(user_gallery_dir_path, GALLERY + 1);
            createDirectory(user_gallery_dir_path);

            if ((strlen(gta_user_dir_path) + strlen(USERTRACKS + 1)) >= 256)
                memcpy(user_tracks_dir_path, USERTRACKS, strlen(USERTRACKS) + 1);
            else
                strcpy(user_tracks_dir_path, USERTRACKS + 1);
            createDirectory(user_tracks_dir_path);
        }
        else
            memcpy(gta_user_dir_path, "data", 5); // strlen("data") + 1
    }

    return gta_user_dir_path;
#endif
}

void CFileMgr::Initialise()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(*)()) 0x5386f0)();
#else
    memset(ms_rootDirName, 0, DIRNAMELENGTH);
    _getcwd(ms_rootDirName, DIRNAMELENGTH);
    ms_rootDirName[strlen(ms_rootDirName)] = '\\';
#endif
}

int CFileMgr::ChangeDir(const char *path)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(*)(const char*)) 0x538730)(path);
#else
    memset(ms_dirName, 0, DIRNAMELENGTH);

    if (*path == '\\')
    {
        memcpy(ms_dirName, ms_rootDirName, strlen(ms_rootDirName));
        path++;
    }

    if (*path)
    {
        if ((strlen(ms_dirName) + strlen(path) + 1) > DIRNAMELENGTH)
        {
            errno = EINVAL;
            return -1;
        }
        strcat(ms_dirName, path);

        char *lastPos = strchr(ms_dirName, 0) - 1;
        if (*lastPos != '\\')
            lastPos[1] = '\\';
    }

    return _chdir(ms_dirName);
#endif
}

int CFileMgr::SetDir(const char *path)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(*)(const char*)) 0x5387D0)(path);
#else
    memset(ms_dirName, 0, DIRNAMELENGTH);
    memcpy(ms_dirName, ms_rootDirName, strlen(ms_rootDirName));

    if (*path)
    {
        if ((strlen(ms_dirName) + strlen(path) + 1) > DIRNAMELENGTH)
        {
            errno = EINVAL;
            return -1;
        }
        strcat(ms_dirName, path);

        char *lastPos = strchr(ms_dirName, 0) - 1;
        if (*lastPos != '\\')
            lastPos[1] = '\\';
    }

    return _chdir(ms_dirName);
#endif
}

int CFileMgr::SetDirMyDocuments()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(*)()) 0x538860)();
#else
    char *userDir = InitUserDirectories();
    if (strlen(userDir) >= DIRNAMELENGTH)
    {
        errno = ENOMEM;
        return -1;
    }

    strcpy(ms_dirName, userDir);
    return _chdir(ms_dirName);
#endif
}

size_t CFileMgr::LoadFile(const char *path, unsigned char *buf, size_t size, const char *mode)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(*)(const char*, unsigned char*, int, const char*)) 0x538890)(path, buf, size, mode);
#else
    FILE *f = fopen(path, mode);
    if (f == nullptr)
        return -1;
    
    // MikuAuahDark: The original implementation actually ignore
    // "size" parameter and adds NUL terminator at the end of the
    // buffer, but that behavior causes buffer overflow
    size_t readed = fread(buf, 1, size, f);
    fclose(f);

    return readed;
#endif
}

FILE* CFileMgr::OpenFile(const char *path, const char *mode)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((FILE*(*)(const char*, const char*)) 0x538900)(path, mode);
#else
    return fopen(path, mode);
#endif
}

FILE* CFileMgr::OpenFileForWriting(const char *path)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((FILE*(*)(const char*)) 0x538910)(path);
#else
    return fopen(path, "wb");
#endif
}

FILE* CFileMgr::OpenFileForAppending(const char *path)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((FILE*(*)(const char*)) 0x538930)(path);
#else
    return fopen(path, "a");
#endif
}

size_t CFileMgr::Read(FILE *file, void *buf, size_t size)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((size_t(*)(FILE*, void*, size_t)) 0x538950)(file, buf, size);
#else
    return fread(buf, 1, size, file);
#endif
}

size_t CFileMgr::Write(FILE *file, const void *buf, size_t size)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((size_t(*)(FILE*, const void*, size_t)) 0x538970)(file, buf, size);
#else
    return fwrite(buf, 1, size, file);
#endif
}

bool CFileMgr::Seek(FILE *file, long offset, int origin)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(*)(FILE*, long, int)) 0x538990)(file, offset, origin);
#else
    // MikuAuahDark: Pretty sure it shouldn't be ret != 0
    return fseek(file, offset, origin) != 0;
#endif
}

bool CFileMgr::ReadLine(FILE *file, char *str, int num)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(*)(FILE*, char*, size_t)) 0x5389b0)(file, str, num);
#else
    return fgets(str, num, file) != nullptr;
#endif
}

int CFileMgr::CloseFile(FILE *file)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(*)(FILE*)) 0x5389d0)(file);
#else
    return fclose(file);
#endif
}

int CFileMgr::GetFileLength(FILE *file)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(*)(FILE*)) 0x5389e0)(file);
#else
    int currentPos, size;
    // MikuAuahDark: The actual implementation uses RwOsGetFileInterface
    // but for sake of portability, default stdio functions is used.
    /*
    RwFileFunctions *functions = RwOsGetFileInterface();

    currentPos = functions->rwftell(file);
    functions->rwfseek(file, 0, SEEK_END);
    size = functions->rwftell(file);
    functions->rwfseek(file, currentPos, SEEK_SET);
    
    return size;
    */
    currentPos = ftell(file);
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, currentPos, SEEK_SET);

    return size;
#endif
}

int CFileMgr::Tell(FILE *file)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(*)(FILE*)) 0x538a20)(file);
#else
    /*
    RwFileFunctions *functions = RwOsGetFileInterface();
    return functions->rwftell(file);
    */

    return ftell(file);
#endif
}

bool CFileMgr::GetErrorReadWrite(FILE *file)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(*)(FILE*)) 0x538a50)(file);
#else
    return (bool) ferror(file);
#endif
}

void CFileMgr::InjectHooks()
{
#ifndef USE_DEFAULT_FUNCTIONS
    HookInstall(0x5386f0, &CFileMgr::Initialise, 7);
    HookInstall(0x538730, &CFileMgr::ChangeDir, 7);
    HookInstall(0x5387D0, &CFileMgr::SetDir, 7);
    HookInstall(0x538860, &CFileMgr::SetDirMyDocuments, 7);
    HookInstall(0x538890, &CFileMgr::LoadFile, 7);
    HookInstall(0x538900, &CFileMgr::OpenFile, 7);
    HookInstall(0x538910, &CFileMgr::OpenFileForWriting, 7);
    HookInstall(0x538930, &CFileMgr::OpenFileForAppending, 7);
    HookInstall(0x538950, &CFileMgr::Read, 7);
    HookInstall(0x538970, &CFileMgr::Write, 7);
    HookInstall(0x538990, &CFileMgr::Seek, 7);
    HookInstall(0x5389b0, &CFileMgr::ReadLine, 7);
    HookInstall(0x5389d0, &CFileMgr::CloseFile, 7);
    HookInstall(0x5389e0, &CFileMgr::GetFileLength, 7);
    HookInstall(0x538a20, &CFileMgr::Tell, 7);
    HookInstall(0x538a50, &CFileMgr::GetErrorReadWrite, 7);
    HookInstall(0x744fb0, &InitUserDirectories, 7);
#endif
}
