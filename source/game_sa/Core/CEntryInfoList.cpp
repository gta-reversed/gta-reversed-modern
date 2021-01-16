#include "StdInc.h"

void CEntryInfoList::InjectHooks()
{
    ReversibleHooks::Install("CEntryInfoList", "Flush", 0x536E10, &CEntryInfoList::Flush);
}

void CEntryInfoList::Flush()
{
    CEntryInfoNode* pCurNode = m_pNode;
    while (pCurNode) {
        auto pNextNode = pCurNode->m_pNext;
        CEntryInfoList::DeleteNode(pCurNode);
        pCurNode = pNextNode;
    }
}

void CEntryInfoList::DeleteNode(CEntryInfoNode* pNode)
{
    if(m_pNode == pNode)
        m_pNode = pNode->m_pNext;

    if (pNode->m_pPrevious)
        pNode->m_pPrevious->m_pNext = pNode->m_pNext;

    if (pNode->m_pNext)
        pNode->m_pNext->m_pPrevious = pNode->m_pPrevious;

    delete pNode;
}
