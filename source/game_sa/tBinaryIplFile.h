/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Base.h"
#include "CarGenerator.h" // CFileCarGenerator
#include "FileObjectInstance.h" // CFileObjectInstance

struct tBinaryIplFile {
    char fourcc[4]; // Should be "bnry" (no null terminator)

    uint32 numInst, numUnk1, numUnk2, numUnk3, numCarGens, numUnk4; // Number of sections

    uint32 offsetInst, sizeInst; // => CFileObjectInstance
    uint32 offsetUnk1, sizeUnk1;
    uint32 offsetUnk2, sizeUnk2;
    uint32 offsetUnk3, sizeUnk3;
    uint32 offsetCarGens, sizeCarGens; // => CFileCarGenerator
    uint32 offsetUnk4, sizeUnk4;


    auto GetObjInstances() const { return std::span{ reinterpret_cast<CFileObjectInstance*>((char*)this + offsetInst), (size_t)numInst }; }
    auto GetCarGens()      const { return std::span{ reinterpret_cast<CFileCarGenerator*>((char*)this + offsetCarGens), (size_t)numCarGens }; }
};
VALIDATE_SIZE(tBinaryIplFile, 0x4C);
