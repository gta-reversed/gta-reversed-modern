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
    uint32_t m_nNumBranches;
    bool32   m_bHasTransparentPixels;

public:
    COctTreeBase();
    ~COctTreeBase();

    //vtable

    bool InsertTree(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue) override;
    void FillPalette(uint8_t* colors) override;

    void Init(int32_t numBranches);
    bool Insert(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue);
    void ReduceBranches(int32_t newBranchesCount);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    COctTreeBase* Constructor();
    COctTreeBase* Destructor();

    bool InsertTree_Reversed(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue);
    void FillPalette_Reversed(uint8_t* colors);
};

extern COctTreeBase& gOctTreeBase;

VALIDATE_SIZE(COctTreeBase, 0x30);
