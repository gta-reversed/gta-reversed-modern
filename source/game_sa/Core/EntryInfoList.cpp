#include "StdInc.h"

void CEntryInfoList::InjectHooks()
{
    ReversibleHooks::Install("CEntryInfoList", "Flush", 0x536E10, &CEntryInfoList::Flush);
}

void CEntryInfoList::Flush()
{
    CEntryInfoNode* curNode = m_node;
    while (curNode) {
        auto nextNode = curNode->m_next;
        CEntryInfoList::DeleteNode(curNode);
        curNode = nextNode;
    }
}

// 0x?
void CEntryInfoList::DeleteNode(CEntryInfoNode* node)
{
    if(m_node == node)
        m_node = node->m_next;

    if (node->m_previous)
        node->m_previous->m_next = node->m_next;

    if (node->m_next)
        node->m_next->m_previous = node->m_previous;

    delete node;
}
