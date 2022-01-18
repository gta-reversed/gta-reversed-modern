#include "StdInc.h"

#include "Data.h"
#include "GxtChar.h"

CData::CData() {
    data = nullptr;
    size = 0;
}

CData::~CData() {
    Unload();
}

// 0x69F640
void CData::Unload() {
    delete[] data;
    data = nullptr;
    size = 0;
}

// nSkipBytes always 0
// 0x69F5D0
void CData::Load(uint32 length, FILESTREAM file, uint32* offset, uint8 nSkipBytes) {
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
    size = length / sizeof(char);
    data = new char[size];

    CFileMgr::Read(file, data, length);
    *offset += length;
#endif
}
