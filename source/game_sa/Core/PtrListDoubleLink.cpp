#include "StdInc.h"

#include "PtrListDoubleLink.h"

void CPtrListDoubleLink::InjectHooks() {
    ReversibleHooks::Install("CPtrListDoubleLink", "Flush", 0x552470, &CPtrListDoubleLink::Flush);
    ReversibleHooks::Install("CPtrListDoubleLink", "AddItem", 0x533670, &CPtrListDoubleLink::AddItem);
    ReversibleHooks::Install("CPtrListDoubleLink", "DeleteItem", 0x5336B0, &CPtrListDoubleLink::DeleteItem);
}

void CPtrListDoubleLink::Flush() {
    if (!m_node)
        return;

    CPtrNodeDoubleLink* pCurNode;
    while ((pCurNode = GetNode()))
        CPtrListDoubleLink::DeleteNode(pCurNode);
}

CPtrNodeDoubleLink* CPtrListDoubleLink::AddItem(void* item) {
    auto pNewDoubleLink = new CPtrNodeDoubleLink(item);
    pNewDoubleLink->AddToList(this);
    return pNewDoubleLink;
}

void CPtrListDoubleLink::DeleteItem(void* item) {
    if (!m_node)
        return;

    auto* pCurNode = GetNode();
    while (pCurNode->m_item != item) {
        pCurNode = reinterpret_cast<CPtrNodeDoubleLink*>(pCurNode->m_next);
        if (!pCurNode)
            return;
    }

    CPtrListDoubleLink::DeleteNode(pCurNode);
}

void CPtrListDoubleLink::DeleteNode(CPtrNodeDoubleLink* node) {
    if (GetNode() == node)
        m_node = m_node->m_next;

    if (node->m_prev)
        node->m_prev->m_next = node->m_next;

    if (node->m_next)
        node->m_next->m_prev = node->m_prev;

    delete node;
}
