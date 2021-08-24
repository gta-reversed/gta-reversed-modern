/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPool.h"

class  COctTree {
public:
    uint32_t                level;
    bool                    lastStep;       // no children
private:
    char                    _pad09;
public:
    short                   children[8];    // pool slot IDs,  -1 - empty
private:
    char                    _pad1A[2];
public:
    uint32_t                redComponent;
    uint32_t                greenComponent;
    uint32_t                blueComponent;

    static bool&            ms_bFailed;
    static uint32_t&        ms_level;
    static CPool<COctTree>& ms_octTreePool;

    //vtable

    virtual bool            InsertTree(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue);
    virtual void            FillPalette(uint8_t* colors);

    COctTree();
    ~COctTree();

    uint32_t                FindNearestColour(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue);
    uint32_t                NoOfChildren();
    void                    ReduceTree();
    void                    RemoveChildren();
    void                    empty();

    static void             InitPool(void* data, int32_t dataSize);
    static void             ShutdownPool();

    //static void operator delete(void* data);  //  Not needed, since destructor already does what this operator does.
    static void*            operator new(uint32_t size);

    static void             InjectHooks();
};

VALIDATE_SIZE(COctTree, 0x28);

extern COctTree **gpTmpOctTree;
