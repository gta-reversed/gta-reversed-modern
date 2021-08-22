#pragma once

#include "CText.h"

struct tTextOffset {
    char szMissionName[8];
    uint offset;
};

// TABL block
class CMissionTextOffsets {
public:
    static const ushort MAX_MISSION_TEXTS = 200;

    tTextOffset data[MAX_MISSION_TEXTS];
    uint        size;

public:
    CMissionTextOffsets();;

    void Load(uint length, FILE* file, uint* offset, uint nSkipBytes);
};
