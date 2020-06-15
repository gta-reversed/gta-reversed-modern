#pragma once

#include <cstdint>

#include "PluginBase.h"

#include "eAudioFileType.h"

struct tUserTracksInfo
{
    std::uint32_t startUfilesPath;
    std::uint32_t pathLength;
    eAudioFileType fileType;
};

VALIDATE_SIZE(tUserTracksInfo, 0xc);
