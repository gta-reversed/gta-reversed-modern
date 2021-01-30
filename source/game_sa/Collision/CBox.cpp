#include "StdInc.h"

void CBox::InjectHooks()
{
    ReversibleHooks::Install("CBox", "Set", 0x40EDE0, &CBox::Set);
    ReversibleHooks::Install("CBox", "Recalc", 0x40EE20, &CBox::Recalc);
}

void CBox::Set(CVector const& vecMin, CVector const& vecMax)
{
    m_vecMin = vecMin;
    m_vecMax = vecMax;
}

void CBox::Recalc()
{
    if (m_vecMin.x > m_vecMax.x)
        std::swap(m_vecMin.x, m_vecMax.x);

    if (m_vecMin.y > m_vecMax.y)
        std::swap(m_vecMin.y, m_vecMax.y);

    if (m_vecMin.z > m_vecMax.z)
        std::swap(m_vecMin.z, m_vecMax.z);
}
