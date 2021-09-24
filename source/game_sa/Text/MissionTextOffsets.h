#pragma once

#include "CText.h"

struct tTextOffset {
    char   szMissionName[8];
    uint32 offset;
};

// TABL block
class CMissionTextOffsets {
public:
    static const uint16 MAX_MISSION_TEXTS = 200;

    tTextOffset data[MAX_MISSION_TEXTS];
    uint32        size;

public:
    CMissionTextOffsets();;

    void Load(uint32 length, FILE* file, uint32* offset, uint32 nSkipBytes);
};
