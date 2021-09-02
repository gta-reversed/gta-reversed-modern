#include "StdInc.h"

void CModelInfoAccelerator::InjectHooks()
{
    ReversibleHooks::Install("CModelInfoAccelerator", "Init", 0x4C6A80, &CModelInfoAccelerator::Init);
    ReversibleHooks::Install("CModelInfoAccelerator", "AddModelInfoId", 0x4C6AA0, &CModelInfoAccelerator::AddModelInfoId);
    ReversibleHooks::Install("CModelInfoAccelerator", "GetNextModelInfoId", 0x4C6AC0, &CModelInfoAccelerator::GetNextModelInfoId);
    ReversibleHooks::Install("CModelInfoAccelerator", "AllocModelInfoIds", 0x4C6AE0, &CModelInfoAccelerator::AllocModelInfoIds);
    ReversibleHooks::Install("CModelInfoAccelerator", "FreeModelInfoIds", 0x4C6B10, &CModelInfoAccelerator::FreeModelInfoIds);
    ReversibleHooks::Install("CModelInfoAccelerator", "GetEntry", 0x4C6B30, &CModelInfoAccelerator::GetEntry);
    ReversibleHooks::Install("CModelInfoAccelerator", "End", 0x4C6B40, &CModelInfoAccelerator::End);
    ReversibleHooks::Install("CModelInfoAccelerator", "GetModelInfoIdFile", 0x4C6B70, &CModelInfoAccelerator::GetModelInfoIdFile);
    ReversibleHooks::Install("CModelInfoAccelerator", "EndOfLoadPhase", 0x4C6BD0, &CModelInfoAccelerator::EndOfLoadPhase);
}

void CModelInfoAccelerator::Init()
{
    m_nNumIDs = 0;
    m_bFileRead = false;
    m_pIDs = nullptr;
    field_1A = 0;
    m_szFilePath[0] = '\0';
}

void CModelInfoAccelerator::AddModelInfoId(uint16 modelId)
{
    m_pIDs[m_nNumIDs] = modelId;
    ++m_nNumIDs;
}

uint16 CModelInfoAccelerator::GetNextModelInfoId()
{
    auto result = m_pIDs[m_nNumIDs];
    ++m_nNumIDs;
    return result;
}

void CModelInfoAccelerator::AllocModelInfoIds()
{
    m_pIDs = new uint16[BUFFER_SIZE];
    memset(m_pIDs, 0, BUFFER_SIZE);
}

void CModelInfoAccelerator::FreeModelInfoIds()
{
    delete[] m_pIDs;
    m_pIDs = nullptr;
}

void CModelInfoAccelerator::GetEntry(CBaseModelInfo** arg0, int32* arg1, char* arg2)
{}

void CModelInfoAccelerator::End(char* arg0)
{}

bool CModelInfoAccelerator::GetModelInfoIdFile()
{
    auto pFile = CFileMgr::OpenFile(m_szFilePath, "rb");
    m_bFileRead = pFile != nullptr;

    CModelInfoAccelerator::AllocModelInfoIds();
    if (m_bFileRead) {
        CFileMgr::Read(pFile, m_pIDs, BUFFER_SIZE);
        CFileMgr::CloseFile(pFile);
    }

    return m_bFileRead;
}

void CModelInfoAccelerator::EndOfLoadPhase()
{
    if (!m_bFileRead) {
        auto pFile = CFileMgr::OpenFileForWriting(m_szFilePath);
        if (pFile) {
            CFileMgr::Write(pFile, m_pIDs, BUFFER_SIZE);
            CFileMgr::CloseFile(pFile);
        }
    }

    CModelInfoAccelerator::FreeModelInfoIds();
}

bool CModelInfoAccelerator::Begin(char* filePath)
{
    strcpy(m_szFilePath, filePath);
    if (field_1A)
        return field_1A;

    return CModelInfoAccelerator::GetModelInfoIdFile();
}
