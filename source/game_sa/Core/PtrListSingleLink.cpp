#include "StdInc.h"

#include "PtrListSingleLink.h"

void CPtrListSingleLink::InjectHooks() {
    RH_ScopedClass(CPtrListSingleLink);
    RH_ScopedCategory("Core");

    RH_ScopedInstall(Flush, 0x552400);
    RH_ScopedInstall(AddItem, 0x5335E0);
    RH_ScopedInstall(DeleteItem, 0x533610);
}

void CPtrListSingleLink::Flush() {
    if (!m_node)
        return;

    // Simplified the logic a lot, same end result
    CPtrNodeSingleLink* curNode;
    while ((curNode = GetNode()))
        CPtrListSingleLink::DeleteNode(curNode, GetNode());
}

CPtrNodeSingleLink* CPtrListSingleLink::AddItem(void* item) {
    auto pNewSingleLink = new CPtrNodeSingleLink(item);
    pNewSingleLink->AddToList(this);
    return pNewSingleLink;
}

void CPtrListSingleLink::DeleteItem(void* item) {
    if (!m_node)
        return;

    auto* curNode = GetNode();
    CPtrNodeSingleLink* lastNode = nullptr;
    while (curNode->m_item != item) {
        lastNode = curNode;
        curNode = reinterpret_cast<CPtrNodeSingleLink*>(curNode->m_next);
        if (!curNode)
            return;
    }

    CPtrListSingleLink::DeleteNode(curNode, lastNode);
}

void CPtrListSingleLink::DeleteNode(CPtrNodeSingleLink* node, CPtrNodeSingleLink* lastNode) {
    if (GetNode() == node)
        m_node = reinterpret_cast<CPtrNode*>(node->m_next);
    else if (lastNode)
        lastNode->m_next = node->m_next;

    delete node;
}
