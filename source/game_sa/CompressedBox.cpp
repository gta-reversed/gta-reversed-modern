#include "StdInc.h"
#include "CompressedBox.h"
#include "Lines.h"

void CompressedBox::DrawWireFrame(CRGBA color, const CMatrix& transform) const
{
    CBox{UncompressLargeVector(m_vecMin), UncompressLargeVector(m_vecMax)}.DrawWireframe(color, transform);
}
