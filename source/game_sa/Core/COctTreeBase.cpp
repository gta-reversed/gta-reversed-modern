#include "StdInc.h"

#include "COctTreeBase.h"

COctTreeBase& gOctTreeBase = *(COctTreeBase*)0xBC1290;

//  0x5A7570
COctTreeBase::COctTreeBase() : COctTree() {
    // NOP
}

//  0x856690
COctTreeBase::~COctTreeBase() {}

//  0x5A7710
bool COctTreeBase::InsertTree(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue) {
    ms_level = 0;

    if (!COctTree::InsertTree(colorRed, colorGreen, colorBlue))
        return false;

    m_nNumBranches--;

    return true;
}

//  0x5A7280
void COctTreeBase::FillPalette(uint8_t* colors) {
    ms_level = 0;

    if (m_bHasTransparentPixels) {
        colors[0] = 0; // red
        colors[1] = 0; // green
        colors[2] = 0; // blue
        colors[3] = 0; // alpha

        ms_level = 1;
    }

    COctTree::FillPalette(colors);
}

//  0x5A7260
void COctTreeBase::Init(int32_t numBranches) {
    ms_level = 0;

    m_nNumBranches = numBranches;
    m_bHasTransparentPixels = 0;

    empty();
}

//  0x5A7750
bool COctTreeBase::Insert(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue) {
    while (true) {
        ms_bFailed = false;

        if (InsertTree(colorRed, colorGreen, colorBlue))
            break;

        if (ms_bFailed) {
            gpTmpOctTree = nullptr;
            ReduceTree();
            m_nNumBranches += gpTmpOctTree->NoOfChildren() - 1;

            gpTmpOctTree->m_bLastStep = true;
            gpTmpOctTree->RemoveChildren();

            if (ms_bFailed)
                continue;
        }

        return false;
    }

    if (m_nNumBranches <= 0) {
        gpTmpOctTree = nullptr;
        ReduceTree();
        m_nNumBranches += gpTmpOctTree->NoOfChildren() - 1;

        gpTmpOctTree->m_bLastStep = true;
        gpTmpOctTree->RemoveChildren();
    }

    return true;
}

//  0x5A7840
void COctTreeBase::ReduceBranches(int32_t newBranchesCount) {
    const int32_t branchesToCount = m_bHasTransparentPixels ? newBranchesCount + 1 : newBranchesCount;

    while (m_nNumBranches < branchesToCount) {
        gpTmpOctTree = nullptr;
        ReduceTree();
        m_nNumBranches += gpTmpOctTree->NoOfChildren() - 1;

        gpTmpOctTree->m_bLastStep = true;
        gpTmpOctTree->RemoveChildren();
    }
}

void COctTreeBase::InjectHooks() {
    ReversibleHooks::Install("COctTreeBase", "COctTreeBase", 0x5A7570, &COctTreeBase::Constructor);
    ReversibleHooks::Install("COctTreeBase", "~COctTreeBase", 0x856690, &COctTreeBase::Destructor);
    ReversibleHooks::Install("COctTreeBase", "Init", 0x5A7260, &COctTreeBase::Init);
    ReversibleHooks::Install("COctTreeBase", "Insert", 0x5A7750, &COctTreeBase::Insert);
    ReversibleHooks::Install("COctTreeBase", "InsertTree", 0x5A7710, &COctTreeBase::InsertTree);
    ReversibleHooks::Install("COctTreeBase", "FillPalette", 0x5A7280, &COctTreeBase::FillPalette);
    ReversibleHooks::Install("COctTreeBase", "ReduceBranches", 0x5A7840, &COctTreeBase::ReduceBranches);
}

COctTreeBase* COctTreeBase::Constructor() {
    this->COctTreeBase::COctTreeBase();
    return this;
}

COctTreeBase* COctTreeBase::Destructor() {
    this->COctTreeBase::~COctTreeBase();
    return this;
}

bool COctTreeBase::InsertTree_Reversed(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue) {
    return COctTreeBase::InsertTree(colorRed, colorGreen, colorBlue);
}

void COctTreeBase::FillPalette_Reversed(uint8_t* colors) {
    COctTreeBase::FillPalette(colors);
}
