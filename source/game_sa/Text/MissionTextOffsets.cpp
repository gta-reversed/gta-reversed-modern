#include "StdInc.h"

#include "MissionTextOffsets.h"

CMissionTextOffsets::CMissionTextOffsets() {
    m_size = 0;
}

// 0x69F670
bool CMissionTextOffsets::Load(uint32 length, FILESTREAM file, uint32* offset, int32 unknown) {
    m_size = (uint16)(length / sizeof(tMissionTextOffset));
    CFileMgr::Read(file, (char*)m_offsets, sizeof(tMissionTextOffset) * m_size);
    *offset += sizeof(tMissionTextOffset) * m_size;

    return true;
}
