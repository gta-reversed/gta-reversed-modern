#include "StdInc.h"

void CColLine::InjectHooks() {
    HookInstall(0x40EF10, &CColLine::Set);
}

CColLine::CColLine(CVector const& start, CVector const& end)
{
    m_vecStart = start;
    m_vecEnd = end;
}

void CColLine::Set(CVector const& start, CVector const& end)
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void (__thiscall*)(CColLine*, CVector const&, CVector const&))0x40EF10)(this, start, end);
#else
    m_vecStart = start;
    m_vecEnd = end;
#endif
}
