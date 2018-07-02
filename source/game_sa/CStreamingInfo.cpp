#include "StdInc.h"

CStreamingInfo *&CStreamingInfo::ms_pArrayBase = *reinterpret_cast<CStreamingInfo **>(0x9654B4);


template < class T >
int GET_INDEX_FROM_BASE(T pThis, T ArrayBase)
{
    unsigned __int64 indexToCalculate = (1717986919i64 * (reinterpret_cast<signed int>(pThis) - reinterpret_cast<signed int>(ArrayBase))) >> 32;
    return static_cast < int > ((indexToCalculate >> 3) + (indexToCalculate >> 31));
}

int CStreamingInfo::AddToList(CStreamingInfo *listStart) {
    m_nNextIndex = listStart->m_nNextIndex;
    m_nPrevIndex = GET_INDEX_FROM_BASE < CStreamingInfo * >(listStart, CStreamingInfo::ms_pArrayBase);
    listStart->m_nNextIndex = GET_INDEX_FROM_BASE < CStreamingInfo * >(this, CStreamingInfo::ms_pArrayBase);
    CStreamingInfo::ms_pArrayBase[m_nNextIndex].m_nPrevIndex = listStart->m_nNextIndex;
    return m_nNextIndex;
}

bool CStreamingInfo::InList()
{
    return m_nNextIndex != -1;
}

void CStreamingInfo::RemoveFromList()
{
    CStreamingInfo::ms_pArrayBase[m_nNextIndex].m_nPrevIndex = m_nPrevIndex;
    CStreamingInfo::ms_pArrayBase[m_nPrevIndex].m_nNextIndex = m_nNextIndex;
    m_nNextIndex = -1;
    m_nPrevIndex = -1;
}