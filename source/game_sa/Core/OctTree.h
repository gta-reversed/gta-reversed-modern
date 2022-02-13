/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Pool.h"

class COctTree {
public:
    uint32 m_nLevel;
    bool   m_bLastStep;       // no children
    int32  m_aChildrens[4];   // pool slot IDs,  -1 - empty
    uint32 m_nRedComponent;
    uint32 m_nGreenComponent;
    uint32 m_nBlueComponent;

public:
    static bool&            ms_bFailed;
    static uint32&          ms_level;
    static CPool<COctTree>& ms_octTreePool;

public:
    COctTree();
    ~COctTree();

    static void* operator new(uint32 size);
    static void  operator delete(void* data);

    //vtable
    virtual bool InsertTree(uint8 colorRed, uint8 colorGreen, uint8 colorBlue);
    virtual void FillPalette(uint8* colors);

    static void InitPool(void* data, int32 dataSize);
    static void ShutdownPool();
    uint32      FindNearestColour(uint8 colorRed, uint8 colorGreen, uint8 colorBlue);
    uint32      NoOfChildren();
    void        ReduceTree();
    void        RemoveChildren();
    void        empty();
};

VALIDATE_SIZE(COctTree, 0x28);

extern COctTree*& gpTmpOctTree;
