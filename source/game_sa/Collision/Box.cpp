#include "StdInc.h"

#include "Box.h"

void CBox::InjectHooks()
{
    RH_ScopedClass(CBox);
    RH_ScopedCategory("Collision");

    RH_ScopedInstall(Set, 0x40EDE0);
    RH_ScopedInstall(Recalc, 0x40EE20);
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
