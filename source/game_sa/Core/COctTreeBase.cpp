#include "StdInc.h"

COctTreeBase** gOctTreeBase = (COctTreeBase**)0xBC1290;

//  0x5A7570
COctTreeBase::COctTreeBase() {}

//  0x856690
COctTreeBase::~COctTreeBase() {}

//  0x5A7710
bool COctTreeBase::InsertTree(uint8_t colorRed, uint8_t colorGreen, uint8_t colorBlue) {
    ms_level = 0;

    if (!COctTree::InsertTree(colorRed, colorGreen, colorBlue))
        return false;

    numBranches--;

    return true;
}

//  0x5A7280
void COctTreeBase::FillPalette(uint8_t* colors) {
    ms_level = 0;

    if (hasTransparentPixels) {
        colors[0] = 0;
        colors[1] = 0;
        colors[2] = 0;
        colors[3] = 0;

        ms_level = 1;
    }

    COctTree::FillPalette(colors);
}

//  0x5A7260
void COctTreeBase::Init(int32_t numBranches) {
    ms_level = 0;

    this->numBranches = numBranches;
    hasTransparentPixels = 0;

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
            numBranches += (*gpTmpOctTree)->NoOfChildren() - 1;

            (*gpTmpOctTree)->lastStep = 1;
            (*gpTmpOctTree)->RemoveChildren();

            if (ms_bFailed)
                continue;
        }

        return false;
    }

    if (numBranches <= 0) {
        gpTmpOctTree = nullptr;
        ReduceTree();
        numBranches += (*gpTmpOctTree)->NoOfChildren() - 1;

        (*gpTmpOctTree)->lastStep = 1;
        (*gpTmpOctTree)->RemoveChildren();
    }

    return true;
}

//  0x5A7840
void COctTreeBase::ReduceBranches(int32_t newBranchesCount) {
    const int32_t branchesToCount = hasTransparentPixels ? newBranchesCount + 1 : newBranchesCount;

    while (numBranches < branchesToCount) {
        gpTmpOctTree = nullptr;
        ReduceTree();
        numBranches += (*gpTmpOctTree)->NoOfChildren() - 1;

        (*gpTmpOctTree)->lastStep = 1;
        (*gpTmpOctTree)->RemoveChildren();
    }
}

void COctTreeBase::InjectHooks() {
    //  Virtual class methods
    ReversibleHooks::Install("COctTreeBase", "InsertTree", 0x5A7710, &COctTreeBase::InsertTree);
    ReversibleHooks::Install("COctTreeBase", "FillPalette", 0x5A7280, &COctTreeBase::FillPalette);

    //  Class methods
    ReversibleHooks::Install("COctTreeBase", "Init", 0x5A7260, &COctTreeBase::Init);
    ReversibleHooks::Install("COctTreeBase", "Insert", 0x5A7750, &COctTreeBase::Insert);
    ReversibleHooks::Install("COctTreeBase", "ReduceBranches", 0x5A7840, &COctTreeBase::ReduceBranches);
}
