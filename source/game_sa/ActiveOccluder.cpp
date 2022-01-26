#include "StdInc.h"

#include "ActiveOccluder.h"

void CActiveOccluder::InjectHooks()
{
    RH_ScopedInstall(IsPointWithinOcclusionArea, 0x71E580);
    RH_ScopedInstall(IsPointBehindOccluder, 0x71FA40);
}

// 0x71E580
bool CActiveOccluder::IsPointWithinOcclusionArea(float fX, float fY, float fRadius)
{
    if (m_cLinesCount <= 0)
        return true;

    for (auto i = 0; i < m_cLinesCount; ++i) {
        auto& line = m_aLines[i];
        if (!IsPointInsideLine(line.m_vecOrigin.x, line.m_vecOrigin.y, line.m_vecDirection.x, line.m_vecDirection.y, fX, fY, fRadius))
            return false;
    }

    return true;
}

// 0x71FA40
bool CActiveOccluder::IsPointBehindOccluder(CVector vecPos, float fRadius)
{
    if (m_cNumVectors <= 0)
        return true;

    for (auto i = 0; i < m_cNumVectors; ++i) {
        const auto& vecCamPos = TheCamera.GetPosition();

        auto fPosDotVec = DotProduct(vecPos, m_aVectors[i]) - m_afRadiuses[i];
        auto fCamDotVec = DotProduct(vecCamPos, m_aVectors[i]) - m_afRadiuses[i];

        if (fCamDotVec * fPosDotVec >= 0.0F || fabs(fPosDotVec) < fRadius)
            return false;
    }

    return true;
}
