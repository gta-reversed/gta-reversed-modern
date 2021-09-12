#pragma once

#include "eAudioFileType.h"

struct tAudioExtensionType {
    char           extension[8];
    eAudioFileType type;
};

VALIDATE_SIZE(tAudioExtensionType, 0xc);
