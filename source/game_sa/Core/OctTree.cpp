#include "StdInc.h"

#include "OctTree.h"

bool& COctTree::ms_bFailed = *(bool*)0xBC12DC;
uint32& COctTree::ms_level = *(uint32*)0xBC12E0;
CPool<COctTree>& COctTree::ms_octTreePool = *(CPool<COctTree>*)0xBC12E4;
COctTree*& gpTmpOctTree = *(COctTree**)0xBC12D8;

// 0x5A6DB0
COctTree::COctTree() {
    m_nLevel = 0;
    m_nRedComponent = 0;
    m_nGreenComponent = 0;
    m_nBlueComponent = 0;
    std::ranges::fill(m_aChildrens, -1);
    m_bLastStep = false;
}

// 0x5A7490
COctTree::~COctTree() {
    empty();
}

// 0x5A7410
void* COctTree::operator new(uint32 size) {
    return ms_octTreePool.New();
}

// 0x5A7420
void COctTree::operator delete(void* data) {
    ms_octTreePool.Delete(static_cast<COctTree*>(data));
}

// 0x5A7460
void COctTree::InitPool(void* data, int32 dataSize) {
    ms_octTreePool.Init(
        dataSize / sizeof(COctTree) + 1,
        data,
        (char*)data + sizeof(COctTree) * (dataSize / sizeof(COctTree)) + 1
    );
    ms_octTreePool.m_bIsLocked = true;
}

// 0x5A6F70
void COctTree::ShutdownPool() {
    ms_octTreePool.Flush();
}

// 0x5A75B0
bool COctTree::InsertTree(uint8 colorRed, uint8 colorGreen, uint8 colorBlue) {
    const auto poolIndex = ((colorRed << ms_level >> 5) & 4) + ((colorGreen << ms_level >> 6) & 2) + ((colorBlue << ms_level >> 7) & 1); // todo:
    ms_level++;

    m_nRedComponent   += colorRed;
    m_nGreenComponent += colorGreen;
    m_nBlueComponent  += colorBlue;
    m_nLevel++;

    if (ms_level == std::size(m_aChildrens) || m_bLastStep) {
        ms_level = 0;
        m_bLastStep = true;

        RemoveChildren();

        return m_nLevel == 1;
    }

    COctTree* treeElement = nullptr;
    if (m_aChildrens[poolIndex] >= 0) {
        if (!ms_octTreePool.IsFreeSlotAtIndex(poolIndex))
            treeElement = ms_octTreePool.GetAt(poolIndex);
    } else {
        treeElement = ms_octTreePool.New();

        if (!treeElement) {
            ms_bFailed = true;
            return false;
        }

        m_aChildrens[poolIndex] = ms_octTreePool.GetIndex(treeElement);
    }

#ifdef FIX_BUGS
    if (!treeElement)
        return false;
#endif

    bool bTreeInserted = treeElement->InsertTree(colorRed, colorGreen, colorBlue);

    if (ms_bFailed && treeElement->m_nLevel < 2) {
        delete treeElement;
        m_aChildrens[poolIndex] = -1;

        return false;
    }

    return bTreeInserted;
}

// 0x5A70F0
void COctTree::FillPalette(uint8* colors) {
    if (m_bLastStep) {
        colors[ms_level + 0] = m_nRedComponent   / m_nLevel;
        colors[ms_level + 1] = m_nGreenComponent / m_nLevel;
        colors[ms_level + 2] = m_nBlueComponent  / m_nLevel;
        colors[ms_level + 3] = 128;

        m_nLevel = ms_level++;
    } else {
        for (auto i = std::size(m_aChildrens) - 1; i; --i) {
            const auto poolIndex = m_aChildrens[i];

            if (poolIndex < 0)
                continue;

            if (!ms_octTreePool.IsFreeSlotAtIndex(poolIndex))
                ms_octTreePool.GetAt(poolIndex)->FillPalette(colors);
        }
    }
}

// 0x5A71E0
uint32 COctTree::FindNearestColour(uint8 colorRed, uint8 colorGreen, uint8 colorBlue) {
    if (m_bLastStep)
        return m_nLevel;

    COctTree* treeElement = this;
    do {
        uint32 treeIndex = treeElement->m_aChildrens[(colorBlue >> 7) + ((colorGreen >> 6) & 2) + ((colorRed >> 5) & 4)]; // todo:
        if (!ms_octTreePool.IsFreeSlotAtIndex(treeIndex))
            treeElement = ms_octTreePool.GetAt(treeIndex);

        colorRed *= 2;
        colorGreen *= 2;
        colorBlue *= 2;
    } while (!treeElement->m_bLastStep);

    return treeElement->m_nLevel;
}

// 0x5A6DE0
uint32 COctTree::NoOfChildren() {
    uint32 numOfChildren = 0;
    for (auto& m_aChildren : m_aChildrens)
        if (m_aChildren >= 0)
            numOfChildren++;

    return numOfChildren;
}

// 0x5A7040
void COctTree::ReduceTree() {
    if (m_bLastStep)
        return;

    ms_level++;

    uint32 currentLevel = 0;
    uint32 totalLevels = 0;
    static uint32 lastLevel;
    for (auto i = std::size(m_aChildrens) - 1; i; --i) {
        if (m_aChildrens[i] < 0)
            continue;

        currentLevel++;

        if (!ms_octTreePool.IsFreeSlotAtIndex(m_aChildrens[i])) {
            COctTree* tree = ms_octTreePool.GetAt(m_aChildrens[i]);

            tree->ReduceTree();
            totalLevels += tree->m_nLevel;
        }
    }

    if (currentLevel >= 2 && (totalLevels < lastLevel || !gpTmpOctTree)) {
        lastLevel = totalLevels;
        gpTmpOctTree = this;
    }

    ms_level--;
}

// 0x5A74F0
void COctTree::RemoveChildren() {
    for (uint32 i = std::size(m_aChildrens) - 1; i; --i) {
        auto& poolIndex = m_aChildrens[i];

        if (poolIndex < 0)
            continue;

        if (ms_octTreePool.IsFreeSlotAtIndex(poolIndex))
            continue;

        COctTree* elem = ms_octTreePool.GetAt(poolIndex);
        if (!elem)
            continue;

        delete elem;
        poolIndex = -1;
    }
}

// 0x5A6FC0
void COctTree::empty() {
    m_nLevel = 0;
    m_nRedComponent = 0;
    m_nGreenComponent = 0;
    m_nBlueComponent = 0;

    for (uint32 i = std::size(m_aChildrens) - 1; i; --i) {
        auto& poolIndex = m_aChildrens[i];

        if (poolIndex < 0)
            continue;

        if (!ms_octTreePool.IsFreeSlotAtIndex(poolIndex) && ms_octTreePool.GetAt(poolIndex))
            delete ms_octTreePool.GetAt(poolIndex);

        poolIndex = -1;
    }
}
