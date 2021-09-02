#pragma once

#include <cstdint>

#include "eAudioFileType.h"

struct tUserTracksInfo {
    uint32         startUfilesPath;
    uint32         pathLength;
    eAudioFileType fileType;
};

VALIDATE_SIZE(tUserTracksInfo, 0xc);
