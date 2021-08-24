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
    uint32_t        numBranches;
    bool32          hasTransparentPixels;

    //vtable

    virtual bool    InsertTree(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue) override;
    virtual void    FillPalette(uint8_t* colors) override;

    COctTreeBase();
    ~COctTreeBase();

    void            Init(int32_t numBranches);
    bool            Insert(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue);
    void            ReduceBranches(int32_t newBranchesCount);

    static void     InjectHooks();
};

extern COctTreeBase** gOctTreeBase;

VALIDATE_SIZE(COctTreeBase, 0x30);
