#include "StdInc.h"

#include "Lines.h"

void CBox::InjectHooks()
{
    RH_ScopedClass(CBox);
    RH_ScopedCategory("Collision");

    RH_ScopedInstall(Set, 0x40EDE0);
    RH_ScopedInstall(Recalc, 0x40EE20);
}

void CBox::Set(const CVector& vecMin, const CVector& vecMax)
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

// NOTSA - TODO(OPT): Refactor code (meaningful names, etc) and possibly use std::optional for `CMatrix` (In cases where a unity matrix would be used otherwise)
void CBox::Draw(const CMatrix& transform, CRGBA color) const {
    auto workVec = m_vecMin;
    CVector v1 = transform * workVec;

    workVec.z = m_vecMax.z;
    CVector v2 = transform * workVec;

    workVec = m_vecMin;
    workVec.x = m_vecMax.x;
    CVector v3 = transform * workVec;

    workVec = m_vecMin;
    workVec.y = m_vecMax.y;
    CVector v4 = transform * workVec;

    workVec = m_vecMin;
    workVec.y = m_vecMax.y;
    workVec.z = m_vecMax.z;
    CVector v5 = transform * workVec;

    workVec = m_vecMin;
    workVec.x = m_vecMax.x;
    workVec.z = m_vecMax.z;
    CVector v6 = transform * workVec;

    workVec = m_vecMin;
    workVec.x = m_vecMax.x;
    workVec.y = m_vecMax.y;
    CVector v7 = transform * workVec;

    workVec = m_vecMax;
    CVector v8 = transform * workVec;

    const auto colorARGB = color.ToIntARGB();
    CLines::RenderLineWithClipping(v1, v2, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v1, v3, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v1, v4, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v5, v2, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v5, v8, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v5, v4, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v6, v2, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v6, v8, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v6, v3, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v7, v8, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v7, v3, colorARGB, colorARGB);
    CLines::RenderLineWithClipping(v7, v4, colorARGB, colorARGB);
}
