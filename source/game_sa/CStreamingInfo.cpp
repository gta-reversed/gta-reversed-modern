#include "StdInc.h"

CStreamingInfo *&CStreamingInfo::ms_pArrayBase = *reinterpret_cast<CStreamingInfo **>(0x9654B4);

void CStreamingInfo::InjectHooks()
{
    ReversibleHooks::Install("CStreamingInfo", "Init", 0x407460, &CStreamingInfo::Init);
    ReversibleHooks::Install("CStreamingInfo", "AddToList", 0x407480, &CStreamingInfo::AddToList);
}

void CStreamingInfo::Init()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x407460, CStreamingInfo*>(this);
#else
    m_nLoadState = LOADSTATE_NOT_LOADED;
    m_nNextIndex = -1;
    m_nPrevIndex = -1;
    m_nNextIndexOnCd = -1;
    m_nImgId = 0;
    m_nCdSize = 0;
    m_nCdPosn = 0;
#endif
}

void CStreamingInfo::AddToList(CStreamingInfo* listStart) 
{
    m_nNextIndex = listStart->m_nNextIndex;
    m_nPrevIndex = static_cast<ptrdiff_t>(listStart - ms_pArrayBase);
    listStart->m_nNextIndex = static_cast<ptrdiff_t>(this - ms_pArrayBase);
    ms_pArrayBase[m_nNextIndex].m_nPrevIndex = listStart->m_nNextIndex;
}

unsigned int CStreamingInfo::GetCdPosn() { return m_nCdPosn + CStreaming::ms_files[m_nImgId].m_StreamHandle; }

void CStreamingInfo::SetCdPosnAndSize(unsigned int CdPosn, unsigned int CdSize)
{
    m_nCdPosn = CdPosn;
    m_nCdSize = CdSize;
}

bool CStreamingInfo::GetCdPosnAndSize(unsigned int* CdPosn, unsigned int* CdSize)
{
    return plugin::CallMethodAndReturn<bool, 0x4075A0, CStreamingInfo*, unsigned int*, unsigned int*>(this, CdPosn, CdSize);
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
