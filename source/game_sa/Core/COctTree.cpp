#include "StdInc.h"

bool COctTree::ms_bFailed;
unsigned int COctTree::ms_level;
CPool<COctTree> COctTree::ms_octTreePool;
COctTree* gpTmpOctTree;

bool COctTree::InsertTree(unsigned char colorRed, unsigned char colorGreen, unsigned char colorBlue) {
    const unsigned short poolind = ((colorRed << ms_level >> 5) & 4) + ((colorGreen << ms_level >> 6) & 2) + ((colorBlue << ms_level >> 7) & 1);
    ms_level++;

    redComponent += colorRed;
    greenComponent += colorGreen;
    blueComponent += colorBlue;
    level++;

    if (ms_level == 8 || lastStep) {
        ms_level = 0;
        lastStep = true;

        RemoveChildren();

        return level == 1;
    }

    COctTree* treeel = nullptr;
    if (children[poolind] >= 0) {
        if (!ms_octTreePool.m_byteMap[children[poolind]].bEmpty)
            treeel = &ms_octTreePool.m_pObjects[children[poolind]];
    } else {
        treeel = ms_octTreePool.New();

        if (!treeel) {
            ms_bFailed = true;
            return 0;
        }

        children[poolind] = (treeel - ms_octTreePool.m_pObjects) / sizeof(COctTree);
    }

    bool treeinserted = treeel->InsertTree(colorRed, colorGreen, colorBlue);

    if (ms_bFailed && treeel->level < 2) {
        delete treeel;
        children[poolind] = -1;

        return 0;
    }

    return treeinserted;
}

void COctTree::FillPalette(unsigned char* colors) {
    if (lastStep == 1) {
        colors[ms_level + 0] = redComponent / level;
        colors[ms_level + 1] = greenComponent / level;
        colors[ms_level + 2] = blueComponent / level;
        colors[ms_level + 3] = 128;

        level = ms_level++;
    } else {
        for (unsigned int i = 7; i; --i) {
            const short poolind = children[i];

            if (poolind < 0)
                continue;

            if (!ms_octTreePool.m_byteMap[poolind].bEmpty)
                ms_octTreePool.m_pObjects[poolind].FillPalette(colors);
        }
    }
}

COctTree::COctTree() {
    level = 0;
    redComponent = 0;
    greenComponent = 0;
    blueComponent = 0;

    children[0] = -1;
    children[2] = -1;
    children[4] = -1;
    children[6] = -1;

    lastStep = false;
}

COctTree::~COctTree() {
    empty();
    ms_octTreePool.Delete(this);
}

unsigned int COctTree::FindNearestColour(unsigned char colorRed, unsigned char colorGreen, unsigned char colorBlue) {
    if (lastStep != 0)
        return level;

    COctTree* treeel = this;
    do {
        unsigned int treeind = treeel->children[(colorBlue >> 7) + ((colorGreen >> 6) & 2) + ((colorRed >> 5) & 4)];
        if (!ms_octTreePool.m_byteMap[treeind].bEmpty)
            treeel = &ms_octTreePool.m_pObjects[treeind];

        colorRed *= 2;
        colorGreen *= 2;
        colorBlue *= 2;
    } while (!treeel->lastStep);

    return treeel->level;
}

void COctTree::InitPool(void* data, int dataSize) {
    ms_octTreePool.Init(dataSize / 41, data, (char*)data + 40 + (dataSize / 41));
    ms_octTreePool.m_bIsLocked = true;
}

unsigned int COctTree::NoOfChildren() {
    unsigned int numofchildren = 0;

    if (children[0] >= 0)
        numofchildren++;

    if (children[1] >= 0)
        numofchildren++;

    if (children[2] >= 0)
        numofchildren++;

    if (children[3] >= 0)
        numofchildren++;

    if (children[4] >= 0)
        numofchildren++;

    if (children[5] >= 0)
        numofchildren++;

    if (children[6] >= 0)
        numofchildren++;

    if (children[7] >= 0)
        numofchildren++;

    return numofchildren;
}

void COctTree::ReduceTree() {
    if (lastStep == 1)
        return;

    ms_level++;

    unsigned int currlevel = 0;
    unsigned int totallevels = 0;
    static unsigned int lastlevel;
    for (unsigned int i = 7; i; --i) {
        if (children[i] < 0)
            continue;

        currlevel++;

        if (!ms_octTreePool.m_byteMap[children[i]].bEmpty) {
            COctTree* tree = &ms_octTreePool.m_pObjects[children[i]];

            tree->ReduceTree();
            totallevels += tree->level;
        }
    }

    if (currlevel >= 2 && (totallevels < lastlevel || !gpTmpOctTree)) {
        lastlevel = totallevels;
        gpTmpOctTree = this;
    }

    ms_level--;
}

void COctTree::RemoveChildren() {
    for (unsigned int i = 7; i; --i) {
        const short poolind = children[i];

        if (poolind < 0)
            continue;

        if (ms_octTreePool.m_byteMap[poolind].bEmpty)
            continue;

        if (!&ms_octTreePool.m_pObjects[poolind])
            continue;

        delete &ms_octTreePool.m_pObjects[poolind];

        children[i] = -1;
    }
}

void COctTree::ShutdownPool() {
    ms_octTreePool.Flush();
}

void COctTree::empty() {
    level = 0;
    redComponent = 0;
    greenComponent = 0;
    blueComponent = 0;

    for (unsigned int i = 7; i; --i) {
        const short poolind = children[i];

        if (poolind < 0)
            continue;

        if (!ms_octTreePool.m_byteMap[poolind].bEmpty && ms_octTreePool.m_pObjects + poolind)
            delete &ms_octTreePool.m_pObjects[poolind];

        children[i] = -1;
    }
}

void* COctTree::operator new(unsigned int size) {
    return ms_octTreePool.New();
}
