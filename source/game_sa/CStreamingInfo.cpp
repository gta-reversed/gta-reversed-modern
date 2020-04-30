#include "StdInc.h"

CStreamingInfo *&CStreamingInfo::ms_pArrayBase = *reinterpret_cast<CStreamingInfo **>(0x9654B4);

void CStreamingInfo::InjectHooks()
{
}

inline int CStreamingInfo::GetIndexFromBase(CStreamingInfo * pThis, CStreamingInfo * ArrayBase)
{
    unsigned __int64 indexToCalculate = (1717986919i64 * (reinterpret_cast<DWORD>(pThis) - reinterpret_cast<DWORD>(ArrayBase))) >> 32;
    return static_cast < int > ((indexToCalculate >> 3) + (indexToCalculate >> 31));
}

int CStreamingInfo::AddToList(CStreamingInfo *listStart) 
{
//#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturnDynGlobal<int,CStreamingInfo *, CStreamingInfo *>(0x407480, this, listStart);
#if 0
    m_nNextIndex = listStart->m_nNextIndex;
    m_nPrevIndex = GetIndexFromBase (listStart, ms_pArrayBase);
    listStart->m_nNextIndex = static_cast<short>((reinterpret_cast<DWORD>(this) - reinterpret_cast<DWORD>(ms_pArrayBase)) / 20);
    ms_pArrayBase[m_nNextIndex].m_nPrevIndex = listStart->m_nNextIndex;
    return m_nNextIndex;
#endif
}

unsigned int CStreamingInfo::GetCdPosn() { return m_nCdPosn + CStreaming::ms_files[m_nImgId].m_StreamHandle; }

bool CStreamingInfo::GetCdPosnAndSize(unsigned int* CdPosn, unsigned int* CdSize)
{
    return plugin::CallMethodAndReturn<bool, 0x1560E50, CStreamingInfo*, unsigned int*, unsigned int*>(this, CdPosn, CdSize);
}

bool CStreamingInfo::InList()
{
    return m_nNextIndex != -1;
}

void CStreamingInfo::RemoveFromList()
{
    ms_pArrayBase[m_nNextIndex].m_nPrevIndex = m_nPrevIndex;
    ms_pArrayBase[m_nPrevIndex].m_nNextIndex = m_nNextIndex;
    m_nNextIndex = -1;
    m_nPrevIndex = -1;
}