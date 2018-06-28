/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "COctTree.h"

class  COctTreeBase : public COctTree {
public:
    unsigned int numBranches;
    bool32       hasTransparentPixels;

    COctTreeBase();
    void Init(int numBranches);
    bool Insert(unsigned char colorRed, unsigned char colorGreen, unsigned char colorBlue);
    void ReduceBranches(int newBranchesCount);
};

VALIDATE_SIZE(COctTreeBase, 0x30);
