#include "StdInc.h"

CPool<CQuadTreeNode>*& CQuadTreeNode::ms_pQuadTreeNodePool = *(CPool<CQuadTreeNode>**)0xB745BC;

void CQuadTreeNode::InjectHooks()
{
    ReversibleHooks::Install("CQuadTreeNode", "InitPool", 0x552C00, &CQuadTreeNode::InitPool);
    ReversibleHooks::Install("CQuadTreeNode", "FindSector_rect", 0x5525A0, (int32(CQuadTreeNode::*)(CRect const&))&CQuadTreeNode::FindSector);
    ReversibleHooks::Install("CQuadTreeNode", "FindSector_vec", 0x552640, (int32(CQuadTreeNode::*)(CVector2D const&)) & CQuadTreeNode::FindSector);
    ReversibleHooks::Install("CQuadTreeNode", "InSector", 0x5526A0, &CQuadTreeNode::InSector);
    ReversibleHooks::Install("CQuadTreeNode", "DeleteItem", 0x552A40, (void(CQuadTreeNode::*)(void*))&CQuadTreeNode::DeleteItem);
    ReversibleHooks::Install("CQuadTreeNode", "DeleteItem_rect", 0x552A90, (void(CQuadTreeNode::*)(void*, CRect const&))&CQuadTreeNode::DeleteItem);
    ReversibleHooks::Install("CQuadTreeNode", "AddItem", 0x552CD0, &CQuadTreeNode::AddItem);
    ReversibleHooks::Install("CQuadTreeNode", "GetAll", 0x552870, &CQuadTreeNode::GetAll);
    ReversibleHooks::Install("CQuadTreeNode", "GetAllMatching_rect", 0x5528C0, (void(CQuadTreeNode::*)(CRect const&, CPtrListSingleLink&))&CQuadTreeNode::GetAllMatching);
    ReversibleHooks::Install("CQuadTreeNode", "GetAllMatching_vec", 0x552930, (void(CQuadTreeNode::*)(CVector2D const&, CPtrListSingleLink&))&CQuadTreeNode::GetAllMatching);
    ReversibleHooks::Install("CQuadTreeNode", "ForAllMatching_rect", 0x552980, (void(CQuadTreeNode::*)(CRect const&, CQuadTreeNodeRectCallBack))&CQuadTreeNode::ForAllMatching);
    ReversibleHooks::Install("CQuadTreeNode", "ForAllMatching_vec", 0x5529F0, (void(CQuadTreeNode::*)(CVector2D const&, CQuadTreeNodeVec2DCallBack))&CQuadTreeNode::ForAllMatching);
}

CQuadTreeNode::CQuadTreeNode(CRect const& size, int32 startLevel) : m_ItemList(), m_apChildren{ nullptr }
{
    m_Rect = size;
    m_nLevel = startLevel;
}

CQuadTreeNode::~CQuadTreeNode()
{
    for (auto& child : m_apChildren)
        delete child;

    m_ItemList.Flush();
}

void CQuadTreeNode::AddItem(void* item, CRect const& rect)
{
    if (!m_nLevel)
    {
        m_ItemList.AddItem(item);
        return;
    }

    for (auto sector = 0; sector < 4; ++sector)
    {
        if (!CQuadTreeNode::InSector(rect, sector))
            continue;

        if (!m_apChildren[sector])
        {
            const CRect sectorRect = CQuadTreeNode::GetSectorRect(sector);
            m_apChildren[sector] = new CQuadTreeNode(sectorRect, m_nLevel - 1);
        }

        m_apChildren[sector]->AddItem(item, rect);
    }
}

void CQuadTreeNode::DeleteItem(void* item)
{
    m_ItemList.DeleteItem(item);

    for (auto sector = 0; sector < 4; ++sector)
        if (m_apChildren[sector])
            m_apChildren[sector]->DeleteItem(item);
}

void CQuadTreeNode::DeleteItem(void* item, CRect const& rect)
{
    m_ItemList.DeleteItem(item);

    for (auto sector = 0; sector < 4; ++sector)
        if (m_apChildren[sector] && CQuadTreeNode::InSector(rect, sector))
            m_apChildren[sector]->DeleteItem(item);
}

int32 CQuadTreeNode::FindSector(CRect const& rect)
{
    const auto center = m_Rect.GetCenter();
    if (!m_nLevel)
        return -1;

    // This stuff for sure can be simplified, but my attempts break the logic
    if (center.y > rect.bottom)
    {
        if (center.x > rect.right)
            return 2;
        if (center.x >= rect.left)
            return -1;
        return 3;
    }
    if (center.y >= rect.top)
        return -1;
    if (center.x > rect.right)
        return 0;
    if (center.x >= rect.left)
        return -1;
    return 1;
}

