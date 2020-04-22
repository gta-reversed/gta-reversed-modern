/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

// Converted from thiscall void CDirectory::CDirectory(void) 0x532290
CDirectory::CDirectory() {
    plugin::CallMethod<0x532290, CDirectory*>(this);
}

// Converted from thiscall void CDirectory::CDirectory(int capacity) 0x5322A0
CDirectory::CDirectory(int capacity) {
    plugin::CallMethod<0x5322A0, CDirectory*, int>(this, capacity);
}

// Converted from thiscall void CDirectory::~CDirectory() 0x5322D0
CDirectory::~CDirectory() {
    plugin::CallMethod<0x5322D0, CDirectory*>(this);
}

// Converted from thiscall void CDirectory::Init(int capacity,void *entries) 0x5322F0
void CDirectory::Init(int capacity, void* entries) {
    plugin::CallMethod<0x5322F0, CDirectory*, int, void*>(this, capacity, entries);
}

// Converted from thiscall void CDirectory::AddItem(DirectoryInfo const&entry) 0x532310
void CDirectory::AddItem(DirectoryInfo const& entry) {
    plugin::CallMethod<0x532310, CDirectory*, DirectoryInfo const&>(this, entry);
}

// Converted from thiscall void CDirectory::ReadDirFile(char const*filename) 0x532350
void CDirectory::ReadDirFile(char const* filename) {
    plugin::CallMethod<0x532350, CDirectory*, char const*>(this, filename);
}

// Converted from thiscall bool CDirectory::WriteDirFile(char const*filename) 0x532410
bool CDirectory::WriteDirFile(char const* filename) {
    return plugin::CallMethodAndReturn<bool, 0x532410, CDirectory*, char const*>(this, filename);
}

// Converted from thiscall DirectoryInfo* CDirectory::FindItem(char const*name) 0x532450
CDirectory::DirectoryInfo* CDirectory::FindItem(char const* name) {
    return plugin::CallMethodAndReturn<DirectoryInfo*, 0x532450, CDirectory*, char const*>(this, name);
}

// Converted from thiscall DirectoryInfo* CDirectory::FindItem(char const*name,uint &outOffset,uint &outStreamingSize) 0x5324A0
CDirectory::DirectoryInfo* CDirectory::FindItem(char const* name, unsigned int& outOffset, unsigned int& outStreamingSize) {
    return plugin::CallMethodAndReturn<DirectoryInfo*, 0x5324A0, CDirectory*, char const*, unsigned int&, unsigned int&>(this, name, outOffset, outStreamingSize);
}

// Converted from thiscall DirectoryInfo* CDirectory::FindItem(uint key,uint &outOffset,uint &outStreamingSize) 0x5324D0
CDirectory::DirectoryInfo* CDirectory::FindItem(unsigned int key, unsigned int& outOffset, unsigned int& outStreamingSize) {
    return plugin::CallMethodAndReturn<DirectoryInfo*, 0x5324D0, CDirectory*, unsigned int, unsigned int&, unsigned int&>(this, key, outOffset, outStreamingSize);
}