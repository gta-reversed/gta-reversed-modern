#include "StdInc.h"

#include "ColLine.h"

void CColLine::InjectHooks() {
    RH_ScopedInstall(Set, 0x40EF10);
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
