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
    DirectoryInfo *m_pEntries;
    unsigned int m_nCapacity;
    unsigned int m_nNumEntries;
    bool m_bOwnsEntries;
private:
    char _padD[3];
public:

    void* operator new(unsigned int size)
    {
        return ((void* (__cdecl*)(unsigned int))0x82119A)(size);
    }

    void operator delete(void* object)
    {
        ((void(__cdecl*)(void*))0x8214BD)(object);
    }

    CDirectory();
    CDirectory(int capacity);
    ~CDirectory();
    void Init(int capacity, void* entries);
    void AddItem(DirectoryInfo const& entry);
    void ReadDirFile(char const* filename);
    bool WriteDirFile(char const* filename);
    DirectoryInfo* FindItem(char const* name);
    DirectoryInfo* FindItem(char const* name, unsigned int& outOffset, unsigned int& outStreamingSize);
    DirectoryInfo* FindItem(unsigned int key, unsigned int& outOffset, unsigned int& outStreamingSize);
};

VALIDATE_SIZE(CDirectory, 0x10);
VALIDATE_SIZE(CDirectory::DirectoryInfo, 0x20);
