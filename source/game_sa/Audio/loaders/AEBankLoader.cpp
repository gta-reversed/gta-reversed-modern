#include "StdInc.h"
#include "AEBankLoader.h"

void CAEBankLoader::InjectHooks() {

}

CAEBankLoader::~CAEBankLoader() {
    if (m_bInitialised) {
        CMemoryMgr::Free(m_pBuffer);

        delete m_paBankSlots;
        delete m_paBankLookups;
        delete m_paStreamHandles;
    }
}

CAEBankLookupItem* CAEBankLoader::GetBankLookup(uint16 bankId) {
    if (m_bInitialised && bankId < m_nBankLookupCount)
        return &m_paBankLookups[bankId];

    return nullptr;
}

bool CAEBankLoader::LoadBankLookupFile() {
    const auto file = CFileMgr::OpenFile("AUDIO\\CONFIG\\BANKLKUP.DAT", "rb");
    if (!file)
        return false;

    if (const auto size = CFileMgr::GetTotalSize(file)) {
        m_nBankLookupCount = size / sizeof(CAEBankLookupItem);
        m_paBankLookups = new CAEBankLookupItem[m_nBankLookupCount];

        if (CFileMgr::Read(file, m_paBankLookups, size) != size) {
            delete m_paBankLookups;
            m_paBankLookups = nullptr;
        }

        CFileMgr::CloseFile(file);
        return m_paBankLookups != nullptr;
    } else {
        CFileMgr::CloseFile(file);
    }

    return false;
}

bool CAEBankLoader::LoadBankSlotFile() {
    const auto file = CFileMgr::OpenFile("AUDIO\\CONFIG\\BANKSLOT.DAT", "rb");
    if (!file)
        return false;

    if (auto size = CFileMgr::GetTotalSize(file); size > 2) {
        CalculateBankSlotsInfosOffsets();
        m_nBufferSize = m_paBankSlots[m_nBankSlotCount - 1].m_nOffset + m_paBankSlots[m_nBankSlotCount - 1].m_nSize;
        m_pBuffer = CMemoryMgr::Malloc(m_nBufferSize);
    } else {
        delete m_paBankSlots;
        m_paBankSlots = nullptr;
    }

    CFileMgr::CloseFile(file);
    return m_pBuffer != nullptr;
}

// 0x4DFC70, broken
bool CAEBankLoader::LoadSFXPakLookupFile() {
    const auto file = CFileMgr::OpenFile("AUDIO\\CONFIG\\PAKFILES.DAT", "rb");
    bool failed = true;
    if (!file)
        return failed;

    if (auto size = CFileMgr::GetTotalSize(file)) {
        m_nPakLookupCount = size / sizeof(tPakLookup);
        m_paPakLookups = new tPakLookup[m_nPakLookupCount];

        if (CFileMgr::Read(file, m_paPakLookups, size) == size) {
            m_paStreamHandles = new int32[4 * m_nPakLookupCount];

            for (auto i = 0; i < m_nPakLookupCount; i++) {
                // NOTSA: Originally a 128 char array allocated in the stack.
                m_paStreamHandles[i] = CdStreamOpen(std::format("AUDIO\\SFX\\{}", m_paPakLookups[i].m_szName).c_str());
            }
            failed = false;
        }
    }

    delete m_paPakLookups;
    m_paPakLookups = nullptr;
    CFileMgr::CloseFile(file);
    return !failed;
}

void CAEBankLoader::CalculateBankSlotsInfosOffsets() {
}
