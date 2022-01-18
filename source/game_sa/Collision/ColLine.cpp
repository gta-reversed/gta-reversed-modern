#include "StdInc.h"

#include "ColLine.h"

void CColLine::InjectHooks() {
    ReversibleHooks::Install("CColLine", "Set", 0x40EF10, &CColLine::Set);
}

// 0x40EF50
CColLine::CColLine(const CVector& start, const CVector& end)
{
    m_vecStart = start;
    m_vecEnd = end;
}

// 0x40EF10
void CColLine::Set(const CVector& start, const CVector& end)
{
    m_vecStart = start;
    m_vecEnd = end;
}
