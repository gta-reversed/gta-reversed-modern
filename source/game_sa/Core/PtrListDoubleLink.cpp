#include "StdInc.h"

void CPtrListDoubleLink::InjectHooks()
{
    ReversibleHooks::Install("CPtrListDoubleLink", "Flush", 0x552470, &CPtrListDoubleLink::Flush);
    ReversibleHooks::Install("CPtrListDoubleLink", "AddItem", 0x533670, &CPtrListDoubleLink::AddItem);
    ReversibleHooks::Install("CPtrListDoubleLink", "DeleteItem", 0x5336B0, &CPtrListDoubleLink::DeleteItem);
}

void CPtrListDoubleLink::Flush()
{
    if (!pNode)
        return;

    CPtrNodeDoubleLink* pCurNode;
    while ((pCurNode = GetNode()))
        CPtrListDoubleLink::DeleteNode(pCurNode);
}

CPtrNodeDoubleLink* CPtrListDoubleLink::AddItem(void* item)
{
    auto pNewDoubleLink = new CPtrNodeDoubleLink(item);
    pNewDoubleLink->AddToList(this);
    return pNewDoubleLink;

}

void CPtrListDoubleLink::DeleteItem(void* item)
{
    if (!pNode)
        return;

    auto* pCurNode = GetNode();
    while (pCurNode->pItem != item) {
        pCurNode = reinterpret_cast<CPtrNodeDoubleLink*>(pCurNode->pNext);
        if (!pCurNode)
            return;
    }

    CPtrListDoubleLink::DeleteNode(pCurNode);
}

void CPtrListDoubleLink::DeleteNode(CPtrNodeDoubleLink* node)
{
    if (GetNode() == node)
        pNode = pNode->pNext;

    if (node->pPrev)
        node->pPrev->pNext = node->pNext;

    if (node->pNext)
        node->pNext->pPrev = node->pPrev;

    delete node;
}
