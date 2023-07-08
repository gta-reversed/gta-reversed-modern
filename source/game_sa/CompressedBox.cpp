#include "StdInc.h"
#include "CompressedBox.h"
#include "Lines.h"

void CompressedBox::DrawWireFrame(CRGBA color, const CMatrix& transform) const
{
    auto workVec = UncompressLargeVector(m_vecMin);
    CVector v1 = transform * workVec;

    workVec.z = m_vecMax.z;
    CVector v2 = transform * workVec;

    workVec = UncompressLargeVector(m_vecMin);
    workVec.x = m_vecMax.x;
    CVector v3 = transform * workVec;

    workVec = UncompressLargeVector(m_vecMin);
    workVec.y = m_vecMax.y;
    CVector v4 = transform * workVec;

    workVec = UncompressLargeVector(m_vecMin);
    workVec.y = m_vecMax.y;
    workVec.z = m_vecMax.z;
    CVector v5 = transform * workVec;

    workVec = UncompressLargeVector(m_vecMin);
    workVec.x = m_vecMax.x;
    workVec.z = m_vecMax.z;
    CVector v6 = transform * workVec;

    workVec = UncompressLargeVector(m_vecMin);
    workVec.x = m_vecMax.x;
    workVec.y = m_vecMax.y;
    CVector v7 = transform * workVec;

    workVec = UncompressLargeVector(m_vecMin);
    CVector v8 = transform * workVec;

    const auto colorARGB = color.ToInt();
    CLines::RenderLineNoClipping(v1, v2, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v1, v3, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v1, v4, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v5, v2, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v5, v8, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v5, v4, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v6, v2, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v6, v8, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v6, v3, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v7, v8, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v7, v3, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(v7, v4, colorARGB, colorARGB);
}
