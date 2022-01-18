#include "StdInc.h"

#include "KeyArray.h"
#include "GxtChar.h"

CKeyArray::CKeyArray() {
    m_data = nullptr;
    m_size = 0;
}

CKeyArray::~CKeyArray() {
    Unload();
}

// 0x69F510
void CKeyArray::Unload() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
}

// unknown always 0
// 0x69F490
bool CKeyArray::Load(uint32 length, FILESTREAM file, uint32* offset, uint8 unknown) {
#ifdef USE_ORIGINAL_CODE
    uint32 temp = 0;

    m_size = length / sizeof(CKeyEntry);
    m_data = new CKeyEntry[m_size];

    if (length) {
        if (length != CFileMgr::Read(file, m_data, length)) {
            return false;
        }

        *offset += length;
    }
#else
    // taken from re3
    m_size = length / sizeof(CKeyEntry);
    m_data = new CKeyEntry[m_size];

    CFileMgr::Read(file, m_data, length);
    *offset += length;
#endif
    return true;
}

// 0x69F540
void CKeyArray::Update(char* offset) {
    for (uint32 i = 0; i < m_size; ++i) {
        m_data[i].string = (GxtChar*)((uint8*)offset + (uint32)(m_data[i].string));
    }
}

// 0x6A0000
char* CKeyArray::Search(const char* key, bool* found) {
    uint32 hash = CKeyGen::GetUppercaseKey(key);
    CKeyEntry* entry = BinarySearch(hash, m_data, 0, m_size - 1);
    if (entry) {
        *found = true;
        return entry->string;
    } else {
        *found = false;
        return nullptr;
    }
}

// 0x69F570
CKeyEntry* CKeyArray::BinarySearch(uint32 hash, CKeyEntry* entries, int16 firstIndex, int16 lastIndex) {
    if (firstIndex > lastIndex)
        return nullptr;

    while (true) {
        uint16 middle = (firstIndex + lastIndex) >> 1;
        auto entryHash = entries[middle].hash;

        if (hash == entryHash)
            return &entries[middle];

        if (hash > entryHash)
            firstIndex = middle + 1;
        else
            lastIndex = middle - 1;

        if (firstIndex > lastIndex)
            return nullptr;
    }
}