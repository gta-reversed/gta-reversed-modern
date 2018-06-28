/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CFileObjectInstance.h"

struct tBinaryIplFile {
    char           fourcc[4]; // "bnry"
    unsigned short numInstances;
private:
    char _unused06[14];
public:
    unsigned short numCarGenerators;
private:
    char _unused16[6];
public:
    unsigned int   instancesOffset; // file offset to CFileObjectInstance structures
private:
    char _unused20[28];
public:
    unsigned int   carGeneratorsOffset;
private:
    char _unused40[12];
public:
};

VALIDATE_SIZE(tBinaryIplFile, 0x4C);