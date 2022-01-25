#include "StdInc.h"

#include "PtrListDoubleLink.h"

void CPtrListDoubleLink::InjectHooks() {
    Install("CPtrListDoubleLink", "Flush", 0x552470, &CPtrListDoubleLink::Flush);
    Install("CPtrListDoubleLink", "AddItem", 0x533670, &CPtrListDoubleLink::AddItem);
    Install("CPtrListDoubleLink", "DeleteItem", 0x5336B0, &CPtrListDoubleLink::DeleteItem);
}

void CPtrListDoubleLink::Flush() {
    if (!m_node)
        return;

    CPtrNodeDoubleLink* curNode;
    while ((curNode = GetNode()))
        CPtrListDoubleLink::DeleteNode(curNode);
}

CPtrNodeDoubleLink* CPtrListDoubleLink::AddItem(void* item) {
    auto pNewDoubleLink = new CPtrNodeDoubleLink(item);
    pNewDoubleLink->AddToList(this);
    return pNewDoubleLink;
}

void CPtrListDoubleLink::DeleteItem(void* item) {
    if (!m_node)
        return;

    auto* curNode = GetNode();
    while (curNode->m_item != item) {
        curNode = reinterpret_cast<CPtrNodeDoubleLink*>(curNode->m_next);
        if (!curNode)
            return;
    }

    CPtrListDoubleLink::DeleteNode(curNode);
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
