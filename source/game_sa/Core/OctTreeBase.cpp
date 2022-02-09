#include "StdInc.h"

#include "OctTreeBase.h"

COctTreeBase& gOctTreeBase = *(COctTreeBase*)0xBC1290;

// 0x5A7570
COctTreeBase::COctTreeBase() : COctTree() {
    // NOP
}

// 0x5A7710
bool COctTreeBase::InsertTree(uint8 colorRed, uint8 colorGreen, uint8 colorBlue) {
    ms_level = 0;

    if (!COctTree::InsertTree(colorRed, colorGreen, colorBlue))
        return false;

    m_nNumBranches--;

    return true;
}

// 0x5A7280
void COctTreeBase::FillPalette(uint8* colors) {
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

// 0x5A7260
void COctTreeBase::Init(int32 numBranches) {
    ms_level = 0;

    m_nNumBranches = numBranches;
    m_bHasTransparentPixels = 0;

    empty();
}

// 0x5A7750
bool COctTreeBase::Insert(uint8 colorRed, uint8 colorGreen, uint8 colorBlue) {
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

// 0x5A7840
void COctTreeBase::ReduceBranches(int32 newBranchesCount) {
    const int32 branchesToCount = m_bHasTransparentPixels ? newBranchesCount + 1 : newBranchesCount;

    while (m_nNumBranches < branchesToCount) {
        gpTmpOctTree = nullptr;
        ReduceTree();
        m_nNumBranches += gpTmpOctTree->NoOfChildren() - 1;

        gpTmpOctTree->m_bLastStep = true;
        gpTmpOctTree->RemoveChildren();
    }
}
