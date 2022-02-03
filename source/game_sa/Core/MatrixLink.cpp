#include "StdInc.h"

#include "MatrixLink.h"

void CMatrixLink::InjectHooks()
{
    RH_ScopedClass(CMatrixLink);
    RH_ScopedCategory("Core");

    RH_ScopedInstall(Insert, 0x54E8F0);
    RH_ScopedInstall(Remove, 0x54E910);
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
