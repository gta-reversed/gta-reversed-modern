/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "COctTree.h"

class COctTreeBase : public COctTree {
public:
    uint32 numBranches;
    bool32 hasTransparentPixels;

public:
    COctTreeBase();

    void Init(int32 numBranches);
    bool Insert(uint8 colorRed, uint8 colorGreen, uint8 colorBlue);
    void ReduceBranches(int32 newBranchesCount);
};

VALIDATE_SIZE(COctTreeBase, 0x30);