int32 CQuadTreeNode::FindSector(CVector2D const& posn)
{
    const auto center = m_Rect.GetCenter();
    if (!m_nLevel)
        return -1;

    // This stuff for sure can be simplified, but my attempts break the logic
    const bool bLeftHalf = center.x > posn.x;
    if (bLeftHalf)
    {
        if (center.y <= posn.y)
            return 0;
        else
            return 2;
    }
    else if (center.y <= posn.y)
        return 1;
    else
        return 3;
}

void CQuadTreeNode::ForAllMatching(CRect const& rect, CQuadTreeNodeRectCallBack callback)
{
    for (auto* node = m_ItemList.GetNode(); node; node = node->pNext)
        callback(rect, node->pItem);

    for (auto sector = 0; sector < 4; ++sector)
        if (m_apChildren[sector] && CQuadTreeNode::InSector(rect, sector))
            m_apChildren[sector]->ForAllMatching(rect, callback);
}

void CQuadTreeNode::ForAllMatching(CVector2D const& posn, CQuadTreeNodeVec2DCallBack callback)
{
    for (auto* node = m_ItemList.GetNode(); node; node = node->pNext)
        callback(posn, node->pItem);

    const auto sector = CQuadTreeNode::FindSector(posn);
    if (sector == -1 || !m_apChildren[sector])
        return;

    m_apChildren[sector]->ForAllMatching(posn, callback);
}

void CQuadTreeNode::GetAll(CPtrListSingleLink& list)
{
    for (auto* node = m_ItemList.GetNode(); node; node = node->pNext)
        list.AddItem(node->pItem);

    for (auto sector = 0; sector < 4; ++sector)
        if (m_apChildren[sector])
            m_apChildren[sector]->GetAll(list);
}

void CQuadTreeNode::GetAllMatching(CRect const& rect, CPtrListSingleLink& list)
{
    for (auto* node = m_ItemList.GetNode(); node; node = node->pNext)
        list.AddItem(node->pItem);

    for (auto sector = 0; sector < 4; ++sector)
        if (m_apChildren[sector] && CQuadTreeNode::InSector(rect, sector))
            m_apChildren[sector]->GetAllMatching(rect, list);
}

void CQuadTreeNode::GetAllMatching(CVector2D const& posn, CPtrListSingleLink& list)
{
    for (auto* node = m_ItemList.GetNode(); node; node = node->pNext)
        list.AddItem(node->pItem);

    const auto sector = CQuadTreeNode::FindSector(posn);
    if (sector == -1 || !m_apChildren[sector])
        return;

    m_apChildren[sector]->GetAllMatching(posn, list);
}

bool CQuadTreeNode::InSector(CRect const& rect, int32 sector) const
{
    if (!m_nLevel)
        return false;

    const CRect sectorRect = CQuadTreeNode::GetSectorRect(sector);

    if (sectorRect.left <= rect.right && sectorRect.right >= rect.left
        && sectorRect.top <= rect.bottom && sectorRect.bottom >= rect.top)
    {
        return true;
    }

    return false;
}

void CQuadTreeNode::InitPool() {
    if (CQuadTreeNode::ms_pQuadTreeNodePool)
        return;

    CQuadTreeNode::ms_pQuadTreeNodePool = new CPool<CQuadTreeNode>(400, "QuadTreeNodes");
}

CRect CQuadTreeNode::GetSectorRect(int32 sector) const
{
    CRect sectorRect = m_Rect;
    const auto center = sectorRect.GetCenter();
    switch (sector)
    {
    case 0:
        sectorRect.right = center.x;
        sectorRect.top = center.y;
        break;
    case 1:
        sectorRect.left = center.x;
        sectorRect.top = center.y;
        break;
    case 2:
        sectorRect.right = center.x;
        sectorRect.bottom = center.y;
        break;
    case 3:
        sectorRect.left = center.x;
        sectorRect.bottom = center.y;
        break;
    default:
        assert(false); //Shouldn't ever get here
    }

    return sectorRect;
}

bool CQuadTreeNode::LiesInside(CRect const& rect) const
{
    return m_Rect.left <= rect.right
        && m_Rect.right >= rect.left
        && m_Rect.top <= rect.bottom
        && m_Rect.bottom >= rect.top;
}

void CQuadTreeNode::operator delete(void* data)
{
    CQuadTreeNode::ms_pQuadTreeNodePool->Delete(static_cast<CQuadTreeNode*>(data));
}

void* CQuadTreeNode::operator new(uint32 size)
{
    return CQuadTreeNode::ms_pQuadTreeNodePool->New();
}
