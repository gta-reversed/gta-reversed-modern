/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPool.h"

class COctTree {
public:
    uint32_t                m_nLevel;
    bool                    m_bLastStep;       // no children
    char                    _pad09;
    short m_aChildrens[8];    // pool slot IDs,  -1 - empty
    char                    _pad1A[2];
    uint32_t                m_nRedComponent;
    uint32_t                m_nGreenComponent;
    uint32_t                m_nBlueComponent;

public:
    static bool&            ms_bFailed;
    static uint32_t&        ms_level;
    static CPool<COctTree>& ms_octTreePool;

public:
    COctTree();
    ~COctTree();

    static void*            operator new(uint32_t size);
    static void             operator delete(void* data);

    //vtable
    virtual bool            InsertTree(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue);
    virtual void            FillPalette(uint8_t* colors);

    uint32_t                FindNearestColour(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue);
    uint32_t                NoOfChildren();
    void                    ReduceTree();
    void                    RemoveChildren();
    void                    empty();

    static void             InitPool(void* data, int32_t dataSize);
    static void             ShutdownPool();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    COctTree* Constructor();
    COctTree* Destructor();

    bool InsertTree_Reversed(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue);
    void FillPalette_Reversed(uint8_t* colors);
};

VALIDATE_SIZE(COctTree, 0x28);

extern COctTree*& gpTmpOctTree;
