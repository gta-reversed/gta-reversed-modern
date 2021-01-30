#include "StdInc.h"

void CColLine::InjectHooks() {
    ReversibleHooks::Install("CColLine", "Set", 0x40EF10, &CColLine::Set);
}

CColLine::CColLine(CVector const& start, CVector const& end)
{
    m_vecStart = start;
    m_vecEnd = end;
}

void CColLine::Set(CVector const& start, CVector const& end)
{
    m_vecStart = start;
    m_vecEnd = end;
}
