/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CAnimationStyleDescriptor {
public:
    char  groupName[16];
    char  blockName[16];
    int32 field_20;
    int32 animsCount;
    void* animNames;
    void* animDesc;
};

VALIDATE_SIZE(CAnimationStyleDescriptor, 0x30);
