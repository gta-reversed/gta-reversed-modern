#include "StdInc.h"

CStreamingInfo*& CStreamingInfo::ms_pArrayBase = *reinterpret_cast<CStreamingInfo**>(0x9654B4); // Just a pointer to `CStreaming::ms_aInfoForModel`

void CStreamingInfo::InjectHooks() {
    RH_ScopedClass(CStreamingInfo);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x407460);
    RH_ScopedInstall(AddToList, 0x407480);
    RH_ScopedInstall(GetCdPosn, 0x407570);
    RH_ScopedInstall(SetCdPosnAndSize, 0x4075E0);
    RH_ScopedInstall(GetCdPosnAndSize, 0x4075A0);
    RH_ScopedInstall(InList, 0x407560);
    RH_ScopedInstall(RemoveFromList, 0x4074E0);
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

// Used to adding `info` to a linked list
// This is done with the help of `m_nNextIndex` and `m_nPrevIndex`
// which are just `indices` into `ms_aInfoForModel`.
// 0x407480
void CStreamingInfo::AddToList(CStreamingInfo* listStart) {
    m_nNextIndex = listStart->m_nNextIndex;
    m_nPrevIndex = static_cast<ptrdiff_t>(listStart - ms_pArrayBase);
    listStart->m_nNextIndex = static_cast<ptrdiff_t>(this - ms_pArrayBase);
    ms_pArrayBase[m_nNextIndex].m_nPrevIndex = listStart->m_nNextIndex;
}

// 0x407570
size_t CStreamingInfo::GetCdPosn() const {
    return m_nCdPosn + CStreaming::ms_files[m_nImgId].m_StreamHandle;
}

// 0x4075E0
void CStreamingInfo::SetCdPosnAndSize(size_t CdPosn, size_t CdSize) {
    m_nCdPosn = CdPosn;
    m_nCdSize = CdSize;
}

// 0x4075A0
bool CStreamingInfo::GetCdPosnAndSize(size_t& CdPosn, size_t& CdSize) {
    if (!HasCdPosnAndSize())
        return false;
    CdPosn = GetCdPosn();
    CdSize = m_nCdSize;
    return true;
}

// 0x407560
bool CStreamingInfo::InList() const {
    return m_nNextIndex != -1;
}

// 0x4074E0
void CStreamingInfo::RemoveFromList() {
    ms_pArrayBase[m_nNextIndex].m_nPrevIndex = m_nPrevIndex;
    ms_pArrayBase[m_nPrevIndex].m_nNextIndex = m_nNextIndex;
    m_nNextIndex = -1;
    m_nPrevIndex = -1;
}
