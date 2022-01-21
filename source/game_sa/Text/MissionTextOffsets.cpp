#include "StdInc.h"

#include "MissionTextOffsets.h"

CMissionTextOffsets::CMissionTextOffsets() {
    m_size = 0;
}

// 0x69F670
bool CMissionTextOffsets::Load(uint32 length, FILESTREAM file, uint32* offset, int32 unknown) {
    tMissionTextOffset* pTextOffset = m_offsets;
    m_size = 0;

    while (true) {
        if (sizeof(tMissionTextOffset) != CFileMgr::Read(file, pTextOffset, sizeof(tMissionTextOffset))) {
            return false;
        }
        *offset += sizeof(tMissionTextOffset);

        ++pTextOffset;
        ++m_size;

        if (uint32(pTextOffset - m_offsets) >= length / sizeof(tMissionTextOffset)) {
            break;
        }
    }

    return true;

#ifdef USE_ORIGINAL_CODE
    // todo: taken from *** and not tested
    size_t entryCount = length / sizeof(tTextOffset);
    for (size_t mi = 0; mi < entryCount; mi++) {
        for (uint32 i = 0; i < sizeof(m_offsets[mi].szMissionName); i++) {
            CFileMgr::Read(file, &m_offsets[i].szMissionName[i], 1);
            (*offset)++;
        }
        char* _buf = (char*)&m_offsets[mi].offset;
        for (uint32 i = 0; i < sizeof(m_offsets[mi].offset); i++) {
            CFileMgr::Read(file, &_buf[i], 1);
            (*offset)++;
        }
    }
    size = (unsigned short)entryCount;
#else
    m_size = (uint16) (length / sizeof(tMissionTextOffset));
    CFileMgr::Read(file, (char*)m_offsets, sizeof(tMissionTextOffset) * m_size);
    *offset += sizeof(tMissionTextOffset) * m_size;
#endif
}
