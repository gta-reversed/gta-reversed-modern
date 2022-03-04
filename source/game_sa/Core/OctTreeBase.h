/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "OctTree.h"

class COctTreeBase : public COctTree {
public:
    uint32 m_nNumBranches;
    bool32 m_bHasTransparentPixels;

public:
    COctTreeBase();
    ~COctTreeBase() = default; // 0x856690

    bool InsertTree(uint8 colorRed, uint8 colorGreen, uint8 colorBlue) override;
    void FillPalette(uint8* colors) override;

    void Init(int32 numBranches);
    bool Insert(uint8 colorRed, uint8 colorGreen, uint8 colorBlue);
    void ReduceBranches(int32 newBranchesCount);
};

extern COctTreeBase& gOctTreeBase;

VALIDATE_SIZE(COctTreeBase, 0x30);
