#include "StdInc.h"
#include "ColTriangle.h"
#include "Lines.h"

// NOTSA
void CColTriangle::DrawWireFrame(CRGBA color, const CompressedVector* vertices, const CMatrix& transform) const {
    const CVector vA = transform * UncompressVector(vertices[m_nVertA]);
    const CVector vB = transform * UncompressVector(vertices[m_nVertB]);
    const CVector vC = transform * UncompressVector(vertices[m_nVertC]);

    const auto colorARGB = color.ToInt();
    CLines::RenderLineNoClipping(vA, vB, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(vA, vC, colorARGB, colorARGB);
    CLines::RenderLineNoClipping(vB, vC, colorARGB, colorARGB);
}
