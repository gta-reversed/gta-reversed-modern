/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"

/*
    http://www.gtamodding.com/wiki/IMG_archive
*/

class CDirectory {
public:
    struct DirectoryInfo {
        unsigned int m_nOffset;
        unsigned short m_nStreamingSize;
        unsigned short m_nSizeInArchive;
        char m_szName[24];
    };

public:
    DirectoryInfo* m_pEntries{};
    unsigned int   m_nCapacity{};
    unsigned int   m_nNumEntries{};
    bool           m_bOwnsEntries{};

public:
    CDirectory();
    CDirectory(size_t capacity);
    ~CDirectory();
private:
    CDirectory* Destructor();
    CDirectory* Constructor();
    CDirectory* Constructor(size_t capacity);
public:
    static void InjectHooks();

    void Init(int32_t capacity, DirectoryInfo* entries);
    void AddItem(const DirectoryInfo& dirInfo);
    void ReadDirFile(const char* filename);
    bool WriteDirFile(const char* fileName);
    DirectoryInfo* FindItem(const char* itemName);
    bool CDirectory::FindItem(const char* name, uint32_t& outOffset, uint32_t& outStreamingSize);
    bool CDirectory::FindItem(uint32_t hashKey, uint32_t& outOffset, uint32_t& outStreamingSize);
};

VALIDATE_SIZE(CDirectory, 0x10);
VALIDATE_SIZE(CDirectory::DirectoryInfo, 0x20);
