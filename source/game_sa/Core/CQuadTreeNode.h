/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
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
 |  |        |        | +
 |  +--------+--------+ +
 |  |node    |node    | +
 |  |level 0 |level 0 | +
 |  |        |        | +
 |  +--------+--------+ +
 +----------------------+--
 |                      |

 Total rectangles = 4^startLevel
*/

class  CQuadTreeNode {
public:
    CRect               rect;
    CPtrListSingleLink  itemList;
    CQuadTreeNode      *childrens[4];
    unsigned int        level; // 0 - last level

    static CPool<CQuadTreeNode> *&ms_pQuadTreeNodePool;

    CQuadTreeNode(CRect const& rect, int startLevel);
    ~CQuadTreeNode();

    void AddItem(void* item, CRect const& rect);
    void DeleteItem(void* item);
    void DeleteItem(void* item, CRect const& rect);
    int FindSector(CRect const& rect); // -1 if not found
    int FindSector(CVector2D const& posn); // -1 if not found
    void ForAllMatching(CRect const& rect, void(*callback)(CRect const&, void *));
    void ForAllMatching(CVector2D const& posn, void(*callback)(CVector2D const&, void *));
    void GetAll(CPtrListSingleLink& list);
    void GetAllMatching(CRect const& rect, CPtrListSingleLink& list);
    void GetAllMatching(CVector2D const& posn, CPtrListSingleLink& list);
    bool InSector(CRect const& rect, int sector);
    void InitPool();
    static void operator delete(void* data);
    static void* operator new(unsigned int size);

};

VALIDATE_SIZE(CQuadTreeNode, 0x28);