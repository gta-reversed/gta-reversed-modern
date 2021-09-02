/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CRect.h"
#include "CPtrListSingleLink.h"
#include "CPool.h"

/*
node level 2
 +----------------------+--
 | node level 1         +
 |  +--------+--------+ +
 |  |node    |node    | +
 |  |level 0 |level 0 | +
 |  |index 0 |index 1 | +
 |  +--------+--------+ +
 |  |node    |node    | +
 |  |level 0 |level 0 | +
 |  |index 2 |index 3 | +
 |  +--------+--------+ +
 +----------------------+--
 |                      |

 Total rectangles = 4^startLevel
*/

typedef void(*CQuadTreeNodeRectCallBack) (CRect const& rect, void* item);
typedef void(*CQuadTreeNodeVec2DCallBack) (CVector2D const& rect, void* item);

class CQuadTreeNode {
public:
    CRect              m_Rect;
    CPtrListSingleLink m_ItemList;
    CQuadTreeNode*     m_apChildren[4];
    uint32             m_nLevel; // 0 - last level

    static CPool<CQuadTreeNode> *&ms_pQuadTreeNodePool;

    CQuadTreeNode(CRect const& size, int32 startLevel);
    ~CQuadTreeNode();

    static void operator delete(void* data);
    static void* operator new(uint32 size);

public:
    static void InjectHooks();
    static void InitPool();

    void AddItem(void* item, CRect const& rect);
    void DeleteItem(void* item);
    void DeleteItem(void* item, CRect const& rect);
    int32 FindSector(CRect const& rect); // -1 if not found
    int32 FindSector(CVector2D const& posn); // -1 if not found
    void ForAllMatching(CRect const& rect, CQuadTreeNodeRectCallBack callback);
    void ForAllMatching(CVector2D const& posn, CQuadTreeNodeVec2DCallBack callback);
    void GetAll(CPtrListSingleLink& list);
    void GetAllMatching(CRect const& rect, CPtrListSingleLink& list);
    void GetAllMatching(CVector2D const& posn, CPtrListSingleLink& list);
    bool InSector(CRect const& rect, int32 sector) const;

// Helpers
public:
    CRect GetSectorRect(int32 sector) const;
    bool LiesInside(CRect const& rect) const;
};

VALIDATE_SIZE(CQuadTreeNode, 0x28);
