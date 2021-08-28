#include "StdInc.h"

#include "CData.h"

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
void CData::Load(uint32 length, FILESTREAM file, uint32* offset, uint8_t nSkipBytes) {
    return plugin::CallMethod<0x69F5D0, CData*, uint32, FILESTREAM, uint32*, uint8_t>(this, length, file, offset, nSkipBytes);

#ifdef USE_ORIGINAL_CODE
    // todo: add original code
#else
    size = length / sizeof(char);
    data = new char[size];

    CFileMgr::Read(file, data, length);
    *offset += length;
#endif
}
