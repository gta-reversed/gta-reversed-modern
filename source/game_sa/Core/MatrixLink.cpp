#include "StdInc.h"

void CMatrixLink::InjectHooks()
{
    ReversibleHooks::Install("CMatrixLink", "Insert", 0x54E8F0, &CMatrixLink::Insert);
    ReversibleHooks::Install("CMatrixLink", "Remove", 0x54E910, &CMatrixLink::Remove);
}

void CMatrixLink::Insert(CMatrixLink* pWhere)
{
    pWhere->m_pNext = m_pNext;
    m_pNext->m_pPrev = pWhere;

    pWhere->m_pPrev = this;
    m_pNext = pWhere;
}

void CMatrixLink::Remove()
{
    m_pNext->m_pPrev = m_pPrev;
    m_pPrev->m_pNext = m_pNext;
}
