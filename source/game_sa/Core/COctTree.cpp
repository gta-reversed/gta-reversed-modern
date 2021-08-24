#include "StdInc.h"

bool& COctTree::ms_bFailed = *(bool*)0xBC12DC;
uint32_t& COctTree::ms_level = *(uint32_t*)0xBC12E0;
CPool<COctTree>& COctTree::ms_octTreePool = *(CPool<COctTree>*)0xBC12E4;
COctTree** gpTmpOctTree = (COctTree**)0xBC12D8;

//  0x5A6DB0
COctTree::COctTree() {
    level = 0;
    redComponent = 0;
    greenComponent = 0;
    blueComponent = 0;

    for (uint32_t i = ARRAY_SIZE(children) - 1; i; --i)
        children[i] = -1;

    lastStep = false;
}

//  0x5A7490
COctTree::~COctTree() {
    empty();
    ms_octTreePool.Delete(this);
}

//  0x5A75B0
bool COctTree::InsertTree(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue) {
    const uint16_t poolIndex = ((colorRed << ms_level >> 5) & 4) + ((colorGreen << ms_level >> 6) & 2) + ((colorBlue << ms_level >> 7) & 1);
    ms_level++;

    redComponent += colorRed;
    greenComponent += colorGreen;
    blueComponent += colorBlue;
    level++;

    if (ms_level == ARRAY_SIZE(children) || lastStep) {
        ms_level = 0;
        lastStep = true;

        RemoveChildren();

        return level == 1;
    }

    COctTree* treeElement = nullptr;
    if (children[poolIndex] >= 0) {
        if (!ms_octTreePool.IsFreeSlotAtIndex(poolIndex))
            treeElement = ms_octTreePool.GetAt(poolIndex);
    } else {
        treeElement = ms_octTreePool.New();

        if (!treeElement) {
            ms_bFailed = true;
            return 0;
        }

        children[poolIndex] = ms_octTreePool.GetIndex(treeElement);
    }

#ifdef FIX_BUGS
    if (!treeel)
        return 0;
#endif

    bool bTreeInserted = treeElement->InsertTree(colorRed, colorGreen, colorBlue);

    if (ms_bFailed && treeElement->level < 2) {
        delete treeElement;
        children[poolIndex] = -1;

        return 0;
    }

    return bTreeInserted;
}

//  0x5A70F0
void COctTree::FillPalette(uint8_t* colors) {
    if (lastStep == 1) {
        colors[ms_level + 0] = redComponent / level;
        colors[ms_level + 1] = greenComponent / level;
        colors[ms_level + 2] = blueComponent / level;
        colors[ms_level + 3] = 128;

        level = ms_level++;
    } else {
        for (uint32_t i = ARRAY_SIZE(children) - 1; i; --i) {
            const int16_t poolIndex = children[i];

            if (poolIndex < 0)
                continue;

            if (!ms_octTreePool.IsFreeSlotAtIndex(poolIndex))
                ms_octTreePool.GetAt(poolIndex)->FillPalette(colors);
        }
    }
}

//  0x5A71E0
uint32_t COctTree::FindNearestColour(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue) {
    if (lastStep != 0)
        return level;

    COctTree* treeElement = this;
    do {
        uint32_t treeIndex = treeElement->children[(colorBlue >> 7) + ((colorGreen >> 6) & 2) + ((colorRed >> 5) & 4)];
        if (!ms_octTreePool.IsFreeSlotAtIndex(treeIndex))
            treeElement = ms_octTreePool.GetAt(treeIndex);

        colorRed *= 2;
        colorGreen *= 2;
        colorBlue *= 2;
    } while (!treeElement->lastStep);

    return treeElement->level;
}

//  0x5A6DE0
uint32_t COctTree::NoOfChildren() {
    unsigned int numOfChildren = 0;
    for (uint32_t i = ARRAY_SIZE(children) - 1; i; --i)
        if (children[i] >= 0)
            numOfChildren++;

    return numOfChildren;
}

//  0x5A7040
void COctTree::ReduceTree() {
    if (lastStep == 1)
        return;

    ms_level++;

    uint32_t currentLevel = 0;
    uint32_t totalLevels = 0;
    static uint32_t lastLevel;
    for (uint32_t i = ARRAY_SIZE(children) - 1; i; --i) {
        if (children[i] < 0)
            continue;

        currentLevel++;

        if (!ms_octTreePool.IsFreeSlotAtIndex(children[i])) {
            COctTree* tree = ms_octTreePool.GetAt(children[i]);

            tree->ReduceTree();
            totalLevels += tree->level;
        }
    }

    if (currentLevel >= 2 && (totalLevels < lastLevel || !*gpTmpOctTree)) {
        lastLevel = totalLevels;
        *gpTmpOctTree = this;
    }

    ms_level--;
}

//  0x5A74F0
void COctTree::RemoveChildren() {
    for (uint32_t i = ARRAY_SIZE(children) - 1; i; --i) {
        const int16_t poolIndex = children[i];

        if (poolIndex < 0)
            continue;

        if (ms_octTreePool.IsFreeSlotAtIndex(poolIndex))
            continue;

        if (!ms_octTreePool.GetAt(poolIndex))
            continue;

        delete ms_octTreePool.GetAt(poolIndex);

        children[i] = -1;
    }
}

//  0x5A6FC0
void COctTree::empty() {
    level = 0;
    redComponent = 0;
    greenComponent = 0;
    blueComponent = 0;

    for (uint32_t i = ARRAY_SIZE(children) - 1; i; --i) {
        const int16_t poolIndex = children[i];

        if (poolIndex < 0)
            continue;

        if (!ms_octTreePool.IsFreeSlotAtIndex(poolIndex) && ms_octTreePool.GetAt(poolIndex))
            delete ms_octTreePool.GetAt(poolIndex);

        children[i] = -1;
    }
}

//  0x5A7460
void COctTree::InitPool(void* data, int32_t dataSize) {
    ms_octTreePool.Init(dataSize / sizeof(COctTree) + 1, data, (char*)data + sizeof(COctTree) * (dataSize / sizeof(COctTree)) + 1);
    ms_octTreePool.m_bIsLocked = true;
}

//  0x5A6F70
void COctTree::ShutdownPool() {
    ms_octTreePool.Flush();
}

//  0x5A7410
void* COctTree::operator new(uint32_t size) {
    return ms_octTreePool.New();
}

void COctTree::InjectHooks() {
    //  Virtual class methods
    ReversibleHooks::Install("COctTree", "InsertTree", 0x5A75B0, &COctTree::InsertTree);
    ReversibleHooks::Install("COctTree", "FillPalette", 0x5A70F0, &COctTree::FillPalette);

    //  Class methods
    ReversibleHooks::Install("COctTree", "FindNearestColour", 0x5A71E0, &COctTree::FindNearestColour);
    ReversibleHooks::Install("COctTree", "NoOfChildren", 0x5A6DE0, &COctTree::NoOfChildren);
    ReversibleHooks::Install("COctTree", "ReduceTree", 0x5A7040, &COctTree::ReduceTree);
    ReversibleHooks::Install("COctTree", "RemoveChildren", 0x5A74F0, &COctTree::RemoveChildren);
    ReversibleHooks::Install("COctTree", "empty", 0x5A6FC0, &COctTree::empty);

    //  Static class methods
    ReversibleHooks::Install("COctTree", "InitPool", 0x5A7460, &COctTree::InitPool);
    ReversibleHooks::Install("COctTree", "ShutdownPool", 0x5A6F70, &COctTree::ShutdownPool);
}
