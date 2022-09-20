#include "StdInc.h"

#include "MissionTextOffsets.h"

CMissionTextOffsets::CMissionTextOffsets() {
    m_size = 0;
}

// 0x69F670
bool CMissionTextOffsets::Load(uint32 length, FILESTREAM file, uint32* offset, int32 unknown) {
#if 0
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
#endif
    m_size = (uint16)(length / sizeof(tMissionTextOffset));
    CFileMgr::Read(file, (char*)m_offsets, sizeof(tMissionTextOffset) * m_size);
    *offset += sizeof(tMissionTextOffset) * m_size;

    return true;
}
