/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

struct tBinaryIplFile {
    char   fourcc[4]; // "bnry"
    uint16 numInstances;
    char   _unused06[14];
    uint16 numCarGenerators;
    char   _unused16[6];
    uint32 instancesOffset; // file offset to CFileObjectInstance structures
    char   _unused20[28];
    uint32 carGeneratorsOffset;
    char   _unused40[12];
};

VALIDATE_SIZE(tBinaryIplFile, 0x4C);
