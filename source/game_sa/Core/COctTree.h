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
    unsigned int            level;
    bool                    lastStep;       // no children
private:
    char                    _pad09;
public:
    short                   children[8];    // pool slot IDs,  -1 - empty
private:
    char                    _pad1A[2];
public:
    unsigned int            redComponent;
    unsigned int            greenComponent;
    unsigned int            blueComponent;

    static bool             ms_bFailed;
    static unsigned int     ms_level;
    static CPool<COctTree>  ms_octTreePool;

    //vtable

    virtual bool            InsertTree(unsigned char colorRed, unsigned char colorGreen, unsigned char colorBlue);
    virtual void            FillPalette(unsigned char* colors);

    COctTree();
    ~COctTree();

    unsigned int            FindNearestColour(unsigned char colorRed, unsigned char colorGreen, unsigned char colorBlue);
    unsigned int            NoOfChildren();
    void                    ReduceTree();
    void                    RemoveChildren();
    void                    empty();

    void                    InitPool(void* data, int dataSize);
    void                    ShutdownPool();

    //static void operator delete(void* data);  //  Not needed, since destructor already does what this operator does.
    static void*            operator new(unsigned int size);
};

VALIDATE_SIZE(COctTree, 0x28);

extern COctTree *gpTmpOctTree;
