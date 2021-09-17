#include "StdInc.h"

#include "CData.h"
#include "GxtChar.h"

CData::CData() {
    m_data = nullptr;
    m_size = 0;
}

CData::~CData() {
    Unload();
}

// 0x69F640
void CData::Unload() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
}

#define USE_ORIGINAL_CODE

// unknown always 0
// 0x69F5D0
bool CData::Load(uint32 length, FILESTREAM file, uint32* offset, uint8 unknown) {
    m_size = length / sizeof(GxtChar);
    m_data = new GxtChar[m_size];

#ifdef USE_ORIGINAL_CODE
    uint32 temp = 0;

    if (!length)
        return true;

    for (uint32 i = 0; i < m_size; ++i) {
        if (!unknown)
            if (sizeof(GxtChar) != CFileMgr::Read(file, &temp, sizeof(GxtChar)))
                return false;

        m_data[i] = (GxtChar)temp;
        ++*offset;
    }

    return true;
#else
    CFileMgr::Read(file, data, length);
    *offset += length;
#endif
}
