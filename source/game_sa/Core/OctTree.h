/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Pool.h"

class COctTree {
protected:
    COctTree(plugin::dummy_func_t) {}

public:
    uint32 level;
    bool   lastStep; // no childrens
    char   _pad09;
    int16  childrens[8]; // pool slot IDs,  -1 - empty
    char   _pad1A[2];
    uint32 redComponent;
    uint32 greenComponent;
    uint32 blueComponent;

    static bool&            ms_bFailed;
    static uint32&          ms_level;
    static CPool<COctTree>& ms_octTreePool;

public:
    // vtable

    bool InsertTree(uint8 colorRed, uint8 colorGreen, uint8 colorBlue);
    void FillPalette(uint8* colors);

    static void* operator new(uint32 size);
    static void  operator delete(void* data);

    COctTree();
    ~COctTree();

    uint32 FindNearestColour(uint8 colorRed, uint8 colorGreen, uint8 colorBlue);
    void   InitPool(void* data, int32 dataSize);
    uint32 NoOfChildren();
    void   ReduceTree();
    void   RemoveChildren();
    void   ShutdownPool();
    void   empty();

private:
    virtual void virtual_dummy() {}
};

VALIDATE_SIZE(COctTree, 0x28);

extern COctTree*& gpTmpOctTree;