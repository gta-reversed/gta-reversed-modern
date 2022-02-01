#include "StdInc.h"

#include "ModelInfoAccelerator.h"

void CModelInfoAccelerator::InjectHooks()
{
    RH_ScopedClass(CModelInfoAccelerator);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x4C6A80);
    RH_ScopedInstall(AddModelInfoId, 0x4C6AA0);
    RH_ScopedInstall(GetNextModelInfoId, 0x4C6AC0);
    RH_ScopedInstall(AllocModelInfoIds, 0x4C6AE0);
    RH_ScopedInstall(FreeModelInfoIds, 0x4C6B10);
    RH_ScopedInstall(GetEntry, 0x4C6B30);
    RH_ScopedInstall(End, 0x4C6B40);
    RH_ScopedInstall(GetModelInfoIdFile, 0x4C6B70);
    RH_ScopedInstall(EndOfLoadPhase, 0x4C6BD0);
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
    auto file = CFileMgr::OpenFile(m_szFilePath, "rb");
    m_bFileRead = file != nullptr;

    CModelInfoAccelerator::AllocModelInfoIds();
    if (m_bFileRead) {
        CFileMgr::Read(file, m_pIDs, BUFFER_SIZE);
        CFileMgr::CloseFile(file);
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
