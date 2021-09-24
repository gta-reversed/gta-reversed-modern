#include "StdInc.h"

void CPtrListSingleLink::InjectHooks()
{
    ReversibleHooks::Install("CPtrListSingleLink", "Flush", 0x552400, &CPtrListSingleLink::Flush);
    ReversibleHooks::Install("CPtrListSingleLink", "AddItem", 0x5335E0, &CPtrListSingleLink::AddItem);
    ReversibleHooks::Install("CPtrListSingleLink", "DeleteItem", 0x533610, &CPtrListSingleLink::DeleteItem);
}

void CPtrListSingleLink::Flush()
{
    if (!pNode)
        return;

    // Simplified the logic a lot, same end result
    CPtrNodeSingleLink* pCurNode;
    while ((pCurNode = GetNode()))
        CPtrListSingleLink::DeleteNode(pCurNode, GetNode());
}

CPtrNodeSingleLink* CPtrListSingleLink::AddItem(void* item)
{
    auto pNewSingleLink = new CPtrNodeSingleLink(item);
    pNewSingleLink->AddToList(this);
    return pNewSingleLink;
}

void CPtrListSingleLink::DeleteItem(void* item)
{
    if (!pNode)
        return;

    auto* pCurNode = GetNode();
    CPtrNodeSingleLink* pLastNode = nullptr;
    while (pCurNode->pItem != item) {
        pLastNode = pCurNode;
        pCurNode = reinterpret_cast<CPtrNodeSingleLink*>(pCurNode->pNext);
        if (!pCurNode)
            return;
    }

    CPtrListSingleLink::DeleteNode(pCurNode, pLastNode);
}

void CPtrListSingleLink::DeleteNode(CPtrNodeSingleLink* node, CPtrNodeSingleLink* lastNode)
{
    if (GetNode() == node)
        pNode = reinterpret_cast<CPtrNode*>(node->pNext);
    else if (lastNode)
        lastNode->pNext = node->pNext;

    delete node;
}
