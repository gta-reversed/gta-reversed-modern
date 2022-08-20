/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CAnimBlock {
public:
    char         szName[16];
    bool         bLoaded;
    char         pad;
    int16        usRefs;
    int32        startAnimation;
    int32        animationCount;
    AssocGroupId animationStyle;
};

VALIDATE_SIZE(CAnimBlock, 0x20);
