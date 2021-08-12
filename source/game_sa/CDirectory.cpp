#include "StdInc.h"
#include "CDirectory.h"


void CDirectory::InjectHooks() {
    ReversibleHooks::Install("CDirectory", "CDirectory", 0x532290, static_cast<CDirectory*(CDirectory::*)()>(&CDirectory::Constructor));
    ReversibleHooks::Install("CDirectory", "CDirectory", 0x5322A0, static_cast<CDirectory*(CDirectory::*)(size_t)>(&CDirectory::Constructor));
    ReversibleHooks::Install("CDirectory", "~CDirectory", 0x5322D0, &CDirectory::Destructor); 
    // ReversibleHooks::Install("CDirectory", "Init", 0x5322F0, &CDirectory::Init); 
    // ReversibleHooks::Install("CDirectory", "AddItem", 0x532310, &CDirectory::AddItem); 
    // ReversibleHooks::Install("CDirectory", "ReadDirFile", 0x532350, &CDirectory::ReadDirFile); 
    // ReversibleHooks::Install("CDirectory", "WriteDirFile", 0x532410, &CDirectory::WriteDirFile); 
    // ReversibleHooks::Install("CDirectory", "FindItem", 0x532450, static_cast<DirectoryInfo*(CDirectory::*)(const char*)>(&CDirectory::FindItem)); 
    // ReversibleHooks::Install("CDirectory", "FindItem", 0x5324A0, static_cast<bool(CDirectory::*)(const char*, uint32_t&, uint32_t&)>(&CDirectory::FindItem)); 
    // ReversibleHooks::Install("CDirectory", "FindItem", 0x5324D0, static_cast<bool(CDirectory::*)(uint32_t, uint32_t&, uint32_t&)>(&CDirectory::FindItem)); 
}

// 0x532290
CDirectory::CDirectory() {
    /* done by the compiler */
}

// 0x532290
CDirectory* CDirectory::Constructor() {
    this->CDirectory::CDirectory();
    return this;
}

// 0x5322A0
CDirectory::CDirectory(size_t capacity) :
    m_nCapacity(capacity),
    m_pEntries(new DirectoryInfo[capacity]),
    m_bOwnsEntries(true)
{
    /* rest done by the compiler */
}

// 0x5322A0
CDirectory* CDirectory::Constructor(size_t capacity) {
    this->CDirectory::CDirectory(capacity);
    return this;
}

// 0x5322D0
CDirectory::~CDirectory() {
    if (m_pEntries && m_bOwnsEntries)
        delete[] m_pEntries;
}

// 0x5322D0
CDirectory* CDirectory::Destructor() {
    this->CDirectory::~CDirectory();
    return this;
}

// 0x5322F0
int32_t CDirectory::Init(int32_t capacity, DirectoryInfo* entries) {
    return plugin::CallMethodAndReturn<int32_t, 0x5322F0, CDirectory*, int32_t, DirectoryInfo*>(this, capacity, entries);
}

// 0x532310
void CDirectory::AddItem(DirectoryInfo* dirInfo) {
    plugin::CallMethod<0x532310, CDirectory*, DirectoryInfo*>(this, dirInfo);
}

// 0x532350
void CDirectory::ReadDirFile(const char* filename) {
    plugin::CallMethod<0x532350, CDirectory*, const char*>(this, filename);
}

// 0x532410
bool CDirectory::WriteDirFile(const char* fileName) {
    return plugin::CallMethodAndReturn<bool, 0x532410, CDirectory*, const char*>(this, fileName);
}

// 0x532450
CDirectory::DirectoryInfo* CDirectory::FindItem(const char* itemName) {
    return plugin::CallMethodAndReturn<DirectoryInfo*, 0x532450, CDirectory*, const char*>(this, itemName);
}

// 0x5324A0
bool CDirectory::FindItem(const char* name, uint32_t& outOffset, uint32_t& outStreamingSize) {
    return plugin::CallMethodAndReturn<bool, 0x5324A0, CDirectory*, const char*, uint32_t&, uint32_t&>(this, name, outOffset, outStreamingSize);
}

// 0x5324D0
bool CDirectory::FindItem(uint32_t hashKey, uint32_t& outOffset, uint32_t& outStreamingSize) {
    return plugin::CallMethodAndReturn<bool, 0x5324D0, CDirectory*, uint32_t, uint32_t&, uint32_t&>(this, hashKey, outOffset, outStreamingSize);
}
