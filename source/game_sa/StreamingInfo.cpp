#include "StdInc.h"

CStreamingInfo*& CStreamingInfo::ms_pArrayBase = *reinterpret_cast<CStreamingInfo**>(0x9654B4);

void CStreamingInfo::InjectHooks() {
    ReversibleHooks::Install("CStreamingInfo", "Init", 0x407460, &CStreamingInfo::Init);
    ReversibleHooks::Install("CStreamingInfo", "AddToList", 0x407480, &CStreamingInfo::AddToList);
    ReversibleHooks::Install("CStreamingInfo", "GetCdPosn", 0x407570, &CStreamingInfo::GetCdPosn);
    ReversibleHooks::Install("CStreamingInfo", "SetCdPosnAndSize", 0x4075E0, &CStreamingInfo::SetCdPosnAndSize);
    ReversibleHooks::Install("CStreamingInfo", "GetCdPosnAndSize", 0x4075A0, &CStreamingInfo::GetCdPosnAndSize);
    ReversibleHooks::Install("CStreamingInfo", "InList", 0x407560, &CStreamingInfo::InList);
    ReversibleHooks::Install("CStreamingInfo", "RemoveFromList", 0x4074E0, &CStreamingInfo::RemoveFromList);
}

// 0x407460
void CStreamingInfo::Init() {
    m_nLoadState = LOADSTATE_NOT_LOADED;
    m_nNextIndex = -1;
    m_nPrevIndex = -1;
    m_nNextIndexOnCd = -1;
    m_nImgId = 0;
    m_nCdSize = 0;
    m_nCdPosn = 0;
}

// 0x407480
void CStreamingInfo::AddToList(CStreamingInfo* listStart) {
    m_nNextIndex = listStart->m_nNextIndex;
    m_nPrevIndex = static_cast<ptrdiff_t>(listStart - ms_pArrayBase);
    listStart->m_nNextIndex = static_cast<ptrdiff_t>(this - ms_pArrayBase);
    ms_pArrayBase[m_nNextIndex].m_nPrevIndex = listStart->m_nNextIndex;
}

// 0x407570
uint32 CStreamingInfo::GetCdPosn() {
    return m_nCdPosn + CStreaming::ms_files[m_nImgId].m_StreamHandle;
}

// 0x4075E0
void CStreamingInfo::SetCdPosnAndSize(uint32 CdPosn, uint32 CdSize) {
    m_nCdPosn = CdPosn;
    m_nCdSize = CdSize;
}

// 0x4075A0
bool CStreamingInfo::GetCdPosnAndSize(uint32& CdPosn, uint32& CdSize) {
    if (!m_nCdSize)
        return false;
    CdPosn = GetCdPosn();
    CdSize = m_nCdSize;
    return true;
}

// 0x407560
bool CStreamingInfo::InList() {
    return m_nNextIndex != -1;
}

// 0x4074E0
void CStreamingInfo::RemoveFromList() {
    ms_pArrayBase[m_nNextIndex].m_nPrevIndex = m_nPrevIndex;
    ms_pArrayBase[m_nPrevIndex].m_nNextIndex = m_nNextIndex;
    m_nNextIndex = -1;
    m_nPrevIndex = -1;
}
